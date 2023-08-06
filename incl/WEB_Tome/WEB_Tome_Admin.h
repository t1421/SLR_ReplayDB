#ifndef WEB_Tome_Admin_H
#define WEB_Tome_Admin_H

#include "..\WEB\WEB_Utility.h"

struct TomeStruct;

class WEB_Tome_Admin : public WebRefresh
{
public:

	WEB_Tome_Admin(TomeStruct *TS);

	Wt::WText		     *wtStatus;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

};


#endif // WEB_Tome_Admin_H
