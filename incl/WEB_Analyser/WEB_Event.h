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
	Wt::WText		 *wtPower;
	Wt::WText		 *wtTime;
	Wt::WSlider* slider;
	Wt::WText* sliderText;

	unsigned int iEventNr;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Event(WEB_Analyser *WR_, unsigned int _iEventNr);
	void WRefresh();


};


#endif // WEB_Event
