#ifndef WEB_Utility_H
#define WEB_Utility_H

#include <string>
#include <Wt/WString.h>

class WebRefresh
{
public:
	virtual void WRefresh() { printf("no refresh\n"); };
};


std::string WSTRINGtoSTRING(Wt::WString in);

#endif //Utility_H


