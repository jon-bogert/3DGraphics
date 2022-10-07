#include "CmdSetViewport.h"

#include "Viewport.h"

bool CmdSetViewport::Execute(const std::vector<std::string>& params)
{
	// Need at least 4 param for x, y, width, and height
	if (params.size() < 4)
		return false;

	const float x = std::stof(params[0]);
	const float y = std::stof(params[1]);
	const float w = std::stof(params[2]);
	const float h = std::stof(params[3]);

	// Set viewport
	Viewport::Get()->SetViewport(x, y, w, h);
	return true;
}
