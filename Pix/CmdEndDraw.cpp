#include "CmdEndDraw.h"
#include "PrimativeManager.h"

bool CmdEndDraw::Execute(const std::vector<std::string>& params)
{
	return PrimativeManager::Get()->EndDraw();
}
