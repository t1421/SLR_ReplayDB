#ifndef WEB_Analyser_Acti_H
#define WEB_Analyser_Acti_H

#include "WEB_Utility.h"


class WEB_Analyser;

class WEB_Analyser_Acti : public WebRefresh
{
public:

	WEB_Analyser *WA;
	
	//Wt::WText		 *wtStatus;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Acti(WEB_Analyser *WA_);
	void WRefresh();

};


#endif // WEB_Analyser_Acti
