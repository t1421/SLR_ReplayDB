#ifndef WEB_Tome_Admin_H
#define WEB_Tome_Admin_H

#include "..\WEB\WEB_Utility.h"



class WEB_Container_Tome;

class WEB_Tome_Admin : public WebRefresh
{
public:

	WEB_Tome_Admin(WEB_Container_Tome *Con_);

	Wt::WTable *wtTabelle;

	Wt::WCheckBox *wcShowPlayers;
	Wt::WCheckBox *wcShowBoosters;
	Wt::WCheckBox *wcShowBoostersOfPlayer;

	Wt::WText *wtGameID;
	Wt::WText *wtAdminID;

	Wt::WPushButton	*wbAddPlayer;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_Admin_H
