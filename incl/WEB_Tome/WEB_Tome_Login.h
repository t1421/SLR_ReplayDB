#ifndef WEB_Tome_Login_H
#define WEB_Tome_Login_H

#include "..\WEB\WEB_Utility.h"

class WEB_Tome_Login : public WebRefresh
{
public:

	WEB_Tome_Login();

	Wt::WText		     *wtStatus;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();

};


#endif // WEB_Tome_Login_H
