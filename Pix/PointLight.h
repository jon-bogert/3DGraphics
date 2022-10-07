#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	X::Color ComputeLightColor(Vector3 position, Vector3 normal) const override;

	void SetPosition(Vector3 position);
	void SetAttenuation(float constant, float linear, float quadratic);

protected:
	Vector3 mPosition;
	float mAttenConst = 1.0f;
	float mAttenLinear = 0.0f;
	float mAttenQuadratic = 0.0f;
};