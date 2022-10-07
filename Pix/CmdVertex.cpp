#include "CmdVertex.h"

#include "PrimitiveManager.h"
#include "VariableCache.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	auto vc = VariableCache::Get();

	float x = 0.0f, y = 0.0f, z = 0.0f, r = 1.0f, g = 1.0f, b = 1.0f;
	if (params.size() == 2)
	{
		x = vc->GetFloat(params[0]);
		y = vc->GetFloat(params[1]);
	}
	else if (params.size() == 3)
	{
		x = vc->GetFloat(params[0]);
		y = vc->GetFloat(params[1]);
		z = vc->GetFloat(params[2]);
	}
	else if (params.size() == 5)
	{
		x = vc->GetFloat(params[0]);
		y = vc->GetFloat(params[1]);
		r = vc->GetFloat(params[2]);
		g = vc->GetFloat(params[3]);
		b = vc->GetFloat(params[4]);
	}
	else if (params.size() == 6)
	{
		x = vc->GetFloat(params[0]);
		y = vc->GetFloat(params[1]);
		z = vc->GetFloat(params[2]);
		r = vc->GetFloat(params[3]);
		g = vc->GetFloat(params[4]);
		b = vc->GetFloat(params[5]);
	}
	else
	{
		return false;
	}

	PrimitiveManager::Get()->AddVertex({ { x, y, z }, { r, g, b, 1.0f } });
	return true;
}
