#ifndef WEB_Tome_Public_H
#define WEB_Tome_Public_H

#include "../WEB/WEB_Toolbar.h"

class WEB_Tome_PublicBoosters;
class WEB_Tome_PublicPlayers;
class WEB_Tome_PublicPlayersBooster;

class WEB_Container_Tome;

class WEB_Tome_Public : public WebRefresh, public WEB_Toolbar
{
public:

	WEB_Tome_Public(WEB_Container_Tome *Con_);

	WEB_Tome_PublicBoosters *PB;
	WEB_Tome_PublicPlayers *PP;
	WEB_Tome_PublicPlayersBooster *PPB;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

private:
	WEB_Container_Tome *Con;

};


#endif // WEB_Tome_Public_H
