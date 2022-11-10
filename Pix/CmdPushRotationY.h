#pragma once
#include "Command.h"
class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationY(rad)\n"
			"\n"
			"- Applies Y-Rotation.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

