#ifndef WEB_Tome_Player_H
#define WEB_Tome_Player_H

#include "..\WEB\WEB_Utility.h"

class WEB_Container_Tome;
class WEB_Analyser;

class WEB_Tome_Player : public WebRefresh
{
public:

	WEB_Tome_Player(WEB_Container_Tome *Con_);
	Wt::WTable *wtBooster;
	Wt::WTable *wtHistory;
	Wt::WLineEdit *wlFilter;

	Wt::WText *wtGameID;
	Wt::WText *wtPlayerID;

	Wt::WFileUpload  *wfuDropZone;	
	Wt::WText		 *wtStatus;
	WEB_Analyser* WA;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_Login_H
