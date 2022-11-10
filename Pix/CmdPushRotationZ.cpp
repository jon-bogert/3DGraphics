#include "CmdPushRotationZ.h"
#include "MatrixStack.h"
#include "VariableCache.h"
#include "MathHelper.h"

bool CmdPushRotationZ::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	MatrixStack::Get()->PushRotationZ(MathHelper::Deg2Rad(VariableCache::Get()->GetFloat(params[0])));
	return true;
}
