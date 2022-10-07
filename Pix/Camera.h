#pragma once

#include "MathHelper.h"

class Camera
{
public:
	static Camera* Get();

public:
	void OnNewFrame();

	void SetPosition(Vector3 position);
	void SetDirection(Vector3 direction);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float fov);

	Vector3 GetPosition() const;
	Vector3 GetDirection() const;

	Matrix4 GetViewMatrix() const;
	Matrix4 GetProjectionMatrix() const;

private:
	Vector3 mPosition;
	Vector3 mDirection;
	float mNearPlane;
	float mFarPlane;
	float mFOV;
};