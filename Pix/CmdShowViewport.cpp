#include "CmdShowViewport.h"

#include "VariableCache.h"
#include "Viewport.h"

bool CmdShowViewport::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as on or off
	if (params.empty())
		return false;

	const auto vc = VariableCache::Get();
	const bool show = vc->GetBool(params[0]);

	// Show viewport
	Viewport::Get()->ShowViewport(show);
	return true;
}
