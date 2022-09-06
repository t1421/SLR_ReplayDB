#ifndef WEB_MB_H
#define WEB_MB_H

#define IMG_SIZE 50

struct WebCard {
	unsigned short CardID;
	unsigned int   playCount;
	unsigned int   iFire;
	unsigned int   iFrost;
	unsigned int   iShadow;
	unsigned int   iNature;
	unsigned int   iNeutral;
	bool		   bUnit;
	bool		   bSpell;
	bool		   bBuilding;

	WImage		  *IMG[3];
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
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MB();
	bool showResults();
	bool FillWebDeck();
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building);
	void addColors();

};


#endif // WEB_MB
