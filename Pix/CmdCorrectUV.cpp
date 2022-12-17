#include "CmdCorrectUV.h"
#include "VariableCache.h"

bool CmdCorrectUV::Execute(const std::vector<std::string>& params)
{
	if (params.size() == 0)
		return false;

	auto vc = VariableCache::Get();
	//const bool correctUV = vc->
	return true;
}
