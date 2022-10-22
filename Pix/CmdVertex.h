#pragma once
#include "Command.h"
class CmdVertex : public Command
{
public:
	const char* GetName() override
	{
		return "Vertex";
	}

	const char* GetDescription() override
	{
		return
			"Vertex(x, y, z, [r, g, b, [a]])\n"
			"\n"
			"- Adds vertex to buffer at position (x, y, z) with color.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

