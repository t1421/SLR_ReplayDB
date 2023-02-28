#ifndef WEB_MD_H
#define WEB_MD_H

#include "WEB_Toolbar.h"

class WEB_MDA;
class WEB_Rank;
class WEB_Analyser;


class WEB_MD : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_MDA *A;
	WEB_Rank *B;

	//Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MD(WEB_Analyser *WA_);
	void WRefresh();
	
};


#endif // WEB_MC
