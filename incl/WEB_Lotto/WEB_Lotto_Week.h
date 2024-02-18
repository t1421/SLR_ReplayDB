#ifndef WEB_Lotto_Week_H
#define WEB_Lotto_Week_H

#include "..\WEB\WEB_Utility.h"

#include <Wt/WFileUpload.h>

class WEB_Container_Lotto;
class WEB_Analyser;

class WEB_Lotto_Week : public WebRefresh
{
public:

	WEB_Lotto_Week(WEB_Container_Lotto *Con_, LottoWeek *BroWeek_);

	Wt::WTable *wtTabelle;

	Wt::WFileUpload  *wfuDropZone;
	Wt::WTable *wtReplayResultCard;
	Wt::WText		 *wtStatus;
	WEB_Analyser* WA;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	WEB_Container_Lotto *Con;
	LottoWeek *BroWeek;
};


#endif // WEB_Lotto_Week_H
