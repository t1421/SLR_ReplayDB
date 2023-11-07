#ifndef WEB_Tome_PublicBoosters_H
#define WEB_Tome_PublicBoosters_H

#include "..\WEB\WEB_Utility.h"
class WEB_Container_Tome;

class WEB_Tome_PublicBoosters : public WebRefresh
{
public:

	WEB_Tome_PublicBoosters(WEB_Container_Tome *Con_);
	Wt::WTable *wtTabelle;
	Wt::WLineEdit *wlFilter;
	Wt::WText *wtBoosterCount;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_PublicBoosters_H
