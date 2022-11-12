#ifndef WEB_MC_H
#define WEB_MC_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

class WEB_MCA;
class WEB_MCB;
class WEB_Replay;


class WEB_MC : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_MCA *A;
	WEB_MCB *B;

	WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MC(WEB_Replay *WR_);
	void WRefresh();
	
};


#endif // WEB_MC
