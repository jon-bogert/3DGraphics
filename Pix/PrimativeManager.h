#pragma once
#include "Vertex.h"

enum class Topology
{
	Point, Line, Triangle
};
enum class CullMode
{
	Back, Front, None
};

class PrimativeManager
{
	std::vector<Vertex> _vertexBuffer;
	Topology _topology = Topology::Triangle;
	bool _drawBegin = false;

	bool _applyTransform = false;

	CullMode mCullMode = CullMode::None;
	bool mCorrectUV = false;

	PrimativeManager() {}

public:
	~PrimativeManager() {}
	static PrimativeManager* Get();

	void OnNewFrame();

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(Vertex vertex);
	bool EndDraw();

	void SetCullMode(const CullMode cm);
	CullMode GetCullMode() const;
	void SetCorrectUV(bool setTo);
};

