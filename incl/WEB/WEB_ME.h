#ifndef WEB_ME_H
#define WEB_ME_H

#include "WEB_Toolbar.h"

class WEB_MEA;
class WEB_Rank;
class WEB_Analyser;


class WEB_ME : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_MEA *A;
	WEB_Rank *B;

	//Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_ME(WEB_Analyser *WA_);
	void WRefresh();
	
};


#endif // WEB_MC
