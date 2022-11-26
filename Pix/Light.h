#pragma once
#include "Vector3.h"
#include <XEngine.h>

class Light
{
protected:
	X::Color mAmbient = {0.f, 0.f, 0.f, 1.f};
	X::Color mDiffuse = { 0.5f, 0.5f, 0.5f, 1.f };
	X::Color mSpecular = { 1.f, 1.f, 1.f, 1.f };

public:
	virtual ~Light() = default;
	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const = 0;

	void SetAmbient(const X::Color& ambient);
	void SetDiffuse(const X::Color& diffuse);
	void SetSpecular(const X::Color& specular);
};

