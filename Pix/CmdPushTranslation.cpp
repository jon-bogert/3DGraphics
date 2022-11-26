#include "CmdPushTranslation.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 2)
		return false;

	float x = VariableCache::Get()->GetFloat(params[0]);
	float y = VariableCache::Get()->GetFloat(params[1]);
	if (params.size() == 2)
	{
		MatrixStack::Get()->PushTranslation({ x, y, 0.f });
		return true;
	}

	float z = VariableCache::Get()->GetFloat(params[2]);
	MatrixStack::Get()->PushTranslation({ x, y, z });
	return true;
}
