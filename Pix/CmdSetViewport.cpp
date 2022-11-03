#include "CmdSetViewport.h"
#include "Viewport.h"

using std::stof;

bool CmdSetViewport::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 4)
		return false;

	Viewport::Get()->SetViewport(stof(params[0]), stof(params[1]), stof(params[2]), stof(params[3]));

	return true;
}
