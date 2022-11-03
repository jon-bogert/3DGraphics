#include "CmdSetClipping.h"
#include "Clipper.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
	bool setTo = false;
	if (params.size() > 0)
		if (params[0] == "true")
			setTo = true;

	Clipper::Get()->SetIsClipping(setTo);
	return true;
}
