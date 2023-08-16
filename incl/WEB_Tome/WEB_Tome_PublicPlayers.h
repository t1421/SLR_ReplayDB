#ifndef WEB_Tome_PublicPlayers_H
#define WEB_Tome_PublicPlayers_H

#include "..\WEB\WEB_Utility.h"
class WEB_Container_Tome;

class WEB_Tome_PublicPlayers : public WebRefresh
{
public:

	WEB_Tome_PublicPlayers(WEB_Container_Tome *Con_);
	Wt::WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();


private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_PublicPlayers_H
