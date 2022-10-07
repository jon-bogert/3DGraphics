#pragma once

#include "Command.h"

class CmdSetClipping : public Command
{
public:
	const char* GetName() override
	{
		return "SetClipping";
	}

	const char* GetDescription() override
	{
		return
			"SetClipping(true or false)\n"
			"\n"
			"- Enable/disable clipping.\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
