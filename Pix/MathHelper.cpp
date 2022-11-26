#include "MathHelper.h"
#include "Vector2.h"
#include "Vector3.h"
#include <math.h>

#define PI 3.14169f

float MathHelper::MagnitudeSquared(const Vector2& v)
{
	return powf(v.x, 2.f) + powf(v.y, 2.f);
}
float MathHelper::MagnitudeSquared(const Vector3& v)
{
	return powf(v.x, 2.f) + powf(v.y, 2.f) + powf(v.z, 2.f);
}
float MathHelper::Magnitude(const Vector2& v)
{
	return sqrtf(MagnitudeSquared(v));
}
float MathHelper::Magnitude(const Vector3& v)
{
	return sqrtf(MagnitudeSquared(v));
}
Vector2 MathHelper::Normalize(const Vector2& v)
{
	float mag = Magnitude(v);
	return { v.x / mag, v.y / mag };
}
Vector3 MathHelper::Normalize(const Vector3& v)
{
	float mag = Magnitude(v);
	return { v.x / mag, v.y / mag , v.z / mag };
}
float MathHelper::Dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}
float MathHelper::Dot(const Vector3& a, const Vector3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b)
{
	return {
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y
	};
}

Vector3 MathHelper::TransformCoord(Vector3 v, Matrix4 m)
{
	const float w = ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + m._44);
	const float invW = (w == 0.0f) ? 1.f : 1 / w;
	return {
		((m._11 * v.x) + (m._21 * v.y) + (m._31 * v.z) + m._41) * invW,
		((m._12 * v.x) + (m._22 * v.y) + (m._32 * v.z) + m._42) * invW,
		((m._13 * v.x) + (m._23 * v.y) + (m._33 * v.z) + m._43) * invW
	};
}

Vector3 MathHelper::TransformNormal(Vector3 v, Matrix4 m)
{
	return {
		(m._11 * v.x) + (m._21 * v.y) + (m._31 * v.z),
		(m._12 * v.x) + (m._22 * v.y) + (m._32 * v.z),
		(m._13 * v.x) + (m._23 * v.y) + (m._33 * v.z)
	};
}

float MathHelper::Determinant(Matrix4 m)
{
	float result = 0.0f;
	result += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	result -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	result += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	result -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return result;
}

Matrix4 MathHelper::Adjoint(Matrix4 m)
{
	return {
		+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	};
}

Matrix4 MathHelper::Transpose(Matrix4 m)
{
	return {
			m._11, m._21, m._31, m._41,
			m._12, m._22, m._32, m._42,
			m._13, m._23, m._33, m._43,
			m._14, m._24, m._34, m._44,
	};
}

Matrix4 MathHelper::Inverse(Matrix4 m)
{
	float det = Determinant(m);
	float iDet = 1.0f / det;
	return Adjoint(m) * iDet;
}

float MathHelper::Deg2Rad(float deg)
{
	return (deg * (PI/180.f));
}

float MathHelper::Rad2Deg(float rad)
{
	return (rad * (180.f/PI));
}

bool MathHelper::CheckEquals(float a, float b)
{
	return fabs(a - b) < 0.001f;
}

bool MathHelper::CheckEquals(const Vector3& a, const Vector3& b)
{
	return fabs(a.x - b.x) < 0.001f && fabs(a.y - b.y) < 0.001f;
}

bool MathHelper::CheckEquals(const Matrix4& a, const Matrix4& b)
{
	return
		fabs(a._11 - b._11) < 0.001f && fabs(a._12 - b._12) < 0.001f && fabs(a._13 - b._13) < 0.001f && fabs(a._14 - b._14) < 0.001f &&
		fabs(a._21 - b._21) < 0.001f && fabs(a._22 - b._22) < 0.001f && fabs(a._23 - b._23) < 0.001f && fabs(a._24 - b._24) < 0.001f &&
		fabs(a._31 - b._31) < 0.001f && fabs(a._32 - b._32) < 0.001f && fabs(a._33 - b._33) < 0.001f && fabs(a._34 - b._34) < 0.001f &&
		fabs(a._41 - b._41) < 0.001f && fabs(a._42 - b._42) < 0.001f && fabs(a._43 - b._43) < 0.001f && fabs(a._44 - b._44) < 0.001f;
}
