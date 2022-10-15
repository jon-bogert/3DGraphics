#include "MathHelper.h"
#include "Vector2.h"
#include "Vector3.h"
#include <math.h>


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
