#include "CmdShowViewport.h"
#include "Viewport.h"

bool CmdShowViewport::Execute(const std::vector<std::string>& params)
{
	bool setTo = false;
	if (params.size() > 0)
		if (params[0] == "true") setTo = true;

	Viewport::Get()->ShowViewport(setTo);
	return true;
}
