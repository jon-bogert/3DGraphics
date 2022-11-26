#pragma once
#include "Light.h"
class PointLight : public Light
{
	Vector3 mPosition{};
	float mAttenConst;
	float mAttenLin;
	float mAttenQuad;

public:
	PointLight() = default;
	virtual ~PointLight() = default;
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetAmbient(const X::Color& ambient);
	void SetDiffuse(const X::Color& diffuse);
	void SetSpecular(const X::Color& specular);

	void SetPosition(const Vector3& direction);
	void SetAttenuation(float constant, float linear, float quadratic);
};

