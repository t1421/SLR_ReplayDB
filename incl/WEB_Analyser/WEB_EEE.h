#ifndef WEB_EEE_H
#define WEB_EEE_H

#include "../WEB/WEB_Toolbar.h"

class WEB_EEE_Check;
class WEB_Analyser;

class WEB_EEE : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_EEE_Check *Check[EEESize];
	WEB_EEE_Check *ALL;
	
	Wt::WSlider *slider;
	Wt::WText *sliderText;
	Wt::WText *sliderTextLow;

	std::string TimeToText(std::time_t timestamp);
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_EEE(WEB_Analyser *WA_);
	void WRefresh();
};


#endif // WEB_EEE
