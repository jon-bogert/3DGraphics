#include "Rasterizer.h"

#include "DepthBuffer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::SetShadeMode(ShadeMode mode)
{
	mShadeMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}