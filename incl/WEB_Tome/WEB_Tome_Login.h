#ifndef WEB_Tome_Login_H
#define WEB_Tome_Login_H

#include "..\WEB\WEB_Utility.h"

class WEB_Container_Tome;

class WEB_Tome_Login : public WebRefresh
{
public:

	WEB_Tome_Login(WEB_Container_Tome *Con_);

	Wt::WText		*wtStatus;
	Wt::WLineEdit	*wlGameID;
	Wt::WLineEdit	*wlPlayerID;
	Wt::WLineEdit	*wlAdminID;

	Wt::WPushButton	*wbJoin;
	Wt::WPushButton	*wbLeave;
		
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void Check_Input(std::string sGameID, std::string sPlayerID, std::string sAdminID);

	void WRefresh();

private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_Login_H