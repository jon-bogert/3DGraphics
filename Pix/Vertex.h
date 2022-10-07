#pragma once

#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vector3 pos;
	X::Color color; // if z or b is negative, we will use x, y as texture coordinates
};

inline Vector3 LerpPosition(Vector3 a, Vector3 b, float t)
{
	return a + (b - a) * t;
}

inline X::Color LerpColor(X::Color a, X::Color b, float t)
{
	return a + (b - a) * t;
}

inline Vertex LerpVertex(Vertex a, Vertex b, float t)
{
	return { LerpPosition(a.pos, b.pos, t), LerpColor(a.color, b.color, t) };
}