#include "DirectionalLight.h"

#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(Vector3 position, Vector3 normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	X::Color ca = mAmbient * mm->GetMaterialAmbient();
	
	auto dirToLight = -mDirection;
	float id = Dot(dirToLight, normal);
	X::Color cd = mDiffuse * mm->GetMaterialDiffuse() * X::Math::Max(id, 0.0f);

	auto dirToEye = cam->GetPosition();
	auto half = Normalize(dirToLight + dirToEye);
	float is = pow(Dot(half, normal), mm->GetMaterialShininess());
	X::Color cs = mSpecular * mm->GetMaterialSpecular() * X::Math::Max(is, 0.0f);

	return ca + cd + cs;
}

void DirectionalLight::SetDirection(Vector3 direction)
{
	mDirection = Normalize(direction);
}
