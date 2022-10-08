#pragma once

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

private:

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;
};