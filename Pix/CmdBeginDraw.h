#pragma once
#include "Command.h"
class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDrawl(topology)\n"
			"\n"
			"- Begin primative drawing and stors topology type.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

