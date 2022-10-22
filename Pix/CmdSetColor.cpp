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

	if (red > 1.f) red /= 255;
	if (green > 1.f) green /= 255;
	if (blue > 1.f) blue /= 255;
	if (alpha > 1.f) alpha /= 255;

	// Draw the pixel
	Rasterizer::Get()->SetColor({ red, green, blue, alpha });
	return true;
}
