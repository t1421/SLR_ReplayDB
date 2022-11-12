#ifndef WEB_MB_H
#define WEB_MB_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

class WEB_MBA;
class WEB_MBB;
class WEB_Replay;

class WEB_MB : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_MBA *A;
	WEB_MBA *B;

	WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MB(WEB_Replay *WR_);
	void WRefresh();
	
};


#endif // WEB_MB
