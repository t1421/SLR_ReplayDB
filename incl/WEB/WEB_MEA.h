#ifndef WEB_MED_H
#define WEB_MED_H

#include "WEB_Utility.h"

class WEB_Analyser;

class WEB_MEA: public WebRefresh
{
public:

	WEB_Analyser *WA;

	Wt::WText		 *wtStatus;
	
	Wt::WTable *wtTabelle;
	Wt::WTable *wtInfos;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MEA(WEB_Analyser *WA_);
	void WRefresh();


};


#endif // WEB_MEA
