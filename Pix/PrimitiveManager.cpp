#include "PrimitiveManager.h"

#include "Camera.h"
#include "Clipper.h"
#include "LightManager.h"
#include "MatrixStack.h"
#include "Rasterizer.h"
#include "Viewport.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		float hw = gResolutionX * 0.5f;
		float hh = gResolutionY * 0.5f;
		return {
			hw,   0.0f, 0.0f, 0.0f,
			0.0f, -hh,  0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw,   hh,   0.0f, 1.0f
		};
	}

	bool IsNDCBackface(Vertex a, Vertex b, Vertex c)
	{
		Vector3 ab = b.pos - a.pos;
		Vector3 ac = c.pos - a.pos;
		Vector3 normal = Normalize(Cross(ab, ac));
		return normal.z > 0.0f;
	}
}

PrimitiveManager* PrimitiveManager::Get()
{
	static PrimitiveManager sInstance;
	return &sInstance;
}

void PrimitiveManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
	mCorrectUV = true;
}

void PrimitiveManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

void PrimitiveManager::SetCorrectUV(bool correctUV)
{
	mCorrectUV = correctUV;
}

bool PrimitiveManager::BeginDraw(Topology topology, bool applyTransform)
{
	if (mDrawBegin)
		return false;

	mVertexBuffer.clear();
	mTopology = topology;
	mApplyTransform = applyTransform;
	mDrawBegin = true;
	return true;
}

void PrimitiveManager::AddVertex(Vertex vertex)
{
	if (mDrawBegin)
		mVertexBuffer.push_back(vertex);
}

bool PrimitiveManager::EndDraw()
{
	if (!mDrawBegin)
		return false;

	auto clipper = Clipper::Get();
	auto rasterizer = Rasterizer::Get();

	switch (mTopology)
	{
		case Topology::Point:
		{
			if (mApplyTransform)
			{
				Matrix4 matWorld = MatrixStack::Get()->GetTransform();
				Matrix4 matView = Camera::Get()->GetViewMatrix();
				Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
				Matrix4 matScreen = GetScreenTransform();
				Matrix4 matFinal = matWorld * matView * matProj * matScreen;

				for (auto& v : mVertexBuffer)
				{
					auto posScreen = TransformCoord(v.pos, matFinal);
					v.pos = posScreen;
				}
			}

			for (size_t i = 0; i < mVertexBuffer.size(); ++i)
			{
				if (clipper->ClipPoint(mVertexBuffer[i]))
					rasterizer->DrawPoint(mVertexBuffer[i]);
			}
			break;
		}
		case Topology::Line:
		{
			if (mVertexBuffer.size() >= 2)
			{
				if (mApplyTransform)
				{
					Matrix4 matWorld = MatrixStack::Get()->GetTransform();
					Matrix4 matView = Camera::Get()->GetViewMatrix();
					Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
					Matrix4 matScreen = GetScreenTransform();
					Matrix4 matFinal = matWorld * matView * matProj * matScreen;

					for (auto& v : mVertexBuffer)
					{
						auto posScreen = TransformCoord(v.pos, matFinal);
						v.pos = posScreen;
					}
				}

				for (size_t i = 0; i < mVertexBuffer.size(); i += 2)
				{
					auto v1 = mVertexBuffer[i];
					auto v2 = mVertexBuffer[i + 1];
					if (clipper->ClipLine(v1, v2))
						rasterizer->DrawLine(v1, v2);
				}
			}
			break;
		}
		case Topology::Triangle:
		{
			if (mVertexBuffer.size() >= 3)
			{
				std::vector<Vertex> triangles;

				if (mApplyTransform)
				{
					Matrix4 matWorld = MatrixStack::Get()->GetTransform();
					Matrix4 matView = Camera::Get()->GetViewMatrix();
					Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
					Matrix4 toWorld = matWorld;
					Matrix4 toView = matView;
					Matrix4 toNDC = matProj;
					Matrix4 toScreen = GetScreenTransform();

					auto lm = LightManager::Get();

					for (size_t i = 0; i < mVertexBuffer.size(); i += 3)
					{
						auto a = mVertexBuffer[i];
						auto b = mVertexBuffer[i + 1];
						auto c = mVertexBuffer[i + 2];

						a.pos = TransformCoord(a.pos, matWorld);
						b.pos = TransformCoord(b.pos, matWorld);
						c.pos = TransformCoord(c.pos, matWorld);

						// HACK: If texturing, don't apply light
						if (a.color.z >= 0.0f)
						{
							auto normal = Normalize(Cross(b.pos - a.pos, c.pos - a.pos));
							a.color *= lm->ComputeLightColor(a.pos, normal);
							b.color *= lm->ComputeLightColor(b.pos, normal);
							c.color *= lm->ComputeLightColor(c.pos, normal);
						}

						a.pos = TransformCoord(a.pos, toView);
						b.pos = TransformCoord(b.pos, toView);
						c.pos = TransformCoord(c.pos, toView);

						if (mCorrectUV && a.color.z < 0.0f)
						{
							a.color.x /= a.pos.z;
							a.color.y /= a.pos.z;
							b.color.x /= b.pos.z;
							b.color.y /= b.pos.z;
							c.color.x /= c.pos.z;
							c.color.y /= c.pos.z;
							a.color.w = 1.0f / a.pos.z;
							b.color.w = 1.0f / b.pos.z;
							c.color.w = 1.0f / c.pos.z;
						}

						a.pos = TransformCoord(a.pos, toNDC);
						b.pos = TransformCoord(b.pos, toNDC);
						c.pos = TransformCoord(c.pos, toNDC);

						if (mCullMode == CullMode::Back && IsNDCBackface(a, b, c))
							continue;
						else if (mCullMode == CullMode::Front && !IsNDCBackface(a, b, c))
							continue;

						a.pos = TransformCoord(a.pos, toScreen);
						b.pos = TransformCoord(b.pos, toScreen);
						c.pos = TransformCoord(c.pos, toScreen);

						triangles.push_back(a);
						triangles.push_back(b);
						triangles.push_back(c);
					}
				}
				else
				{
					triangles = mVertexBuffer;
				}

				for (size_t i = 0; i < triangles.size(); i += 3)
				{
					std::vector<Vertex> vertices;
					vertices.push_back(triangles[i]);
					vertices.push_back(triangles[i + 1]);
					vertices.push_back(triangles[i + 2]);
					if (clipper->ClipTriangle(vertices))
					{
						for (size_t j = 2; j < vertices.size(); ++j)
						{
							rasterizer->DrawTriangle(vertices[0], vertices[j - 1], vertices[j]);
						}
					}
				}
			}
			break;
		}
	default:
		break;
	}

	mDrawBegin = false;
	return true;
}