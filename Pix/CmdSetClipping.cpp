#include "CmdSetClipping.h"

#include "Clipper.h"
#include "VariableCache.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as on or off
	if (params.empty())
		return false;

	const auto vc = VariableCache::Get();
	const bool clip = vc->GetBool(params[0]);

	// Set clipping
	Clipper::Get()->SetClipping(clip);
	return true;
}
