#ifndef WEB_Tome_PublicCards_H
#define WEB_Tome_PublicCards_H

#include "..\WEB\WEB_Utility.h"
class WEB_Container_Tome;

class WEB_Tome_PublicCards : public WebRefresh
{
public:

	WEB_Tome_PublicCards(WEB_Container_Tome *Con_);
	Wt::WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();


private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_PublicCards_H
