#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	X::Color ComputeLightColor(Vector3 position, Vector3 normal) const override;

	void SetDirection(Vector3 direction);

protected:
	Vector3 mDirection;
};