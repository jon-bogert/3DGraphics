#pragma once

#include <XEngine.h>
#include "Vertex.h"

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

	X::Color GetColor() const;
	ShadeMode GetShadeMode() const;

private:

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;

	bool showDebug = true;
};