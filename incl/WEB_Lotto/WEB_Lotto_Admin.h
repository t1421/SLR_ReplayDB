#ifndef WEB_Lotto_Admin_H
#define WEB_Lotto_Admin_H

#include "..\WEB\WEB_Utility.h"

class WEB_Container_Lotto;

class WEB_Lotto_Admin : public WebRefresh
{
public:

	WEB_Lotto_Admin(WEB_Container_Lotto *Con_);

	Wt::WTable *wtTabelle;

	Wt::WPushButton *wbAddWeek;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	WEB_Container_Lotto *Con;
};


#endif // WEB_Lotto_Admin_H
