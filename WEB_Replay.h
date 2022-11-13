#ifndef WEB_Replay_H
#define WEB_Replay_H

#include "WEB_Main.h"

class Replay;

#define BOT2_IMG_SIZE 50
#define BOT3_IMG_SIZE 300
#define Xoffset -304
#define Yoffset -199

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




struct Marker
{
	unsigned short Type;
	unsigned long Unit;
	WText *Time;
	WImage *IMG;

	Marker(unsigned short _Type,
		unsigned long _Unit,
		short _X,
		short _Y) :
		Type(_Type),
		Unit(_Unit),
		Time(new WText("XX:XX")),
		IMG(new WImage("./resources/M.gif"))
	{
		IMG->setHidden(true);
		IMG->setHeight(10);
		IMG->setWidth(10);
		IMG->resize(10, 10);
		IMG->setMaximumSize(10, 10);
		IMG->setPositionScheme(PositionScheme::Relative);
		IMG->setOffsets(_X + Xoffset, Side::Left);
		IMG->setOffsets(_Y + Yoffset, Side::Top);
	}
};


class WEB_Replay
{
public:

	Replay* R;
	vector <WebCard*> WebDeckDeck;
	vector <WebCard*> WebDeckActions;
	vector <Marker *> vMarker;
	bool BOT3Stuff;

	WEB_Replay();
	
	string BOT1();
	string BOT2(bool bMode, WTable *wtTabelle);
	string BOT3(WTable *wtTabelle, WContainerWidget *cMap);

	int CountActions();
	int CountActions(string sFilter);
	unsigned int Difficulty();
	unsigned int Playtime();
	string MapName();
	string Time();

	bool NewReplay(string sFile);
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

	bool getFromCSVBuilding(unsigned short uiCardID);
	bool getFromCSVSpell(unsigned short uiCardID);
	bool getFromCSVUnit(unsigned short uiCardID);
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building, vector <WebCard*>& WebDeck);
	void addColors(vector <WebCard*>& WebDeck);
	void InitVector();

	bool FillWebDeckDeck();
	bool FillWebDeckAction();
	bool FillTableBOT2(vector <WebCard*>& WebDeck, WTable *wtTabelle);

	void BOT3WellsAndOrbUnit();
	void FillTableBOT3(WTable *wtTabelle);

};

#endif //WEB_Replay_H
