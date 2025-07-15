#ifndef DataTypes_H
#define DataTypes_H

#if defined BrokerTome || defined BrokerWeb
#include <Wt/WCheckBox.h>
#endif

#if defined BrokerLotto
#include <Wt/WImage.h>
#endif

enum SMJPicType { Small, Big, ImgOnly, Lotto };

struct Allied {
	unsigned char i;
	unsigned char j;
	unsigned char v;
};

struct Team {
	std::string Name;
	unsigned long GroupID;
	unsigned short Value;
};

struct Card {
	unsigned short DeckCardID;
	unsigned long  CardFull;
	unsigned short CardID;
	unsigned short Upgrade;
	unsigned char  Charges;
	unsigned long  count;
};

struct Player {
	std::string Name;
	unsigned long long PlayerID;
	unsigned long ActionPlayer;
	unsigned char GroupID;
	unsigned char IDinGroup;
	unsigned char Type;
	//unsigned char Cards;
	unsigned short CardsTotal;
	std::vector <Card*> Deck;
#if defined BrokerTome || defined BrokerWeb || defined BrokerLotto
	Wt::WCheckBox *wcBox;
	unsigned int iActionCount;
#endif 
#if defined BrokerPVP
	unsigned int iSaveID;
	std::vector <unsigned short> ActionsPerSec;
	std::vector <unsigned short> LastPlayStack;
#endif 
};

struct Action {
	unsigned long Time;
	//unsigned long Size;

	unsigned long Type;
	unsigned long Card;
	unsigned long Upgrade;
	unsigned long CardFull;

	unsigned long ActionPlayer;
	unsigned long long PlayerID;
	unsigned char Charges;

	unsigned int Position;
	float X;
	float Y;

	std::string AdditionalInfo;
	//std::string sActionName;
	

	Action() :Time(0), Type(0), Card(0), Upgrade(0), CardFull(0), ActionPlayer(0), PlayerID(0), Charges(0), AdditionalInfo(), X(0),Y(0) //, sActionName()
	{}

	//unsigned long Unit;
	//unsigned short UnitCount;

	//unsigned short Cardx;
	//unsigned short Cardy;
	//unsigned short Cardz;

	//unsigned long X;
	//unsigned long Y;
	//unsigned long Zero;

	//unsigned char Unknow8;

};

struct ActionSum {
	std::string sActionName;
	unsigned long ActionID;
	unsigned int iCount;
#if defined BrokerTome || defined BrokerWeb || defined BrokerLotto
	Wt::WCheckBox *wcBox;
	unsigned int iActionCount;
#endif 
};


struct ActionWeb {
	unsigned long Time;

	std::string Info;
	std::string sActionName;
	std::string sPlayerName;

	//int iImage;

	ActionWeb() : Time(0), Info(), sActionName(), sPlayerName()	{}
};

struct SMJCard {
	unsigned short cardId;
	std::string SMJid;
	std::string cardName;
	std::string cardNameSimple;
	char color;
	unsigned char orbsTotal;
	unsigned char orbsNeutral;
	unsigned char orbsFire;
	unsigned char orbsShadow;
	unsigned char orbsNature;
	unsigned char orbsFrost;
	unsigned char orbsFireShadow;
	unsigned char orbsNatureFrost;
	unsigned char orbsFireNature;
	unsigned char orbsShadowFrost;
	unsigned char orbsShadowNature;
	unsigned char orbsFireFrost;
	unsigned char type;
	unsigned char maxCharges;
	unsigned int powerCost[4];
	char affinity;
	char rarity;
	char promo;
	std::vector <int> vBoosters;
	bool reforged;
};


struct Tome_Booster
{
	std::string sType;
	std::vector <SMJCard*> vCards;
	Tome_Booster(std::string _sType) :sType(_sType) {};
	unsigned int iLfdnr;
};

struct ROW {
	std::string ID;
	unsigned long ReplayID;
	unsigned long Stamps[RankRowStamps];
	ROW() {}
	ROW(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]) :
		ID(_ID), ReplayID(_ReplayID) {
		for (unsigned int i = 0; i < RankRowStamps; i++)Stamps[i] = _Stamps[i];
	}
	ROW(std::string _ID, unsigned long _ReplayID) :
		ID(_ID), ReplayID(_ReplayID) {
		for (unsigned int i = 0; i < RankRowStamps; i++)Stamps[i] = 0;
	}

};

struct EventData
{
	std::string Name;
	int Start;
	int End;
	int Hide;
	unsigned int RankType;
};

#endif //DataTypes


