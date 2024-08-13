#ifndef WEB_EEE_Check_H
#define WEB_EEE_Check_H

#include "../WEB/WEB_Utility.h"

class WEB_Analyser;
class WEB_Rank;

class WEB_EEE_Check : public WebRefresh
{
public:

	WEB_Rank *Rank;
	WEB_Analyser *WR;

	Wt::WText		 *wtStatus;	
	Wt::WText		 *wtPower;
	Wt::WText		 *wtTime;
	Wt::WText		 *wtAddInfo;
	
	unsigned int EEENR;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_EEE_Check(WEB_Analyser *WR_, unsigned int iEEE_NR_);
	void WRefresh();


};


#endif // WEB_EEE_Check
