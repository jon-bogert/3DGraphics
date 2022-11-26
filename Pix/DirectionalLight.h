#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
	Vector3 mDirection{};

public:
	DirectionalLight() = default;
	virtual ~DirectionalLight() = default;
	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const override;

	void SetAmbient(const X::Color& ambient);
	void SetDiffuse(const X::Color& diffuse);
	void SetSpecular(const X::Color& specular);

	void SetDirection(const Vector3& direction);
};