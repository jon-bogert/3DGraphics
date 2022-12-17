#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "MathHelper.h"

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
	if (DepthBuffer::Get()->CheckDepthBuffer(v.position.x, v.position.y, v.position.z))
	{
		X::DrawPixel((int)v.position.x, (int)v.position.y, v.color);
	}
}

void Rasterizer::DrawLine(Vertex v1, Vertex v2)
{
	int dx = v2.position.x - v1.position.x;
	int dy = v2.position.y - v1.position.y;
	bool vertLine = (dx == 0);

	float m{};
	if (!vertLine) m = dy / (float)dx;
	float t{};

	if (fabs(m) <= 1 && !vertLine)
	{
		for (int i = 0; i <= abs(dx); ++i)
		{
			t = i / fabs(dx);
			DrawPoint(Vertex::LerpVertex(v1, v2, t));
		}
	}
	else
	{
		for (int i = 0; i <= abs(dy); ++i)
		{
			t = i / fabs(dy);
			DrawPoint(Vertex::LerpVertex(v1, v2, t));
		}
	}
}

void Rasterizer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v2.color = v1.color;
		v3.color = v1.color;
		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((v2.position - v1.position),
			(v3.position - v1.position)));
		v1.normal = faceNorm;
		v2.normal = faceNorm;
		v3.normal = faceNorm;
	}

	if (mFillMode == FillMode::Wireframe)
	{
		DrawLine(v1, v2);
		DrawLine(v2, v3);
		DrawLine(v3, v1);
		return;
	}

	//Sort Coners by 'y' value
	Vertex corners[] = { v1, v2, v3 };
	if (corners[0].position.y > corners[1].position.y)
		std::swap(corners[0], corners[1]);
	if (corners[0].position.y > corners[2].position.y)
		std::swap(corners[0], corners[2]);
	if (corners[1].position.y > corners[2].position.y)
		std::swap(corners[1], corners[2]);


	//lineLong = [0][2]
	//lineShortA = [0][1]
	//lineShortB = [1][2]
	int dyLong = corners[2].position.y - corners[0].position.y;
	int dyShort = corners[1].position.y - corners[0].position.y;
	int dx{};
	Vertex longSide{}, shortSide{};

	for (int i = 0; i <= abs(dyLong); ++i)
	{
		longSide = Vertex::LerpVertex(corners[0], corners[2], i / fabs(dyLong));
		if (i <= dyShort) //1st sub-tri
		{
			if (dyShort == 0) shortSide = corners[1]; // straight edge check
			else shortSide = Vertex::LerpVertex(corners[0], corners[1], i / fabs(dyShort));
		}
		else // 2nd sub-tri
		{
			if (dyLong - dyShort == 0) shortSide = corners[1];// straight edge check
			else shortSide = Vertex::LerpVertex(corners[1], corners[2], (i - dyShort) / fabs(dyLong - dyShort));
		}
		dx = shortSide.position.x - longSide.position.x;
		for (int j = 0; j <= abs(dx); ++j)
		{
			DrawPoint(Vertex::LerpVertex(longSide, shortSide, j / fabs(dx)));
		}
	}
}

X::Color Rasterizer::GetColor() const
{
	return mColor;
}

ShadeMode Rasterizer::GetShadeMode() const
{
	return mShadeMode;
}
