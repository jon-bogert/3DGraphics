#pragma once
#include "Command.h"
class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return
			"PushRotationZ(rad)\n"
			"\n"
			"- Applies Z-Rotation.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

