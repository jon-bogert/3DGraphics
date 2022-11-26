#pragma once
#include <ostream>

struct Vector3
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	Vector3() {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	virtual ~Vector3() = default;

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v3)
	{
		os << '[' << v3.x << ", " << v3.y << ", " << v3.z << ']';
		return os;
	}

	Vector3 operator+(const Vector3& other)
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	Vector3 operator-(const Vector3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector3 operator*(const float& c)
	{
		return { x * c, y * c, z * c };
	}

	Vector3 operator/(const float& c)
	{
		if (c == 0)
		{
			return Vector3();
		}
		return { x / c, y / c, z / c };
	}

	bool operator==(const Vector3& other)
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}
};