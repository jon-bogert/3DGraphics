#include "CmdBeginDraw.h"
#include "PrimativeManager.h"

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
    Topology top = Topology::Point;
    bool applyTransform = false;
    if (params.size() >= 1)
    {
        if (params[0] == "line" || params[0] == "Line")
            top = Topology::Line;
        else if (params[0] == "triangle" || params[0] == "Triangle"
            || params[0] == "tri" || params[0] == "Tri")
            top = Topology::Triangle;
        //else stay as Topology::Point;

        if (params.size() >= 2 && params[1] == "true")
            applyTransform = true;
    }

    return PrimativeManager::Get()->BeginDraw(top, applyTransform);
}
