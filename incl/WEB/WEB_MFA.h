#ifndef WEB_MFA_H
#define WEB_MFA_H

#include "WEB_Utility.h"

class WEB_Analyser;

class WEB_MFA: public WebRefresh
{
public:

	WEB_Analyser *WR;

	Wt::WText		 *wtStatus;

	//Wt::WContainerWidget *cMap;
	Wt::WImage       *wiMap;

	//Wt::WContainerWidget *cMain;
	//Wt::WContainerWidget *cReplay;
	//Wt::WContainerWidget *cReplayResult;
	
	Wt::WTable *wtTabelle[3];
	Wt::WContainerWidget *wcTabelle[3];

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MFA(WEB_Analyser *WR_);
	void WRefresh();

};


#endif // WEB_MFA
