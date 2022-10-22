#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
	FillMode fillMode = FillMode::Solid;
	if (params.size() > 0)
		if (params[0] == "wireframe" || params[0] == "Wireframe"
			|| params[0] == "wire" || params[0] == "Wire")
			fillMode = FillMode::Wireframe;

	Rasterizer::Get()->SetFillMode(fillMode);
	return true;
}
