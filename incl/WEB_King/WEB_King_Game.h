#ifndef WEB_King_Game_H
#define WEB_King_Game_H

#include "..\WEB\WEB_Utility.h"

class WEB_Analyser;
class WEB_Container_King;

class WEB_King_Game : public WebRefresh
{
public:

	WEB_King_Game(WEB_Container_King* Con_, WEB_Analyser* WA_);

	Wt::WTable *wtGames;
	Wt::WPushButton* wbSave;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }
	LottoWeek *BroWeek;

	void WRefresh();
private:
	WEB_Container_King *Con;
	WEB_Analyser* WA;
	
};


#endif // WEB_King_Game
