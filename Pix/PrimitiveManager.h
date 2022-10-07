#pragma once

#include "MathHelper.h"
#include "Vertex.h"
#include <XEngine.h>

enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None,
	Front,
	Back
};

class PrimitiveManager
{
public:
	static PrimitiveManager* Get();

public:
	void OnNewFrame();

	void SetCullMode(CullMode mode);
	void SetCorrectUV(bool correctUV);

	bool BeginDraw(Topology topology, bool applyTransform);
	void AddVertex(Vertex vertex);
	bool EndDraw();

private:
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Triangle;
	CullMode mCullMode = CullMode::Back;
	bool mApplyTransform = false;
	bool mCorrectUV = true;
	bool mDrawBegin = false;
};