#include "CmdVertex.h"
#include "PrimativeManager.h"
#include "Rasterizer.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 2)
        return false;

    Vertex vert;
    vert.color = Rasterizer::Get()->GetColor();
    vert.position.x = std::stoi(params[0]);
    vert.position.y = std::stoi(params[1]);
    if (params.size() == 5)
    {
        vert.color.r = std::stof(params[2]);
        vert.color.g = std::stof(params[3]);
        vert.color.b = std::stof(params[4]);

        if (vert.color.r > 1.f) vert.color.r /= 255;
        if (vert.color.g > 1.f) vert.color.g /= 255;
        if (vert.color.b > 1.f) vert.color.b /= 255;
    }
    else
    {
        if (params.size() >= 3)
        {
            vert.position.z = std::stoi(params[2]);
        }
        if (params.size() >= 6)
        {
            vert.color.r = std::stof(params[3]);
            vert.color.g = std::stof(params[4]);
            vert.color.b = std::stof(params[5]);
            if (params.size() >= 7)
                vert.color.a = std::stof(params[6]);

            if (vert.color.r > 1.f) vert.color.r /= 255;
            if (vert.color.g > 1.f) vert.color.g /= 255;
            if (vert.color.b > 1.f) vert.color.b /= 255;
            if (vert.color.a > 1.f) vert.color.a /= 255;
        }
    }
    PrimativeManager::Get()->AddVertex(vert);
    return true;
}
