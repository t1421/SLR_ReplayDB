#ifndef WEB_MCA_H
#define WEB_MCA_H

#include "WEB_MC.h"

class WEB_MCA: public WebRefresh
{
public:

	WEB_Replay *WR;

	WText		 *wtStatus;

	WContainerWidget *cMap;
	WImage       *wiMap;	

	WContainerWidget *cMain;
	WContainerWidget *cReplay;
	WContainerWidget *cReplayResult;
	
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MCA(WEB_Replay *WR_);
	void WRefresh();

};


#endif // WEB_MCA
