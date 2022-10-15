#pragma once
#include <ostream>


struct Vector2
{
	float x = 0.f;
	float y = 0.f;

	Vector2() {}
	Vector2(float x, float y) : x(x), y(y) {}
	virtual ~Vector2() = default;

	friend std::ostream& operator<<(std::ostream& os, const Vector2& v2)
	{
		os << '[' << v2.x << ", " << v2.y << ']';
		return os;
	}

	Vector2 operator+(const Vector2& other)
	{
		return { x + other.x, y + other.y };
	}

	Vector2 operator-(const Vector2& other)
	{
		return { x - other.x, y - other.y };
	}

	Vector2 operator*(const float& c)
	{
		return { x * c, y * c };
	}

	Vector2 operator/(const float& c)
	{
		if (c == 0)
		{
			return Vector2();
		}
		return { x / c, y / c };
	}
};