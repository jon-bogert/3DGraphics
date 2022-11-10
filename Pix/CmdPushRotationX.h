#pragma once
#include "Command.h"

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationX(rad)\n"
			"\n"
			"- Applies X-Rotation.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

