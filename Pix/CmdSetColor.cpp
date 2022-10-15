#include "CmdSetColor.h"
#include "Rasterizer.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float red = stof(params[0]);
	float green = stof(params[1]);
	float blue = stof(params[2]);

	float alpha = 1.f;
	if (params.size() >= 4)
		alpha = stof(params[3]);

	// Draw the pixel
	Rasterizer::Get()->SetColor({ red, green, blue, alpha });
	return true;
}
