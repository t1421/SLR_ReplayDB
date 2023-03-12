#ifndef WEB_MCD_H
#define WEB_MCD_H

#include "WEB_Utility.h"

class WEB_Analyser;

class WEB_MDA: public WebRefresh
{
public:

	WEB_Analyser *WA;

	Wt::WText		 *wtStatus;
	
	Wt::WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MDA(WEB_Analyser *WA_);
	void WRefresh();


};


#endif // WEB_MCA
