#ifndef WEB_Analyser_H
#define WEB_Analyser_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

class WEB_Analyser_Head;
class WEB_Analyser_Deck;
class WEB_Analyser_Acti;
class WEB_Replay;
class WEB_Rank;

class WEB_Analyser : public WEB_Toolbar, public WebRefresh
{
public:

	WEB_Analyser_Head *Head;
	WEB_Analyser_Deck *Deck;
	WEB_Analyser_Acti *Acti;

	Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser(WEB_Replay *WR_);
	void WRefresh();
};


#endif // WEB_Analyser
