#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

struct Vector2;
struct Vector3;

class MathHelper
{
public:
	static float MagnitudeSquared(const Vector2& v);
	static float MagnitudeSquared(const Vector3& v);
	static float Magnitude(const Vector2& v);
	static float Magnitude(const Vector3& v);
	static Vector2 Normalize(const Vector2& v);
	static Vector3 Normalize(const Vector3& v);
	static float Dot(const Vector2& a, const Vector2& b);
	static float Dot(const Vector3& a, const Vector3& b);
	static Vector3 Cross(const Vector3& a, const Vector3& b);

	static Vector3 TransformCoord(Vector3 v, Matrix4 m);			// assume w = 1
	static Vector3 TransformNormal(Vector3 v, Matrix4 m);			// assume w = 0
	static float Determinant(Matrix4 m);
	static Matrix4 Adjoint(Matrix4 m);
	static Matrix4 Transpose(Matrix4 m);
	static Matrix4 Inverse(Matrix4 m);

	static float Deg2Rad(float deg);
	static float Rad2Deg(float rad);

	static bool CheckEquals(float a, float b);
	static bool CheckEquals(const Vector3& a, const Vector3& b);
	static bool CheckEquals(const Matrix4& a, const Matrix4& b);
};