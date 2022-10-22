#pragma once
#include "Command.h"
class CmdEndDraw : public Command
{
public:
	const char* GetName() override
	{
		return "EndDraw";
	}

	const char* GetDescription() override
	{
		return
			"EndDraw()\n"
			"\n"
			"- Push all vertex data to rasterizer for rendering.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

