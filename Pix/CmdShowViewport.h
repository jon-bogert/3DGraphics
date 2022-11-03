#pragma once
#include "Command.h"
class CmdShowViewport : public Command
{
public:
	const char* GetName() override
	{
		return "ShowViewport";
	}

	const char* GetDescription() override
	{
		return
			"ShowViewport(bool)\n"
			"\n"
			"- Sets whether viewport is visible based on bool\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

