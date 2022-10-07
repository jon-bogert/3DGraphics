#pragma once

#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

public:
	void OnNewFrame();

	void AddDirectionalLight(Vector3 direction);
	void AddPointLight(Vector3 position, float constant, float linear, float quadratic);
	void AddSpotLight(Vector3 position, Vector3 direction, float constant, float linear, float quadratic, float angle, float decay);

	void SetLightAmbient(X::Color ambient);
	void SetLightDiffuse(X::Color diffuse);
	void SetLightSpecular(X::Color specular);

	X::Color ComputeLightColor(Vector3 position, Vector3 normal) const;

private:
	std::vector<std::unique_ptr<Light>> mLights;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};