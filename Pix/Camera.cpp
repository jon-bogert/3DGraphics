#include "Camera.h"
#include "MathHelper.h"

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera instance;
	return &instance;
}

void Camera::OnNewFrame()
{
	mPosition = { 0.f, 0.f, 0.f };
	mDirection = { 0.f, 0.f, 1.f };
	mNearPlane = 0.01f;
	mFarPlane = 100.f;
	mFOV = 1.57f;
}

void Camera::SetPosition(const Vector3 pos)
{
	mPosition = pos;
}

void Camera::SetDirection(const Vector3 dir)
{
	mDirection = dir;
}

void Camera::SetNearPlane(const float nPlane)
{
	mNearPlane = nPlane;
}

void Camera::SetFarPlane(const float fPlane)
{
	mFarPlane = fPlane;
}

void Camera::SetFOV(const float fov)
{
	mFOV = fov;
}

Matrix4 Camera::GetViewMatrix() const
{
	const Vector3 l = mDirection;
	const Vector3 r = MathHelper::Normalize(MathHelper::Cross({ 0.0f, 1.0f, 0.0f }, l));
	const Vector3 u = MathHelper::Normalize(MathHelper::Cross(l, r));
	const float dx = -MathHelper::Dot(r, mPosition);
	const float dy = -MathHelper::Dot(u, mPosition);
	const float dz = -MathHelper::Dot(l, mPosition);
	return{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		dx,  dy,  dz,  1.0f
	};
}

Matrix4 Camera::GetProjectionMatrix() const
{
	const float aspect = gResolutionX / gResolutionY;
	const float h = 1 / tan(mFOV * 0.5f);
	const float w = h / aspect;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float d = zf / (zf - zn);

	return{
		w,		0.f,	0.f,	0.f,
		0.f,	h,		0.f,	0.f,
		0.f,	0.f,	d,		1.f,
		0.f,	0.f,	-zn * d, 0.f
	};
}