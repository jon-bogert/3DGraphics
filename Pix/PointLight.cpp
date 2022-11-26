#include "PointLight.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "MathHelper.h"

X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	Camera* cam = Camera::Get();
	MaterialManager* matMangr = MaterialManager::Get();

	Vector3 dirToLight = mPosition - position;
	float distToLight = MathHelper::Magnitude(dirToLight);
	dirToLight = dirToLight / distToLight; // normalizing

	float atten = 1.f / (mAttenConst + (mAttenLin * distToLight) + (mAttenQuad * distToLight * distToLight));
	float attenValue = X::Math::Clamp(atten, 0.f, 1.f);

	X::Color colorAmbient = mAmbient * matMangr->GetMaterialAmbient() * atten;
	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDiffuse = mDiffuse * matMangr->GetMaterialDiffuse() * X::Math::Max(dot, 0.0f) * attenValue;

	Vector3 dirToCam = cam->GetPosition();
	Vector3 half = MathHelper::Normalize(dirToLight + dirToCam);
	float fallOff = powf(MathHelper::Dot(half, normal), matMangr->GetMaterialShininess());
	X::Color colorSpecular = mSpecular * matMangr->GetMaterialSpecular() * X::Math::Max(fallOff, 0.f) * attenValue;

	return colorAmbient + colorDiffuse + colorSpecular;
}

void PointLight::SetAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}

void PointLight::SetDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}

void PointLight::SetSpecular(const X::Color& specular)
{
	mSpecular = specular;
}

void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	mAttenConst = constant;
	mAttenLin = linear;
	mAttenQuad = quadratic;
}

