#pragma once
#include "Vector3.h"

struct Matrix4
{
	float	_11 = 0.f, _12 = 0.f, _13 = 0.f, _14 = 0.f,
			_21 = 0.f, _22 = 0.f, _23 = 0.f, _24 = 0.f,
			_31 = 0.f, _32 = 0.f, _33 = 0.f, _34 = 0.f,
			_41 = 0.f, _42 = 0.f, _43 = 0.f, _44 = 0.f;

	Matrix4 operator+(const Matrix4& other)
	{
		return {
			_11 + other._12, _12 + other._12, _13 + other._13, _14 + other._14,
			_21 + other._22, _22 + other._22, _23 + other._23, _24 + other._24,
			_31 + other._33, _32 + other._32, _33 + other._33, _34 + other._34,
			_41 + other._44, _42 + other._42, _43 + other._43, _44 + other._44,
		};
	}
	Matrix4 operator*(const float& s)
	{
		return {
			_11 * s, _12 * s, _13 * s, _14 * s,
			_21 * s, _22 * s, _23 * s, _24 * s,
			_31 * s, _32 * s, _33 * s, _34 * s,
			_41 * s, _42 * s, _43 * s, _44 * s,
		};
	}
	Matrix4 operator*(const Matrix4& other)
	{
		return {
			(_11 * other._11) + (_12 * other._21) + (_13 * other._31) + (_14 * other._41),
			(_11 * other._12) + (_12 * other._22) + (_13 * other._32) + (_14 * other._42), 
			(_11 * other._13) + (_12 * other._23) + (_13 * other._33) + (_14 * other._43),
			(_11 * other._14) + (_12 * other._24) + (_13 * other._34) + (_14 * other._44),

			(_21 * other._11) + (_22 * other._21) + (_23 * other._31) + (_24 * other._41),
			(_21 * other._12) + (_22 * other._22) + (_23 * other._32) + (_24 * other._42),
			(_21 * other._13) + (_22 * other._23) + (_23 * other._33) + (_24 * other._43),
			(_21 * other._14) + (_22 * other._24) + (_23 * other._34) + (_24 * other._44),

			(_31 * other._11) + (_32 * other._21) + (_33 * other._31) + (_34 * other._41),
			(_31 * other._12) + (_32 * other._22) + (_33 * other._32) + (_34 * other._42),
			(_31 * other._13) + (_32 * other._23) + (_33 * other._33) + (_34 * other._43),
			(_31 * other._14) + (_32 * other._24) + (_33 * other._34) + (_34 * other._44),

			(_41 * other._11) + (_42 * other._21) + (_43 * other._31) + (_44 * other._41),
			(_41 * other._12) + (_42 * other._22) + (_43 * other._32) + (_44 * other._42),
			(_41 * other._13) + (_42 * other._23) + (_43 * other._33) + (_44 * other._43),
			(_41 * other._14) + (_42 * other._24) + (_43 * other._34) + (_44 * other._44)
		};
	}

	static Matrix4 Identity()
	{
		return{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}
	static Matrix4 RotationX(float rad)
	{
		return {

			1.f,		0.f,		0.f,		0.f,
			0.f,		cosf(rad),	sinf(rad),	0.f,
			0.f,		-sinf(rad),	cosf(rad),	0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}
	static Matrix4 RotationY(float rad)
	{
		return {
			cosf(rad),	0.f,		-sinf(rad),	0.f,
			0.f,		1.f,		0.f,		0.f,
			sinf(rad),	0.f,		cosf(rad),	0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}
	static Matrix4 RotationZ(float rad)
	{
		return {
			cosf(rad),	sinf(rad),	0.f,		0.f,
			-sinf(rad),	cosf(rad),	0.f,		0.f,
			0.f,		0.f,		1.f,		0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}
	static Matrix4 Scaling(float s)
	{
		return{
			s,		0.f,	0.f,	0.f,
			0.f,	s,		0.f,	0.f,
			0.f,	0.f,	s,		0.f,
			0.f,	0.f,	0.f,	s
		};
	}
	static Matrix4 Scaling(Vector3 s)
	{
		return{
			s.x,	0.f,	0.f,	0.f,
			0.f,	s.y,	0.f,	0.f,
			0.f,	0.f,	s.z,	0.f,
			0.f,	0.f,	0.f,	1.f
		};
	}
	static Matrix4 Scaling(float sx, float sy, float sz)
	{
		return{
			sx,		0.f,	0.f,	0.f,
			0.f,	sy,		0.f,	0.f,
			0.f,	0.f,	sz,		0.f,
			0.f,	0.f,	0.f,	1.f
		};
	}
	static Matrix4 Translation(Vector3 d)
	{
		return{
			1.f,	0.f,	0.f,	0.f,
			0.f,	1.f,	0.f,	0.f,
			0.f,	0.f,	1.f,	0.f,
			d.x,	d.y,	d.z,	1.f
		};
	}
	static Matrix4 Translation(float dx, float dy, float dz)
	{
		return{
			1.f,	0.f,	0.f,	0.f,
			0.f,	1.f,	0.f,	0.f,
			0.f,	0.f,	1.f,	0.f,
			dx,		dy,		dz,		1.f
		};
	}
};