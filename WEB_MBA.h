#ifndef WEB_MBA_H
#define WEB_MBA_H

#include "WEB_MB.h"

class WEB_MBA
{
public:

	Replay* R;

	WFileUpload  *wfuDropZone;	
	WText		 *wtStatus;
	WText		 *wtMap;
	WText		 *wtTime;
	WText		 *Head;

	vector <WebCard*> WebDeck;	

	WContainerWidget *cMain;
	WContainerWidget *cResult;
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MBA();
	string showResults();
	bool FillWebDeck();
	bool FillWebDeckAction();
	bool FillWebDeckDeck();
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building);
	void addColors();

	bool getFromCSVBuilding(unsigned short uiCardID);
	bool getFromCSVSpell(unsigned short uiCardID);
	bool getFromCSVUnit(unsigned short uiCardID);

};


#endif // WEB_MBA
