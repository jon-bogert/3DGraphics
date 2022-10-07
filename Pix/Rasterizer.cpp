#include "Rasterizer.h"

#include "DepthBuffer.h"
#include "TextureCache.h"

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

void Rasterizer::DrawPoint(Vertex v)
{
	int x = static_cast<int>(v.pos.x);
	int y = static_cast<int>(v.pos.y);
	if (DepthBuffer::Get()->CheckDepthBuffer(x, y, v.pos.z))
		X::DrawPixel(x, y, v.color);
}

void Rasterizer::DrawLine(Vertex v1, Vertex v2)
{
	float dx = v2.pos.x - v1.pos.x;
	float dy = v2.pos.y - v1.pos.y;
	float m = dy / dx;
	float b = v1.pos.y - (m * v1.pos.x);

	int startX = static_cast<int>(v1.pos.x);
	int endX = static_cast<int>(v2.pos.x);
	int stepsX = static_cast<int>(fabs(dx));
	int startY = static_cast<int>(v1.pos.y);
	int endY = static_cast<int>(v2.pos.y);
	int stepsY = static_cast<int>(fabs(dy));

	auto db = DepthBuffer::Get();
	auto tc = TextureCache::Get();

	if (fabs(m) <= 1.0f)
	{
		// Loop in x
		int dx = (startX < endX) ? 1 : -1;
		for (int x = startX; x != endX; x += dx)
		{
			float t = static_cast<float>(abs(x - startX)) / stepsX;
			float z = v1.pos.z + (v2.pos.z - v1.pos.z) * t;
			int y = static_cast<int>((m * x) + b);
			if (db->CheckDepthBuffer(x, y, z))
				X::DrawPixel(x, y, tc->SampleColor(LerpColor(v1.color, v2.color, t)));
		}
	}
	else
	{
		// Loop in y
		int dy = (startY < endY) ? 1 : -1;
		for (int y = startY; y != endY; y += dy)
		{
			float t = static_cast<float>(abs(y - startY)) / stepsY;
			float z = v1.pos.z + (v2.pos.z - v1.pos.z) * t;
			int x = static_cast<int>((y - b) / m);
			if (db->CheckDepthBuffer(x, y, z))
				X::DrawPixel(x, y, tc->SampleColor(LerpColor(v1.color, v2.color, t)));
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v2.color = v1.color;
		v3.color = v1.color;
	}

	switch (mFillMode)
	{
		case FillMode::Solid:
		{
			DrawTriangleFilled(v1, v2, v3, true);
			break;
		}
		case FillMode::Wireframe:
		{
			DrawTriangleWireframe(v1, v2, v3);
			break;
		}
	}
}

void Rasterizer::DrawTriangleFilled(Vertex v1, Vertex v2, Vertex v3, bool canSplit)
{
	// Order vertices from top to bottom
	Vertex yOrder[3] = { v1, v2, v3 };
	Vertex temp;
	if (yOrder[1].pos.y < yOrder[0].pos.y)
	{
		temp = yOrder[0]; yOrder[0] = yOrder[1]; yOrder[1] = temp;
	}
	if (yOrder[2].pos.y < yOrder[1].pos.y)
	{
		temp = yOrder[1]; yOrder[1] = yOrder[2]; yOrder[2] = temp;
	}
	if (yOrder[1].pos.y < yOrder[0].pos.y)
	{
		temp = yOrder[0]; yOrder[0] = yOrder[1]; yOrder[1] = temp;
	}

	// Check for a flat line along y
	if (canSplit && v1.pos.y != v2.pos.y && v1.pos.y != v3.pos.y && v2.pos.y != v3.pos.y)
	{
		// No flat line, split the triangles and process separately

		// Find vertex to split triangles
		float t = (yOrder[1].pos.y - yOrder[0].pos.y) / (yOrder[2].pos.y - yOrder[0].pos.y);
		Vertex splitVertex = LerpVertex(yOrder[0], yOrder[2], t);

		// draw two new triangles seperately
		DrawTriangleFilled(yOrder[0], splitVertex, yOrder[1], false);
		DrawTriangleFilled(yOrder[1], splitVertex, yOrder[2], false);
	}
	else
	{
		int yTop = static_cast<int>(yOrder[0].pos.y);
		int yBottom = static_cast<int>(yOrder[2].pos.y);
		int yRange = yBottom - yTop + 1;

		if (yOrder[0].pos.y == yOrder[1].pos.y)
		{
			// Flat top
			int leftTop, rightTop;
			if (yOrder[0].pos.x < yOrder[1].pos.x)
			{
				leftTop = 0;
				rightTop = 1;
			}
			else
			{
				leftTop = 1;
				rightTop = 0;
			}

			for (int y = yTop; y <= yBottom; ++y)
			{
				float t = static_cast<float>(y - yTop) / (yRange - 1);
				Vertex left = LerpVertex(yOrder[leftTop], yOrder[2], t);
				Vertex right = LerpVertex(yOrder[rightTop], yOrder[2], t);
				left.pos.y = right.pos.y = (float)y;
				DrawLine(left, right);
			}
		}
		else
		{
			// Flat bottom
			int leftBottom, rightBottom;
			if (yOrder[1].pos.x < yOrder[2].pos.x)
			{
				leftBottom = 1;
				rightBottom = 2;
			}
			else
			{
				leftBottom = 2;
				rightBottom = 1;
			}

			for (int y = yTop; y <= yBottom; ++y)
			{
				float t = static_cast<float>(y - yTop) / (yRange - 1);
				Vertex left = LerpVertex(yOrder[0], yOrder[leftBottom], t);
				Vertex right = LerpVertex(yOrder[0], yOrder[rightBottom], t);
				left.pos.y = right.pos.y = (float)y;
				DrawLine(left, right);
			}
		}
	}
}

void Rasterizer::DrawTriangleWireframe(Vertex v1, Vertex v2, Vertex v3)
{
	DrawLine(v1, v2);
	DrawLine(v2, v3);
	DrawLine(v3, v1);

	// TODO: Problem, using Bresenheim's algorithm, you can have
	// more than one pixel along the first row if you have a shallow enough line:
	//
	//    ****
	//        ********
	//                ********
	//
	// However, with edge walking, you will never be able to have more than
	// one pixel for the first row as the interpolation starts at 0!
	// In other words, if you switch between wireframe vs solid mode, you will
	// always have different results. How is this handled??
	//
	// Solution: Look up rasterization rules on how to decide which pixel to fill.
	// https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-rasterizer-stage-rules
}
