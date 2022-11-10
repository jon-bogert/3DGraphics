#include "CmdPushTranslation.h"
#include "MatrixStack.h"

bool CmdPushTranslation::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 2)
		return false;

	float x = std::stof(params[0]);
	float y = std::stof(params[1]);
	if (params.size() == 2)
	{
		MatrixStack::Get()->PushTranslation({ x, y, 0.f });
		return true;
	}

	float z = std::stof(params[2]);
	MatrixStack::Get()->PushTranslation({ x, y, z });
	return true;
}
