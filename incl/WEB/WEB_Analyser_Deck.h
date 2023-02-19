#ifndef WEB_Analyser_Deck_H
#define WEB_Analyser_Deck_H

#include "WEB_Utility.h"

class WEB_Replay;
struct Player;

class WEB_Analyser_Deck : public WebRefresh
{
public:

	WEB_Replay *WR;
	
	//Wt::WText		 *wtStatus;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Deck(WEB_Replay *WR_);
	void WRefresh();

	Wt::WTable *wtTabelle;

private:
	bool GetDecks();
	unsigned int drawPlayer(unsigned int iPlayer, unsigned int &iRow);
	std::vector <Player*> Players;
	
};


#endif // WEB_Analyser_Deck
