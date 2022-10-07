#include "CmdBeginDraw.h"

#include "PrimitiveManager.h"

bool CmdBeginDraw::Execute(const std::vector<std::string>& params)
{
	// Need at least 1 param as primitive topology
	if (params.empty())
		return false;

	Topology topology;
	if (params[0] == "point")
		topology = Topology::Point;
	else if (params[0] == "line")
		topology = Topology::Line;
	else if (params[0] == "triangle")
		topology = Topology::Triangle;
	else
		return false;

	bool applyTransform = params.size() > 1 && params[1] == "true";

	// Begin primitive
	return PrimitiveManager::Get()->BeginDraw(topology, applyTransform);
}
