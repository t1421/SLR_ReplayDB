#ifndef WEB_Tome_PublicPlayersBooster_H
#define WEB_Tome_PublicPlayersBooster_H

#include "..\WEB\WEB_Utility.h"
class WEB_Container_Tome;

class WEB_Tome_PublicPlayersBooster : public WebRefresh
{
public:

	WEB_Tome_PublicPlayersBooster(WEB_Container_Tome *Con_);
	Wt::WTable *wtTabelle;
	Wt::WLineEdit* wlFilter;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_PublicPlayersBooster_H
