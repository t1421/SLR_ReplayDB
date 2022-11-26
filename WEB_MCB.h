#ifndef WEB_MCB_H
#define WEB_MCB_H

#include "WEB_Utility.h"

class WEB_MCB: public WebRefresh
{
public:
	
	Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MCB();	
};


#endif // WEB_MCB
