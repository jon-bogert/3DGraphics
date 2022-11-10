#include "CmdPushScaling.h"
#include "MatrixStack.h"

bool CmdPushScaling::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;

	float x = std::stof(params[0]);
	if (params.size() == 1)
	{
		MatrixStack::Get()->PushScaling({ x, x, x });
		return true;
	}

	float y = std::stof(params[1]);
	if (params.size() == 2)
	{
		MatrixStack::Get()->PushScaling({ x, y, 1.f });
		return true;
	}

	float z = std::stof(params[2]);
	MatrixStack::Get()->PushScaling({x, y, z});
	return true;
}
