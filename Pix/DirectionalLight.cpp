#include "DirectionalLight.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "MathHelper.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
	Camera* cam = Camera::Get();
	MaterialManager* matMangr = MaterialManager::Get();
	X::Color colorAmbient = mAmbient * matMangr->GetMaterialAmbient();

	Vector3 dirToLight = { -mDirection.x, -mDirection.y, -mDirection.z };
	float dot = MathHelper::Dot(dirToLight, normal);
	X::Color colorDiffuse = mDiffuse * matMangr->GetMaterialDiffuse() * X::Math::Max(dot, 0.0f);

	Vector3 dirToCam = cam->GetPosition();
	Vector3 half = MathHelper::Normalize(dirToLight + dirToCam);
	float fallOff = powf(MathHelper::Dot(half, normal), matMangr->GetMaterialShininess());
	X::Color colorSpecular = mSpecular * matMangr->GetMaterialSpecular() * X::Math::Max(fallOff, 0.f);

	return colorAmbient + colorDiffuse + colorSpecular;
}

void DirectionalLight::SetAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}

void DirectionalLight::SetDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}

void DirectionalLight::SetSpecular(const X::Color& specular)
{
	mSpecular = specular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
	mDirection = direction;
}
