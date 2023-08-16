#ifndef WEB_Tome_PublicPlayersBooster_H
#define WEB_Tome_PublicPlayersBooster_H

#include "..\WEB\WEB_Utility.h"

class WEB_Tome_PublicPlayersBooster : public WebRefresh
{
public:

	WEB_Tome_PublicPlayersBooster();

	Wt::WText		     *wtStatus;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

};


#endif // WEB_Tome_PublicPlayersBooster_H
