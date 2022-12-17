#pragma once
#include "Command.h"
class CmdCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "CorrectUV";
	}

	const char* GetDescription() override
	{
		return
			"CorrectUV(setTo)\n"
			"\n"
			"- Use UV of colors.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

