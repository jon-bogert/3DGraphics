#pragma once
#include "Command.h"
class CmdModel :
    public Command
{
public:
	const char* GetName() override
	{
		return "Model";
	}

	const char* GetDescription() override
	{
		return
			"Model(fileName)\n"
			"\n"
			"- Loads model to modelCache (fileName).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

