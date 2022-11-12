#ifndef WEB_MBA_H
#define WEB_MBA_H

#include "WEB_MB.h"


class WEB_MBA: public WebRefresh
{
public:

	WEB_Replay *WR;
	
	WText		 *wtMap;
	WText		 *wtTime;
	WText		 *wtStatus;
	bool bMode;
	
	WContainerWidget *cMain;
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MBA(WEB_Replay *WR_,bool bMode_);
	void WRefresh();

};


#endif // WEB_MBA
