#include "CmdSetCorrectUV.h"

#include "PrimitiveManager.h"
#include "VariableCache.h"

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as on or off
	if (params.empty())
		return false;

	auto vc = VariableCache::Get();
	const bool correctUV = vc->GetBool(params[0]);

	// Use perspective correct texturing
	PrimitiveManager::Get()->SetCorrectUV(correctUV);
	return true;
}
