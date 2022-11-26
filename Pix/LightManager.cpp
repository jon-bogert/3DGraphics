#include "LightManager.h"
#include "DirectionalLight.h"
#include "PointLight.h"

LightManager* LightManager::Get()
{
    static LightManager instance;
    return &instance;
}

void LightManager::OnNewFrame()
{
    mLights.clear();
}

void LightManager::AddDirectionalLight(const Vector3& direction)
{
    auto light = std::make_shared<DirectionalLight>();
    light->SetDirection(direction);
    light->SetAmbient(mAmbient);
    light->SetDiffuse(mDiffuse);
    light->SetSpecular(mSpecular);
    mLights.emplace_back(std::move(light));
}

void LightManager::AddPointLight(const Vector3& position, float constant, float linear, float quad)
{
    auto light = std::make_shared<PointLight>();
    light->SetPosition(position);
    light->SetAttenuation(constant, linear, quad);
    light->SetAmbient(mAmbient);
    light->SetDiffuse(mDiffuse);
    light->SetSpecular(mSpecular);
    mLights.emplace_back(std::move(light));
}

void LightManager::SetLightingAmbient(const X::Color& ambient)
{
    mAmbient = ambient;
}

void LightManager::SetLightingDiffuse(const X::Color& diffuse)
{
    mDiffuse = diffuse;
}

void LightManager::SetLightingSpecular(const X::Color& specular)
{
    mSpecular = specular;
}

X::Color LightManager::ComputeLightColor(const Vector3& position, const Vector3& normal) const
{
    if (mLights.empty())
        return X::Colors::White;

    X::Color color;
    for (auto& light : mLights)
        color += light->ComputeLightColor(position, normal);

    return color;
}
