#ifndef WEB_Analyser_Acti_H
#define WEB_Analyser_Acti_H

#include "WEB_Utility.h"

class WEB_Replay;

class WEB_Analyser_Acti : public WebRefresh
{
public:

	WEB_Replay *WR;
	
	//Wt::WText		 *wtStatus;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Acti(WEB_Replay *WR_);
	void WRefresh();

};


#endif // WEB_Analyser_Acti
