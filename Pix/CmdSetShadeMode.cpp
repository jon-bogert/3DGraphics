#include "CmdSetShadeMode.h"
#include "Rasterizer.h"

bool CmdSetShadeMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() <= 0)
		return false;

	ShadeMode sm = ShadeMode::Gouraud;
	if (params[0] == "flat" || params[0] == "Flat")
	{
		sm = ShadeMode::Flat;
	}
	else if (params[0] == "gouraud" || params[0] == "Gouraud")
	{
		sm = ShadeMode::Gouraud;
	}
	else if(params[0] == "phong" || params[0] == "Phong")
	{
		sm = ShadeMode::Phong;
	}

	Rasterizer::Get()->SetShadeMode(sm);
	return true;
}
