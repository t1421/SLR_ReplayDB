#ifndef WEB_MA_H
#define WEB_MA_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

class WEB_MAA;
class WEB_Replay;
class WEB_Rank;

class WEB_MA : public WEB_Toolbar, public WebRefresh
{
public:

	WEB_MAA *A;
	WEB_Rank *B;

	Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MA(WEB_Replay *WR_);
	void WRefresh();
};


#endif // WEB_MA
