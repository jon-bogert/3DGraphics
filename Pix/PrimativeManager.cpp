#include "PrimativeManager.h"
#include "Rasterizer.h"

PrimativeManager* PrimativeManager::Get()
{
	static PrimativeManager instance;
	return &instance;
}

bool PrimativeManager::BeginDraw(Topology topology)
{
	_vertexBuffer.clear();
	_topology = topology;

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
			Rasterizer::Get()->DrawPoint(_vertexBuffer[i]);
		}
		break;
	case Topology::Line:
		for (int i = 1; i < _vertexBuffer.size(); i += 2)
		{
			Rasterizer::Get()->DrawLine(_vertexBuffer[i - 1], _vertexBuffer[i]);
		}
		break;
	case Topology::Triangle:
		for (int i = 2; i < _vertexBuffer.size(); i += 3)
		{
			Rasterizer::Get()->DrawTriangle(_vertexBuffer[i - 2], _vertexBuffer[i - 1], _vertexBuffer[i]);
		}
		break;
	default:
		return false;
	}

	return true;
}
