#ifndef WEB_MCD_H
#define WEB_MCD_H

#include "WEB_Utility.h"

class WEB_Replay;

class WEB_MDA: public WebRefresh
{
public:

	WEB_Replay *WR;

	Wt::WText		 *wtStatus;

	Wt::WContainerWidget *cMap;
	Wt::WImage       *wiMap;

	Wt::WContainerWidget *cMain;
	Wt::WContainerWidget *cReplay;
	Wt::WContainerWidget *cReplayResult;
	
	Wt::WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MDA(WEB_Replay *WR_);
	void WRefresh();

};


#endif // WEB_MCA
