#include "SpotLight.h"

#include "Camera.h"
#include "MaterialManager.h"

X::Color SpotLight::ComputeLightColor(Vector3 position, Vector3 normal) const
{
	auto cam = Camera::Get();
	auto mm = MaterialManager::Get();

	auto dirToLight = mPosition - position;
	auto distanceToLight = Magnitude(dirToLight);
	dirToLight /= distanceToLight;

	auto lightDir = -dirToLight;
	auto dirDot = Dot(lightDir, mDirection);
	if (dirDot < mCosAngle)
		return 0.0f;

	float spot = pow(dirDot, mDecay);
	float i = spot / (mAttenConst + (mAttenLinear * distanceToLight) + (mAttenQuadratic * distanceToLight * distanceToLight));

	X::Color ca = mAmbient * mm->GetMaterialAmbient();
	
	float id = Dot(dirToLight, normal);
	X::Color cd = mDiffuse * mm->GetMaterialDiffuse() * X::Math::Max(id, 0.0f);

	auto dirToEye = cam->GetPosition();
	auto half = Normalize(dirToLight + dirToEye);
	float is = pow(Dot(half, normal), mm->GetMaterialShininess());
	X::Color cs = mSpecular * mm->GetMaterialSpecular() * X::Math::Max(is, 0.0f);

	X::Color final = ca + cd + cs;
	final.r = X::Math::Clamp(final.r, 0.0f, 1.0f);
	final.g = X::Math::Clamp(final.g, 0.0f, 1.0f);
	final.b = X::Math::Clamp(final.b, 0.0f, 1.0f);
	return final * i;
}

void SpotLight::SetPosition(Vector3 position)
{
	mPosition = position;
}

void SpotLight::SetDirection(Vector3 direction)
{
	mDirection = Normalize(direction);
}

void SpotLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLinear = linear;
	mAttenQuadratic = quadratic;
}

void SpotLight::SetAngle(float radian)
{
	mCosAngle = cos(radian);
}

void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}