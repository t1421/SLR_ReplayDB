#ifndef WEB_Tome_Admin_H
#define WEB_Tome_Admin_H

#include "..\WEB\WEB_Utility.h"

//#include <Wt/WFileUpload.h>

class WEB_Container_Tome;
//class WEB_Analyser;
struct WEB_Tome_Player;

class WEB_Tome_Admin : public WebRefresh
{
public:

	WEB_Tome_Admin(WEB_Container_Tome *Con_);

	Wt::WTable *wtTabelle;

	Wt::WCheckBox *wcAllowOpening;

	Wt::WCheckBox *wcShowPlayers;
	Wt::WCheckBox *wcShowBoosters;
	Wt::WCheckBox *wcShowBoostersOfPlayer;
	Wt::WCheckBox *wcNoDouble;

	Wt::WText *wtGameID;
	Wt::WText *wtAdminID;
	Wt::WAnchor *waLink;

	Wt::WPushButton *wbSave;
	Wt::WPushButton	*wbAddPlayer;	

	//Wt::WFileUpload  *wfuDropZone;
	//Wt::WTable *wtReplayResultCard;
	//Wt::WText		 *wtStatus;
	//WEB_Analyser* WA;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
private:
	WEB_Container_Tome *Con;
	void FixTable();
	void TabelToBro();
	std::vector<WEB_Tome_Player *> Tabel_Player;
};


#endif // WEB_Tome_Admin_H
