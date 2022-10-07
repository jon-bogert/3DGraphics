#pragma once

#include "MathHelper.h"
#include <XEngine.h>

class Light
{
public:
	virtual ~Light() = default;

	virtual X::Color ComputeLightColor(Vector3 position, Vector3 normal) const = 0;

	void SetAmbient(X::Color ambient);
	void SetDiffuse(X::Color diffuse);
	void SetSpecular(X::Color specular);

protected:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};