#ifndef WEB_MAA_H
#define WEB_MAA_H

#include "WEB_Utility.h"

class WEB_Replay;

class WEB_MAA : public WebRefresh
{
public:

	WEB_Replay *WR;
	
	Wt::WText		 *wtStatus;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MAA(WEB_Replay *WR_);
	void WRefresh();

};


#endif // WEB_MAA
