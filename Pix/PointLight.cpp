#include "PointLight.h"

#include "Camera.h"
#include "MaterialManager.h"

X::Color PointLight::ComputeLightColor(Vector3 position, Vector3 normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	auto dirToLight = mPosition - position;
	auto distanceToLight = Magnitude(dirToLight);
	dirToLight /= distanceToLight;

	float atten = 1.0f / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuadratic * distanceToLight * distanceToLight));
	float i = X::Math::Clamp(atten, 0.0f, 1.0f);

	X::Color ca = mAmbient * mm->GetMaterialAmbient() * i;
	
	float id = Dot(dirToLight, normal);
	X::Color cd = mDiffuse * mm->GetMaterialDiffuse() * X::Math::Max(id, 0.0f) * i;

	auto dirToEye = cam->GetPosition();
	auto half = Normalize(dirToLight + dirToEye);
	float is = pow(Dot(half, normal), mm->GetMaterialShininess());
	X::Color cs = mSpecular * mm->GetMaterialSpecular() * X::Math::Max(is, 0.0f) * i;

	return ca + cd + cs;
}

void PointLight::SetPosition(Vector3 position)
{
	mPosition = position;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLinear = linear;
	mAttenQuadratic = quadratic;
}
