#pragma once
#include "Command.h"
class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightAmbient";
	}

	const char* GetDescription() override
	{
		return
			"SetLightAmbient(r, g, b)\n"
			"\n"
			"- Sets light Ambiant color (r, g, b).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightDiffuse";
	}

	const char* GetDescription() override
	{
		return
			"SetLightDiffuse(r, g, b)\n"
			"\n"
			"- Sets light Diffuse color (r, g, b).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
class CmdSetLightSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightSpecular";
	}

	const char* GetDescription() override
	{
		return
			"SetLightSpecular(r, g, b)\n"
			"\n"
			"- Sets light Specular color (r, g, b).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
class CmdAddDirectionalLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddDirectionalLight";
	}

	const char* GetDescription() override
	{
		return
			"AddDirectionalLight(x, y, z)\n"
			"\n"
			"- Adds directional light with direction vector (x, y, z).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddPointLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddPointLight";
	}

	const char* GetDescription() override
	{
		return
			"AddPointLight(x, y, z, const, lin, quad)\n"
			"\n"
			"- Adds point light with position vector and attenuation(x, y, z, const, lin, quad).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

