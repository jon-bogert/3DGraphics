#include "Clipper.h"
#include "Vertex.h"
#include "Viewport.h"
#include "PrimativeManager.h"
#include <iostream>

const int CODE_INSIDE = 0;	  // 0000
const int CODE_LEFT = 1 << 1; // 0001
const int CODE_RIGHT = 1 << 2; // 0010
const int CODE_BOTTOM = 1 << 3; // 0100
const int CODE_TOP = 1 << 4; // 1000


enum class ClipEdge : int {Left, Bottom, Right, Top, Count};

bool IsInFront(ClipEdge edge, const Vector3& point)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	switch (edge)
	{
	case ClipEdge::Left:	return point.x > minX;
	case ClipEdge::Bottom:	return point.y < maxY;
	case ClipEdge::Right:	return point.x < maxX;
	case ClipEdge::Top:		return point.y > minY;
	default:
		break;
	}
	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v1, const Vertex& v2)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	float t = 0.0f;
	switch (edge)
	{
	case ClipEdge::Left:
		t = (minX - v1.position.x) / (v2.position.x - v1.position.x);
		break;
	case ClipEdge::Bottom:
		t = (maxY - v1.position.y) / (v2.position.y - v1.position.y);
		break;
	case ClipEdge::Right:
		t = (maxX - v1.position.x) / (v2.position.x - v1.position.x);
		break;
	case ClipEdge::Top:
		t = (minY - v1.position.y) / (v2.position.y - v1.position.y);
		break;
	default:
		break;
	}

	return Vertex::LerpVertex(v1, v2, t);
}


Clipper* Clipper::Get()
{
	static Clipper instance;
	return &instance;
}

void Clipper::OnNewFrame()
{
}

bool Clipper::ClipPoint(Vertex& v)
{
	if (!mIsClipping)
		return false;

	return !(v.position.x >= Viewport::Get()->GetMinX()
		&& v.position.x <= Viewport::Get()->GetMaxX()
		&& v.position.y >= Viewport::Get()->GetMinY()
		&& v.position.y <= Viewport::Get()->GetMaxY());
}

bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
	if (mIsClipping)
	{
		float maxX = Viewport::Get()->GetMaxX();
		float maxY = Viewport::Get()->GetMaxY();
		float minX = Viewport::Get()->GetMinX();
		float minY = Viewport::Get()->GetMinY();
		int codeV1 = GetRegionCode(v1.position.x, v1.position.y);
		int codeV2 = GetRegionCode(v2.position.x, v2.position.y);
		bool accept = false;

		while (true)
		{
			if (!(codeV1 | codeV2))
			{
				accept = true;
				break;
			}
			else if (codeV1 & codeV2)
			{
				break;
			}
			else
			{
				float x, y = 0.0f;
				int outcodeOut = codeV2 > codeV1 ? codeV2 : codeV1;

				if (outcodeOut & CODE_TOP)
				{
					x = v1.position.x + (v2.position.x - v1.position.x) * (maxY - v1.position.y) / (v2.position.y - v1.position.y);
					y = maxY;
				}
				else if (outcodeOut & CODE_BOTTOM)
				{
					x = v1.position.x + (v2.position.x - v1.position.x) * (minY - v1.position.y) / (v2.position.y - v1.position.y);
					y = minY;
				}
				else if (outcodeOut & CODE_RIGHT)
				{
					y = v1.position.y + (v2.position.y - v1.position.y) * (maxX - v1.position.x) / (v2.position.x - v1.position.x);
					x = maxX;
				}
				else if (outcodeOut & CODE_LEFT)
				{
					y = v1.position.y + (v2.position.y - v1.position.y) * (minX - v1.position.x) / (v2.position.x - v1.position.x);
					x = minX;
				}
				if (outcodeOut == codeV1)
				{
					v1.position.x = x;
					v1.position.y = y;
					codeV1 = GetRegionCode(v1.position.x, v1.position.y);
				}
				else
				{
					v2.position.x = x;
					v2.position.y = y;
					codeV2 = GetRegionCode(v2.position.x, v2.position.y);
				}
			}
		}
		return accept;
	}
	return true;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (mIsClipping)
	{
		std::vector<Vertex> newVertices;
		for (int i = 0; i < static_cast<int>(ClipEdge::Count); ++i)
		{
			newVertices.clear();
			ClipEdge edge = static_cast<ClipEdge>(i);
			for (size_t n = 0; n < vertices.size(); ++n)
			{
				size_t np1 = (n + 1) % vertices.size();
				const Vertex& v1 = vertices[n];
				const Vertex& v2 = vertices[np1];
				bool isInFront_V1 = IsInFront(edge, v1.position);
				bool isInFront_V2 = IsInFront(edge, v2.position);

				if (isInFront_V1 && isInFront_V2)
				{
					newVertices.push_back(v2);
				}
				else if (isInFront_V1 && !isInFront_V2)
				{
					newVertices.push_back(ComputeIntersection(edge, v1, v2));
				}
				else if (!isInFront_V1 && isInFront_V2)
				{
					newVertices.push_back(ComputeIntersection(edge, v1, v2));
					newVertices.push_back(v2);
				}
			}
			vertices = newVertices;
		}
	}
	return true;
}

bool Clipper::GetIsClipping() const
{
	return mIsClipping;
}

void Clipper::SetIsClipping(const bool isClipping)
{
	mIsClipping = isClipping;
}

int Clipper::GetRegionCode(const float& x, const float& y)
{
	int code = CODE_INSIDE; // Center

	if (x < Viewport::Get()->GetMinX()) //Left
		code |= CODE_LEFT;
	else if (x > Viewport::Get()->GetMaxX()) //Right
		code |= CODE_RIGHT;
	if (y < Viewport::Get()->GetMinY())//Below
		code |= CODE_BOTTOM;
	else if (y > Viewport::Get()->GetMaxY())//Above
		code |= CODE_TOP;

	return code;
}
