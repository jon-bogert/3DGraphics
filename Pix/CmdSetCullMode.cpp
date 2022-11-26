#include "CmdSetCullMode.h"
#include "PrimativeManager.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
	if ( params.size() < 0)
		return false;

	if (params[0] == "none" || params[0] == "None")
		PrimativeManager::Get()->SetCullMode(CullMode::None);
	else if (params[0] == "back" || params[0] == "Back")
		PrimativeManager::Get()->SetCullMode(CullMode::Back);
	else if (params[0] == "front" || params[0] == "Front")
		PrimativeManager::Get()->SetCullMode(CullMode::Front);


	return true;
}
