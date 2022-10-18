#ifndef WEB_MB_H
#define WEB_MB_H

#define IMG_SIZE 50
#define MaxRegister 2

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
	WText		 *wtMap;
	WText		 *wtTime;
	WText		 *Head;

	vector <WebCard*> WebDeck;	

	WContainerWidget *cMain;
	WContainerWidget *cResult;
	WTable *wtTabelle;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MB();
	string showResults();
	bool FillWebDeck();
	bool FillWebDeckAction();
	bool FillWebDeckDeck();
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building);
	void addColors();

	bool getFromCSVBuilding(unsigned short uiCardID);
	bool getFromCSVSpell(unsigned short uiCardID);
	bool getFromCSVUnit(unsigned short uiCardID);

	Wt::WPushButton *button[MaxRegister];
	Wt::WToolBar *toolBar;
	int iAktiveToolbar;
	void updateToolbar();
	void ToolBarButton(int Index, string Name);

};


#endif // WEB_MB
