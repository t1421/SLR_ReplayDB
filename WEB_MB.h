#ifndef WEB_MB_H
#define WEB_MB_H

struct WebCard {
	unsigned short CardID;
	unsigned int   playCount;
	bool		   bFire;
	bool		   bFrost;
	bool		   bShadow;
	bool		   bNature;
	bool		   bUnit;
	bool		   bSpell;
	bool		   bBuilding;
};

class WEB_MB
{
public:

	Replay* R;

	WFileUpload  *wfuDropZone;	
	WText		 *wtStatus;
	WText		 *Head;

	vector <WebCard*> WebDeck;
	

	WContainerWidget *cMain;
	WContainerWidget *cResult;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MB();
	bool showResults();
	bool FillWebDeck();
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building);
	void addColors();

};


#endif // WEB_MB
