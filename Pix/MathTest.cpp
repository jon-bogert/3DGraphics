#include "MathTest.h"

#include <XEngine.h>

namespace
{
	bool Check(float value, float expected)
	{
		return fabs(value - expected) < 0.001f;
	}

	bool Check(Vector2 value, Vector2 expected)
	{
		return
			Check(value.x, expected.x) &&
			Check(value.y, expected.y);
	}

	bool Check(Vector3 value, Vector3 expected)
	{
		return
			Check(value.x, expected.x) &&
			Check(value.y, expected.y) &&
			Check(value.z, expected.z);
	}

	bool Check(Matrix4 value, Matrix4 expected)
	{
		return
			Check(value._11, expected._11) &&
			Check(value._12, expected._12) &&
			Check(value._13, expected._13) &&
			Check(value._14, expected._14) &&
			Check(value._21, expected._21) &&
			Check(value._22, expected._22) &&
			Check(value._23, expected._23) &&
			Check(value._24, expected._24) &&
			Check(value._31, expected._31) &&
			Check(value._32, expected._32) &&
			Check(value._33, expected._33) &&
			Check(value._34, expected._34) &&
			Check(value._41, expected._41) &&
			Check(value._42, expected._42) &&
			Check(value._43, expected._43) &&
			Check(value._44, expected._44);
	}
}

void TestVector3()
{
	XASSERT(Check(MagnitudeSquared({ 1.0f, 1.0f }), 2.0f), "MagnitudeSquared failed.");
	XASSERT(Check(MagnitudeSquared({ 1.0f, 2.0f, 3.0f }), 14.0f), "MagnitudeSquared failed.");
	XASSERT(Check(Magnitude({ 2.0f, 3.0f }), 3.605f), "Magnitude failed.");
	XASSERT(Check(Magnitude({ 2.0f, 3.0f, 4.0f }), 5.385f), "Magnitude failed.");
	XASSERT(Check(Normalize({ 2.0f, 6.0f }), { 0.316f, 0.948f }), "Normalize failed.");
	XASSERT(Check(Normalize({ 1.0f, 2.0f, 3.0f }), { 0.267f, 0.534f, 0.801f }), "Normalize failed.");
	XASSERT(Check(Dot({ 1.0f, 0.0f }, { 0.0f, 1.0f }), 0.0f), "Dot failed");
	XASSERT(Check(Dot({ 1.0f, 2.0f }, { 3.0f, 1.0f }), 5.0f), "Dot failed");
	XASSERT(Check(Dot({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }), 0.0f), "Dot failed");
	XASSERT(Check(Dot({ 1.0f, 0.5f, 0.7f }, { 0.5f, 1.0f, 0.7f }), 1.490f), "Dot failed");
	XASSERT(Check(Cross({ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }), { 0.0f, 0.0f, 1.0f }), "Cross failed");
	XASSERT(Check(Cross({ 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }), { 1.0f, 0.0f, 0.0f }), "Cross failed");
	XASSERT(Check(Cross({ 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }), { 0.0f, 1.0f, 0.0f }), "Cross failed");
}

void TestMatrix4()
{
	XASSERT(Check(
		Matrix4::Identity(),
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }),
		"Identity failed.");

	XASSERT(Check(
		Matrix4::RotationX(0.47f),
		{ 1, 0, 0, 0, 0, cos(0.47f), sin(0.47f), 0, 0, -sin(0.47f), cos(0.47f), 0, 0, 0, 0, 1 }),
		"RotationX failed.");

	XASSERT(Check(
		Matrix4::RotationY(0.33f),
		{ cos(0.33f), 0, -sin(0.33f), 0, 0, 1, 0, 0, sin(0.33f), 0, cos(0.33f), 0, 0, 0, 0, 1 }),
		"RotationY failed.");

	XASSERT(Check(
		Matrix4::RotationZ(0.26f),
		{ cos(0.26f), sin(0.26f), 0, 0, -sin(0.26f), cos(0.26f), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }),
		"RotationZ failed.");

	XASSERT(Check(
		Matrix4::Scaling(0.77f),
		{ 0.77f, 0, 0, 0, 0, 0.77f, 0, 0, 0, 0, 0.77f, 0, 0, 0, 0, 1 }),
		"Scaling failed.");

	XASSERT(Check(
		Matrix4::Scaling({ 1.2f, 2.3f, 3.4f }),
		{ 1.2f, 0, 0, 0, 0, 2.3f, 0, 0, 0, 0, 3.4f, 0, 0, 0, 0, 1 }),
		"Scaling failed.");

	XASSERT(Check(
		Matrix4::Translation({ 1.2f, 2.3f, 3.4f }),
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1.2f, 2.3f, 3.4f, 1 }),
		"Translation failed.");

	XASSERT(Check(
		Matrix4::Translation({ 2.2f, 3.3f, 4.4f }),
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2.2f, 3.3f, 4.4f, 1 }),
		"Translation failed.");

	XASSERT(Check(
		TransformCoord({ 0, 1, 0 }, Matrix4::RotationX(1.57f) * Matrix4::Translation({ 1, 0, 1 })),
		{ 1, 0, 2 }),
		"TransformCoord failed");

	XASSERT(Check(
		TransformNormal({ 0, 1, 0 }, Matrix4::RotationZ(1.57f) * Matrix4::Translation({ 1, 0, 1 })),
		{ -1, 0, 0 }),
		"TransformNormal failed");

	XASSERT(Check(
		Determinant({ 1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3 }),
		23.0f),
		"Determinant failed.");

	XASSERT(Check(
		Adjoint({ 1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3 }),
		{ -41, 22, 20, -15, -15, 3, 9, -1, 22, -9, -4, 3, 5, -1, -3, 8 }),
		"Adjoint failed");

	XASSERT(Check(
		Transpose({ 1, -1, 2, 1, 2, -3, 1, 3, 1, 2, 3, 1, 0, 1, 0, 3 }),
		{ 1, 2, 1, 0, -1, -3, 2, 1, 2, 1, 3, 0, 1, 3, 1, 3 }),
		"Transpose failed.");

	XASSERT(Check(
		Inverse({ 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 2, -5, 8, 1 }),
		{ 0, -1, 0, 0, 1, 0, 0, 0, 0.625f, 0.25f, -0.125f, 0.125f, 0, 0, 1, 0 }),
		"Inverse failed.");
}