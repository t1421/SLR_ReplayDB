#ifndef WEB_Lotto_Admin_Pull_H
#define WEB_Lotto_Admin_Pull_H

#include "..\WEB\WEB_Utility.h"

class WEB_Container_Lotto;

class WEB_Lotto_Admin_Pull : public WebRefresh
{
public:

	WEB_Lotto_Admin_Pull(WEB_Container_Lotto *Con_);

	Wt::WTable *wtTabelle;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	LottoWeek *BroWeek;
	WEB_Container_Lotto *Con;
};


#endif // WEB_Lotto_Admin_Pull_H
