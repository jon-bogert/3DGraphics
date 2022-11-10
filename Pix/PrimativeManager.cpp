#include "PrimativeManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Matrix4.h"
#include "MatrixStack.h";
#include "Camera.h"
#include "MathHelper.h"

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

	if (_applyTransform)
	{
		Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		Matrix4 matView = Camera::Get()->GetViewMatrix();
		Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		Matrix4 matScreen = GetScreenTransform();
		Matrix4 matFinal = matWorld * matView * matProj * matScreen;
		for (auto& v : _vertexBuffer)
		{
			auto posScreen = MathHelper::TransformCoord(v.position, matFinal);
			v.position = posScreen;
		}
	}

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
		for (int i = 2; i < _vertexBuffer.size(); i += 3)
		{

			std::vector<Vertex> triangle = { _vertexBuffer[i - 2], _vertexBuffer[i - 1], _vertexBuffer[i] };
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (int j = 2; j < triangle.size(); ++j)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[j - 1], triangle[j]);
				}
			}
		}
		break;
	default:
		return false;
	}

	return true;
}
