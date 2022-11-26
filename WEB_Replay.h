#ifndef WEB_Replay_H
#define WEB_Replay_H

//#include "WEB_Main.h"

#include <Wt/WText.h>
#include <Wt/WImage.h>

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

	Wt::WImage		  *IMG[3];
};




struct Marker
{
	unsigned short Type;
	unsigned long Unit;
	Wt::WText *Time;
	Wt::WImage *IMG;

	Marker(unsigned short _Type,
		unsigned long _Unit,
		short _X,
		short _Y) :
		Type(_Type),
		Unit(_Unit),
		Time(new Wt::WText("XX:XX")),
		IMG(new Wt::WImage("./resources/M.gif"))
	{
		IMG->setHidden(true);
		IMG->setHeight(10);
		IMG->setWidth(10);
		IMG->resize(10, 10);
		IMG->setMaximumSize(10, 10);
		IMG->setPositionScheme(Wt::PositionScheme::Relative);
		IMG->setOffsets(_X + Xoffset, Wt::Side::Left);
		IMG->setOffsets(_Y + Yoffset, Wt::Side::Top);
	}
};


class WEB_Replay
{
public:

	Replay* R;
	std::vector <WebCard*> WebDeckDeck;
	std::vector <WebCard*> WebDeckActions;
	std::vector <Marker *> vMarker;
	bool BOT3Stuff;

	WEB_Replay();
	
	std::string BOT1();
	std::string BOT2(bool bMode, Wt::WTable *wtTabelle);
	std::string BOT3(Wt::WTable *wtTabelle, Wt::WContainerWidget *cMap);

	int CountActions();
	int CountActions(std::string sFilter);
	unsigned int Difficulty();
	unsigned int Playtime();
	std::string MapName();
	std::string Time();

	bool NewReplay(std::string sFile);
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

	bool getFromCSVBuilding(unsigned short uiCardID);
	bool getFromCSVSpell(unsigned short uiCardID);
	bool getFromCSVUnit(unsigned short uiCardID);
	void addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building, std::vector <WebCard*>& WebDeck);
	void addColors(std::vector <WebCard*>& WebDeck);
	void InitVector();

	bool FillWebDeckDeck();
	bool FillWebDeckAction();
	bool FillTableBOT2(std::vector <WebCard*>& WebDeck, Wt::WTable *wtTabelle);

	void BOT3WellsAndOrbUnit();
	void FillTableBOT3(Wt::WTable *wtTabelle);

};

#endif //WEB_Replay_H
