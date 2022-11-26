#pragma once
#include "Matrix4.h"

class Camera
{
	Vector3 mPosition = { 0.f, 0.f, 0.f };
	Vector3 mDirection = { 0.f, 0.f, 1.f };
	float mNearPlane = 0.01f;
	float mFarPlane = 100.f;
	float mFOV = 1.57f;

public:
	static Camera* Get();

private:
	Camera() {}

public:
	void OnNewFrame();

	void SetPosition(const Vector3 pos);
	void SetDirection(const Vector3 dir);
	void SetNearPlane(const float nPlane);
	void SetFarPlane(const float fPlane);
	void SetFOV(const float fov);

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;
	
	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetDirection() const { return mDirection; }
};

