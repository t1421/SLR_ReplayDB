#ifndef WEB_Analyser_Deck_H
#define WEB_Analyser_Deck_H

#include "../WEB/WEB_Utility.h"

class WEB_Analyser;

class WEB_Analyser_Deck : public WebRefresh
{
public:
	bool newData;

	WEB_Analyser *WA;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Deck(WEB_Analyser *WA_);
	void WRefresh();

	Wt::WTable *wtTabelle;

private:
	//bool GetDecks();
	unsigned int drawPlayer(unsigned int iPlayer, unsigned int &iRow);
	
	
};


#endif // WEB_Analyser_Deck
