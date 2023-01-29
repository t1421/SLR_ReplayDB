#ifndef WEB_MBA_H
#define WEB_MBA_H

#include "WEB_Utility.h"

class WEB_Replay;

class WEB_MBA: public WebRefresh
{
public:

	WEB_Replay *WR;
	
	Wt::WText		 *wtStatus;
	bool bMode;
	
	Wt::WContainerWidget *cMain;
	Wt::WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MBA(WEB_Replay *WR_,bool bMode_);
	void WRefresh();

};


#endif // WEB_MBA
