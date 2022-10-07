#pragma once

#include "MathHelper.h"
#include "Vertex.h"
#include <XEngine.h>

enum class FillMode
{
	Solid,
	Wireframe
};

enum class ShadeMode
{
	Flat,
	Gouraud,
	Phong
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);
	void SetShadeMode(ShadeMode mode);

	void DrawPoint(int x, int y);

	void DrawPoint(Vertex v);
	void DrawLine(Vertex v1, Vertex v2);
	void DrawTriangle(Vertex v1, Vertex v2, Vertex v3);

private:
	// TODO - Fix splitting bug so it does not fall into an infinite loop
	// (check 3d_texturing and rotate cube when camera is close). Remove 'canSplit'.
	void DrawTriangleFilled(Vertex v1, Vertex v2, Vertex v3, bool canSplit);
	void DrawTriangleWireframe(Vertex v1, Vertex v2, Vertex v3);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;
};