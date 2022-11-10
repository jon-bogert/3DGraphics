#include "CmdSetCameraPosition.h"
#include "Camera.h"
#include "VariableCache.h"

bool CmdSetCameraPosition::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 3)
        return false;
    float x = VariableCache::Get()->GetFloat(params[0]);
    float y = VariableCache::Get()->GetFloat(params[1]);
    float z = VariableCache::Get()->GetFloat(params[2]);

    Camera::Get()->SetPosition({ x, y, z });
}
