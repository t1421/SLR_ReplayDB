#ifndef WEB_Event_H
#define WEB_Event_H

#include "../WEB/WEB_Utility.h"

class WEB_Analyser;
class WEB_Rank;

class WEB_Event : public WebRefresh
{
public:

	WEB_Rank *Rank;
	WEB_Analyser *WR;

	Wt::WText		 *wtStatus;	
	Wt::WText* wtLine1;
	Wt::WText* wtLine2;
	Wt::WText* wtLine3;
	Wt::WText* wtLine4;
	Wt::WSlider* slider;
	Wt::WText* sliderText;
	Wt::WText* sliderNow;

	unsigned int iEventNr;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Event(WEB_Analyser *WR_, unsigned int _iEventNr);
	void WRefresh();


};


#endif // WEB_Event
