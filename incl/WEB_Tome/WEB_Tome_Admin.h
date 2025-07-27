#ifndef WEB_Tome_Admin_H
#define WEB_Tome_Admin_H

#include "..\WEB\WEB_Utility.h"

#include <Wt/WFileUpload.h>

class WEB_Container_Tome;
class WEB_Analyser;
struct WEB_Tome_Player;

class WEB_Tome_Admin : public WebRefresh
{
public:

	WEB_Tome_Admin(WEB_Container_Tome *Con_);

	Wt::WTable *wtTabelle;

	Wt::WCheckBox* wcShowGlobalBoosterProgress;

	Wt::WCheckBox* wcTapShowPlayer;
	Wt::WCheckBox* wcTapShowPlayerBoosterOpen;
	Wt::WCheckBox* wcTapShowPlayerBoosterMax;

	Wt::WCheckBox* wcTapShowBooster;
	Wt::WCheckBox* wcTapShowBoosterUR;
	Wt::WCheckBox* wcTapShowBoosterR;
	Wt::WCheckBox* wcTapShowBoosterUC;
	Wt::WCheckBox* wcTapShowBoosterC;
	Wt::WComboBox* wcTapShowBoosterOrder;

	Wt::WCheckBox* wcTapShowCards;
	Wt::WCheckBox* wcTapShowCardsUR;
	Wt::WCheckBox* wcTapShowCardsR;
	Wt::WCheckBox* wcTapShowCardsUC;
	Wt::WCheckBox* wcTapShowCardsC;
	Wt::WComboBox* wcTapShowCardsOrder;

	Wt::WCheckBox* wcTapShowBoosterPerPlayer;
	Wt::WCheckBox* wcTapShowBoosterPerPlayerUR;
	Wt::WCheckBox* wcTapShowBoosterPerPlayerR;
	Wt::WCheckBox* wcTapShowBoosterPerPlayerUC;
	Wt::WCheckBox* wcTapShowBoosterPerPlayerC;
	Wt::WCheckBox* wcTapShowBoosterPerPlayerBooster;	
	Wt::WComboBox* wcTapShowBoosterPerPlayerOrder;


	Wt::WCheckBox* wcAllowOpening;
	Wt::WCheckBox* wcNoDoubleBooster;

	Wt::WCheckBox* wcAllowRefroging;
	Wt::WCheckBox* wcNoDoubleRefroging;
		
	Wt::WCheckBox* wcNoAffinities;
	Wt::WCheckBox* wcNoPromos;
	
	Wt::WText *wtGameID;
	Wt::WText *wtAdminID;
	Wt::WAnchor *waLink;

	Wt::WPushButton *wbSave;
	Wt::WPushButton	*wbAddPlayer;	

	Wt::WFileUpload  *wfuDropZone;
	Wt::WTable *wtReplayResultCard;
	Wt::WText		 *wtStatus;
	WEB_Analyser* WA;
	
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
