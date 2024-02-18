#include "..\..\incl\WEB\WEB_Utility.h" 

#include <sstream>
#include <Wt/WImage.h>
#include <Wt/WEnvironment.h>

std::string WSTRINGtoSTRING(Wt::WString in)
{
	std::stringstream ss;
	ss << in;
	return ss.str();
}

Wt::WImage* DrawImg(std::string sPath, int iX, int iY)
{
	Wt::WImage* IMG = new Wt::WImage(sPath);
	IMG->setHeight(iY);
	IMG->setWidth(iX);
	IMG->resize(iX, iY);
	IMG->setMaximumSize(iX, iY);
	return IMG;
}

std::string sGetParam(const Wt::WEnvironment& env, std::string sParam)
{
	if (!env.getParameterValues(sParam).empty())
	{
		const std::string *PARA = (env.getParameter(sParam));
		return PARA->c_str();
	}
	return "";
}