#pragma once
#include "Command.h"
class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"PopMatrix()\n"
			"\n"
			"- Removes the last-pushed transformation.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

