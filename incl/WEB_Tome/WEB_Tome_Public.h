#ifndef WEB_Tome_Public_H
#define WEB_Tome_Public_H

#include "..\WEB\WEB_Utility.h"

struct  TomeStruct;

class WEB_Tome_Public : public WebRefresh
{
public:

	WEB_Tome_Public();

	Wt::WText		     *wtStatus;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

};


#endif // WEB_Tome_Public_H
