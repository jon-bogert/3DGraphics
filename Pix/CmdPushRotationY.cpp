#include "CmdPushRotationY.h"
#include "MatrixStack.h"
#include "VariableCache.h"
#include "MathHelper.h"

bool CmdPushRotationY::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	MatrixStack::Get()->PushRotationY(MathHelper::Deg2Rad(VariableCache::Get()->GetFloat(params[0])));
	return true;
}
