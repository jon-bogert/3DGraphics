#include "CmdLights.h"
#include "LightManager.h"
#include "VariableCache.h"

bool CmdSetLightAmbient::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float red = VariableCache::Get()->GetFloat(params[0]);
	float green = VariableCache::Get()->GetFloat(params[1]);
	float blue = VariableCache::Get()->GetFloat(params[2]);

	float alpha = 1.f;
	if (params.size() >= 4)
		alpha = VariableCache::Get()->GetFloat(params[3]);

	if (red > 1.f) red /= 255;
	if (green > 1.f) green /= 255;
	if (blue > 1.f) blue /= 255;
	if (alpha > 1.f) alpha /= 255;

	// Draw the pixel
	LightManager::Get()->SetLightingAmbient({ red, green, blue, alpha });
	return true;
}

bool CmdSetLightDiffuse::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float red = VariableCache::Get()->GetFloat(params[0]);
	float green = VariableCache::Get()->GetFloat(params[1]);
	float blue = VariableCache::Get()->GetFloat(params[2]);

	float alpha = 1.f;
	if (params.size() >= 4)
		alpha = VariableCache::Get()->GetFloat(params[3]);

	if (red > 1.f) red /= 255;
	if (green > 1.f) green /= 255;
	if (blue > 1.f) blue /= 255;
	if (alpha > 1.f) alpha /= 255;

	// Draw the pixel
	LightManager::Get()->SetLightingDiffuse({ red, green, blue, alpha });
	return true;
}

bool CmdSetLightSpecular::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float red = VariableCache::Get()->GetFloat(params[0]);
	float green = VariableCache::Get()->GetFloat(params[1]);
	float blue = VariableCache::Get()->GetFloat(params[2]);

	float alpha = 1.f;
	if (params.size() >= 4)
		alpha = VariableCache::Get()->GetFloat(params[3]);

	if (red > 1.f) red /= 255;
	if (green > 1.f) green /= 255;
	if (blue > 1.f) blue /= 255;
	if (alpha > 1.f) alpha /= 255;

	// Draw the pixel
	LightManager::Get()->SetLightingSpecular({ red, green, blue, alpha });
	return true;
}

bool CmdAddDirectionalLight::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for x, y, z
	if (params.size() < 3)
		return false;

	float x = VariableCache::Get()->GetFloat(params[0]);
	float y = VariableCache::Get()->GetFloat(params[1]);
	float z = VariableCache::Get()->GetFloat(params[2]);

	LightManager::Get()->AddDirectionalLight({ x, y, z });
	return true;
}

bool CmdAddPointLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
		return false;

	Vector3 pos{
		VariableCache::Get()->GetFloat(params[0]),
		VariableCache::Get()->GetFloat(params[1]),
		VariableCache::Get()->GetFloat(params[2])
	};
	float constant = 1.f;
	float linear = 0.5f;
	float quad = 0.f;

	if (params.size() >= 6)
	{
		constant = VariableCache::Get()->GetFloat(params[3]);
		linear = VariableCache::Get()->GetFloat(params[4]);
		quad = VariableCache::Get()->GetFloat(params[5]);
	}
	LightManager::Get()->AddPointLight(pos, constant, linear, quad);
	return true;
}
