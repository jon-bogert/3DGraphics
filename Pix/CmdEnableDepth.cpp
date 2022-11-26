#include "CmdEnableDepth.h"
#include "DepthBuffer.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
        return false;

    if (params[0] == "true" || params[0] == "True")
        DepthBuffer::Get()->SetEnabled(true);
    else
        DepthBuffer::Get()->SetEnabled(false);

    return true;
}
