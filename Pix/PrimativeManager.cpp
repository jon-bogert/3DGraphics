#include "PrimativeManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Matrix4.h"
#include "MatrixStack.h";
#include "Camera.h"
#include "MathHelper.h"
#include "DirectionalLight.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		float hw = gResolutionX * 0.5f;
		float hh = gResolutionY * 0.5f;
		return{
			hw,		0.0f,	0.0f,	0.0f,
			0.0f,	-hh,	0.0f,	0.0f,
			0.0f,	0.0f,	1.0f,	0.0f,
			hw,		hh,		0.0f,	1.0f
		};
	}
}

PrimativeManager* PrimativeManager::Get()
{
	static PrimativeManager instance;
	return &instance;
}

void PrimativeManager::OnNewFrame()
{
	mCorrectUV = true;
}

bool PrimativeManager::BeginDraw(Topology topology, bool applyTransform)
{
	_vertexBuffer.clear();
	_topology = topology;
	_applyTransform = applyTransform;

	return true;
}

void PrimativeManager::AddVertex(Vertex vertex)
{
	_vertexBuffer.push_back(vertex);
}

bool PrimativeManager::EndDraw()
{
	switch (_topology)
	{
	case Topology::Point:
		for (int i = 0; i < _vertexBuffer.size(); ++i)
		{
			if (!Clipper::Get()->ClipPoint(_vertexBuffer[i]))
				Rasterizer::Get()->DrawPoint(_vertexBuffer[i]);
		}
		break;
	case Topology::Line:
		for (int i = 1; i < _vertexBuffer.size(); i += 2)
		{
			if (Clipper::Get()->ClipLine(_vertexBuffer[i - 1], _vertexBuffer[i]))
				Rasterizer::Get()->DrawLine(_vertexBuffer[i - 1], _vertexBuffer[i]);
		}
		break;
	case Topology::Triangle:
	{
		Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		Matrix4 matView = Camera::Get()->GetViewMatrix();
		Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		Matrix4 matScreen = GetScreenTransform();
		Matrix4 matFinal = matProj * matScreen;

		for (int i = 2; i < _vertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { _vertexBuffer[i - 2], _vertexBuffer[i - 1], _vertexBuffer[i] };
			if (_applyTransform)
			{
				if (MathHelper::MagnitudeSquared(triangle[0].normal) < 0.5f)
				{
					Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((triangle[1].position - triangle[0].position),
						(triangle[2].position - triangle[0].position)));
					for (auto& v : triangle)
						v.normal = faceNorm;
				}

				//to world
				for (auto& v : triangle)
				{
					v.position = MathHelper::TransformCoord(v.position, matWorld);
					v.normal = MathHelper::TransformNormal(v.normal, matWorld);
					v.worldPosition = v.position;
					v.worldNormal = v.normal;
				}

				//apply color
				if (Rasterizer::Get()->GetShadeMode() != ShadeMode::Phong)
				{
					for (auto& v : triangle)
					{
						v.color *= LightManager::Get()->ComputeLightColor(v.position, v.normal);
					}
				}

				if (mCullMode != CullMode::None)
				{
					for (auto& v : triangle)
					{
						v.position = MathHelper::TransformCoord(v.position, matView);
						v.normal = MathHelper::TransformNormal(v.normal, matView);
					}

					if (mCorrectUV && triangle[0].color.z < 0.f)
					{
						for (auto& v : triangle)
						{
							v.color.x /= v.position.z;
							v.color.y /= v.position.z;
							v.color.w = 1.f / v.position.z;
						}
					}

					//Get facing camera to determine culling
					Vector3 faceNorm = MathHelper::Cross((triangle[1].position - triangle[0].position),
						(triangle[2].position - triangle[0].position));

					if (mCullMode == CullMode::Back && faceNorm.z > 0.f)
					{
						continue;
					}
					else if (mCullMode == CullMode::Front && faceNorm.z < 0.f)
					{
						continue;
					}
				}

				for (auto& v : triangle)
				{
					auto posScreen = MathHelper::TransformCoord(v.position, matScreen);
					v.position = posScreen;
				}
			}
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (int j = 2; j < triangle.size(); ++j)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[j - 1], triangle[j]);
				}
			}
		}
		break;
	}
	default:
		return false;
	}

	return true;
}

void PrimativeManager::SetCullMode(const CullMode cm)
{
	mCullMode = cm;
}

CullMode PrimativeManager::GetCullMode() const
{
	return mCullMode;
}

void PrimativeManager::SetCorrectUV(bool setTo)
{
	mCorrectUV = setTo;
}
