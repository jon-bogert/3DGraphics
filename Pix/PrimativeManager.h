#pragma once
#include "Vertex.h"

enum class Topology
{
	Point, Line, Triangle
};

class PrimativeManager
{
	std::vector<Vertex> _vertexBuffer;
	Topology _topology = Topology::Triangle;
	bool _drawBegin = false;

	PrimativeManager() {}

public:
	~PrimativeManager() {}
	static PrimativeManager* Get();

	bool BeginDraw(Topology topology);
	void AddVertex(Vertex vertex);
	bool EndDraw();
};

