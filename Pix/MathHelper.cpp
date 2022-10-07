#include "MathHelper.h"

#include <cmath>

Matrix4 Matrix4::Identity()
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::Translation(Vector3 d)
{
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		d.x,  d.y,  d.z,  1.0f
	};
}

Matrix4 Matrix4::RotationX(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c,    s,    0.0f,
		0.0f, -s,   c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::RotationY(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return {
		c,    0.0f, -s,   0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s,    0.0f, c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::RotationZ(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return {
		c,    s,    0.0f, 0.0f,
		-s,   c,    0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::Scaling(float s)
{
	return {
		s,    0.0f, 0.0f, 0.0f,
		0.0f, s,    0.0f, 0.0f,
		0.0f, 0.0f, s,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

Matrix4 Matrix4::Scaling(Vector3 s)
{
	return {
		s.x,  0.0f, 0.0f, 0.0f,
		0.0f, s.y,  0.0f, 0.0f,
		0.0f, 0.0f, s.z,  0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

float MagnitudeSquared(Vector2 v)
{
	return v.x * v.x + v.y * v.y;
}

float MagnitudeSquared(Vector3 v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float Dot(Vector2 a, Vector2 b)
{
	return a.x * b.x + a.y * b.y;
}

float Dot(Vector3 a, Vector3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Magnitude(Vector2 v)
{
	return sqrt(Dot(v, v));
}

float Magnitude(Vector3 v)
{
	return sqrt(Dot(v, v));
}

Vector2 Normalize(Vector2 v)
{
	float invMag = 1.0f / Magnitude(v);
	return v * invMag;
}

Vector3 Normalize(Vector3 v)
{
	float invMag = 1.0f / Magnitude(v);
	return v * invMag;
}

Vector3 Cross(Vector3 a, Vector3 b)
{
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float Determinant(const Matrix4& m)
{
	float det = 0.0f;
	det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}

Matrix4 Adjoint(const Matrix4& m)
{
	return
	{
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

Matrix4 Transpose(const Matrix4& m)
{
	return {
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	};
}

Matrix4 Inverse(const Matrix4& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}

Vector3 TransformCoord(const Vector3& v, const Matrix4& m)
{
	const float w = ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44));
	const float invW = (w == 0.0f) ? 1.0f : 1 / w;
	return {
		((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41)) * invW,
		((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42)) * invW,
		((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)) * invW
	};
}

Vector3 TransformNormal(const Vector3& v, const Matrix4& m)
{
	return {
		(v.x * m._11) + (v.y * m._21) + (v.z * m._31),
		(v.x * m._12) + (v.y * m._22) + (v.z * m._32),
		(v.x * m._13) + (v.y * m._23) + (v.z * m._33)
	};
}

bool Intersect(Ray ray, Sphere sphere, float& distance)
{
	Vector3 v = sphere.center - ray.origin;
	float t = Dot(v, ray.direction);

	Vector3 closestPoint = ray.origin + (ray.direction * t);
	float closestPointToCenterSqr = MagnitudeSquared(closestPoint - sphere.center);
	float radiusSqr = sphere.radius * sphere.radius;
	if (closestPointToCenterSqr > radiusSqr)
		return false;

	float oppositeSide = sqrt(radiusSqr - closestPointToCenterSqr);
	if (MagnitudeSquared(ray.origin - sphere.center) < radiusSqr)
		distance = t + oppositeSide;
	else
		distance = t - oppositeSide;
	return true;
}