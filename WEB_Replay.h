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

	WEB_Replay();
	bool NewReplay(string sFile);

	bool BOT1();
	int CountActions();

	Replay* R;
	vector <WebCard*> WebDeckDeck;
	vector <WebCard*> WebDeckActions;
	vector <Marker *> vMarker;
	
	bool BOT2();
	bool FillWebDeckDeck();
	bool FillWebDeckAction();
	bool FillTableBOT2(vector <WebCard*>& WebDeck, WTable *wtTabelle);

	bool BOT3();
	bool BOT3Stuff;
	void BOT3WellsAndOrbUnit();
	unsigned int Difficulty();
	int CountActions(string sFilter);
	unsigned int Playtime();
	void FillTableBOT3(WTable *wtTabelle);
	

	string MapName();
	string Time();


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
	
	

};

#endif //WEB_Replay_H
