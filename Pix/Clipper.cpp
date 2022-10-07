#include "Clipper.h"

#include "Viewport.h"

namespace
{
	using OutCode = uint32_t;

	// OutCode:
	//
	//     1001  |  1000  |  1010      LEFT   = 1st bit
	// ----------------------------    RIGHT  = 2nd bit
	//     0001  |  0000  |  0010      BOTTOM = 3rd bit
	// ----------------------------    TOP    = 4th bit
	//     0101  |  0100  |  0110

	constexpr OutCode OutCode_Inside = 0; // 0000
	constexpr OutCode OutCode_Left   = 1; // 0001
	constexpr OutCode OutCode_Right  = 2; // 0010
	constexpr OutCode OutCode_Bottom = 4; // 0100
	constexpr OutCode OutCode_Top    = 8; // 1000

	OutCode ComputeOutCode(Vector3 pt)
	{
		OutCode code = OutCode_Inside;
		auto vp = Viewport::Get();

		if (pt.x < vp->GetMinX())		// To the left of clip window
			code |= OutCode_Left;
		else if (pt.x > vp->GetMaxX())	// To the right of clip window
			code |= OutCode_Right;
		else if (pt.y > vp->GetMaxY())	// Below the clip window
			code |= OutCode_Bottom;
		if (pt.y < vp->GetMinY())		// Above the clip window
			code |= OutCode_Top;

		return code;
	}

	enum ClipEdge
	{
		ClipEdge_Left,
		ClipEdge_Bottom,
		ClipEdge_Right,
		ClipEdge_Top,
		ClipEdge_Count
	};

	bool IsInFront(ClipEdge edge, Vector3 pt)
	{
		auto vp = Viewport::Get();

		switch (edge)
		{
		case ClipEdge_Left:   return (pt.x > vp->GetMinX());
		case ClipEdge_Bottom: return (pt.y < vp->GetMaxY());
		case ClipEdge_Right:  return (pt.x < vp->GetMaxX());
		case ClipEdge_Top:    return (pt.y > vp->GetMinX());
		}
		
		return false;
	}

	Vertex ComputeIntersection(ClipEdge edge, Vertex v1, Vertex v2)
	{
		auto vp = Viewport::Get();

		float t = 0.0f;
		switch (edge)
		{
		case ClipEdge_Left:
			t = (vp->GetMinX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
			break;
		case ClipEdge_Bottom:
			t = (vp->GetMaxY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
			break;
		case ClipEdge_Right:
			t = (vp->GetMaxX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
			break;
		case ClipEdge_Top:
			t = (vp->GetMinY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
			break;
		}

		return LerpVertex(v1, v2, t);
	}
}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

void Clipper::OnNewFrame()
{
	mClipping = false;
}

bool Clipper::ClipPoint(Vertex v)
{
	// If not clipping, skip viewport check
	if (!mClipping)
		return true;

	auto vp = Viewport::Get();
	if (v.pos.x >= vp->GetMinX() &&
		v.pos.x < vp->GetMaxX() &&
		v.pos.y >= vp->GetMinY() &&
		v.pos.y < vp->GetMaxY())
		return true;

	return false;
}

bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
	// If not clipping, skip viewport check
	if (!mClipping)
		return true;

	// Cohen-Sutherland algorithm
	// https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm

	OutCode outCode1 = ComputeOutCode(v1.pos);
	OutCode outCode2 = ComputeOutCode(v2.pos);
	bool accept = false;

	auto vp = Viewport::Get();
	while (true)
	{
		if ((outCode1 | outCode2) == 0)
		{
			// bitwise OR is 0000: both points inside window; trivially accept and exit loop
			accept = true;
			break;
		}
		else if ((outCode1 & outCode2) != 0)
		{
			// bitwise AND is not 0000: both points share an outside zone (LEFT, RIGHT, TOP,
			// or BOTTOM), so both must be outside window; exit loop (accept is false)
			break;
		}
		else
		{
			// failed both tests, so calculate the line segment to clip
			// from an outside point to an intersection with clip edge
			Vertex intersection;

			// At least one endpoint is outside the clip rectangle; pick it.
			OutCode outCodeOut = outCode2 > outCode1 ? outCode2 : outCode1;

			// Now find the intersection point;
			// use formulas:
			//   slope = (y1 - y0) / (x1 - x0)
			//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
			//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
			// No need to worry about divide-by-zero because, in each case, the
			// outcode bit being tested guarantees the denominator is non-zero
			if (outCodeOut & OutCode_Top)
			{
				// point is above the clip window
				float t = (vp->GetMinY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
				intersection = LerpVertex(v1, v2, t);
			}
			else if (outCodeOut & OutCode_Bottom)
			{
				// point is below the clip window
				float t = (vp->GetMaxY() - v1.pos.y) / (v2.pos.y - v1.pos.y);
				intersection = LerpVertex(v1, v2, t);
			}
			else if (outCodeOut & OutCode_Right)
			{
				// point is to the right of clip window
				float t = (vp->GetMaxX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
				intersection = LerpVertex(v1, v2, t);
			}
			else if (outCodeOut & OutCode_Left)
			{
				// point is to the left of clip window
				float t = (vp->GetMinX() - v1.pos.x) / (v2.pos.x - v1.pos.x);
				intersection = LerpVertex(v1, v2, t);
			}

			// Now we move outside point to intersection point to clip
			// and get ready for next pass.
			if (outCodeOut == outCode1)
			{
				v1 = intersection;
				outCode1 = ComputeOutCode(intersection.pos);
			}
			else
			{
				v2 = intersection;
				outCode2 = ComputeOutCode(intersection.pos);
			}
		}
	}

	return accept;
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	// If not clipping, skip viewport check
	if (!mClipping)
		return true;

	// Sutherland-Hodgman algorithm
	// https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm

	for (int e = 0; e < ClipEdge_Count; ++e)
	{
		auto inputList = vertices;
		vertices.clear();

		ClipEdge edge = (ClipEdge)e;
		size_t count = inputList.size();
		if (count == 0)
			return false;
		Vertex previous = inputList[count - 1];

		for (size_t i = 0; i < count; ++i)
		{
			Vertex current = inputList[i];

			if (IsInFront(edge, current.pos))
			{
				if (!IsInFront(edge, previous.pos))
				{
					vertices.push_back(ComputeIntersection(edge, previous, current));
				}
				vertices.push_back(current);
			}
			else if (IsInFront(edge, previous.pos))
			{
				vertices.push_back(ComputeIntersection(edge, previous, current));
			}

			previous = current;
		}
	}

	return true;
}