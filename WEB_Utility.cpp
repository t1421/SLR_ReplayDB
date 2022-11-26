#include "WEB_Utility.h" 

#include <sstream>

std::string WSTRINGtoSTRING(Wt::WString in)
{
	std::stringstream ss;
	ss << in;
	return ss.str();
}