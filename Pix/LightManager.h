#pragma once
#include "Light.h"

class LightManager
{
	std::vector<std::shared_ptr<Light>> mLights;
	X::Color mAmbient = { 0.2f, 0.2f, 0.2f, 1.f };
	X::Color mDiffuse = { 0.5f, 0.5f, 0.5f, 1.f };
	X::Color mSpecular = { 0.9f, 0.9f, 0.9f, 1.f };

	LightManager() {}

public:
	static LightManager* Get();

	~LightManager() {}

	void OnNewFrame();

	void AddDirectionalLight(const Vector3& direction);
	void AddPointLight(const Vector3& position, float constant = 1.f, float linear = 0.5f, float quad = 0.f);

	void SetLightingAmbient(const X::Color& ambient);
	void SetLightingDiffuse(const X::Color& diffuse);
	void SetLightingSpecular(const X::Color& specular);

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const;

};

