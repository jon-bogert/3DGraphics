#pragma once
#include "Command.h"
class CmdPushTranslation : public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}

	const char* GetDescription() override
	{
		return
			"PushTranslation(x, y, z)\n"
			"\n"
			"- Applies Translation.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

