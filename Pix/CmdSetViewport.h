#pragma once
#include "Command.h"
class CmdSetViewport : public Command
{
public:
	const char* GetName() override
	{
		return "SetViewport";
	}

	const char* GetDescription() override
	{
		return
			"SetViewport(x, y, width, height)\n"
			"\n"
			"- Sets the viewport position to (x, y).\n"
			"- Sets viewport width and height to (width, height)\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

