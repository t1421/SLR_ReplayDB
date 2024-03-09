#ifndef WEB_Lotto_Week_H
#define WEB_Lotto_Week_H

#include "..\WEB\WEB_Utility.h"

#include <Wt/WFileUpload.h>

class WEB_Container_Lotto;
class WEB_Analyser;
struct Lotto_Player;

class WEB_Lotto_Week : public WebRefresh
{
public:

	WEB_Lotto_Week(WEB_Container_Lotto *Con_, LottoWeek *BroWeek_);

	Wt::WTable *wtTabelle;
	Wt::WTable *wtPulls;

	Wt::WFileUpload  *wfuDropZone;
	Wt::WTable *wtReplayResultCard;
	//std::vector<std::string> SimpelDeck;
	Lotto_Player *myPlayer;
	Wt::WText		 *wtStatus;
	Wt::WPushButton *wtJoin;
	WEB_Analyser* WA;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }
	LottoWeek *BroWeek;

	void WRefresh();
private:
	void DrawDeck(Wt::WTable *wtTabelle, Lotto_Player *Player, bool bColore);
	WEB_Container_Lotto *Con;
	
};


#endif // WEB_Lotto_Week_H
