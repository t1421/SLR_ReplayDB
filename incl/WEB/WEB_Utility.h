#ifndef WEB_Utility_H
#define WEB_Utility_H

#include <string>
#include <Wt/WString.h>

class WebRefresh
{
public:
	Wt::WContainerWidget *cMain;
	virtual void WRefresh() { printf("no refresh\n"); };
};


std::string WSTRINGtoSTRING(Wt::WString in);
Wt::WImage* DrawImg(std::string sPath, int iX, int iY);
std::string sGetParam(const Wt::WEnvironment& env, std::string sParam);

#endif //Utility_H


