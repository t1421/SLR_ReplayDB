#ifndef Tome_Game_H
#define Tome_Game_H

#define NumBoostersTypes 14 + 1
#include "..\DataTypes.h"

bool compareBoostersLfdnr(const Tome_Booster* a, const Tome_Booster* b);
bool compareBoostersType(const Tome_Booster* a, const Tome_Booster* b);

bool compareCardColour(const std::unique_ptr<SMJCard>& a, const std::unique_ptr<SMJCard>& b);
bool compareCardRarity(const std::unique_ptr<SMJCard>& a, const std::unique_ptr<SMJCard>& b);
bool compareCardID(const std::unique_ptr<SMJCard>& a, const std::unique_ptr<SMJCard>& b);

struct Tome_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	unsigned int iMaxBoosters[NumBoostersTypes] = {0};
	//unsigned int iOpendBoosters[12] = { 0 };
	std::vector<Tome_Booster*> vBoosters;

	Tome_Booster* ReforgeBooster;

	Tome_Player(std::string _sPlayerID, std::string _sPlayerName): sPlayerID(_sPlayerID), sPlayerName(_sPlayerName) 
	{
		ReforgeBooster = new Tome_Booster("-91");
		for (unsigned int i = 0; i < 5; i++)
			ReforgeBooster->vCards.push_back(std::make_unique<SMJCard>(0));
	};
	unsigned int iOpendBoostersSum()
	{
		unsigned int iReturn = 0;
		for (unsigned int i = 0; i < vBoosters.size(); i++) if (vBoosters[i]->sType != "-91")iReturn++;
		return iReturn;
	};
	unsigned int iMaxBoostersSum()
	{
		unsigned int iReturn = 0;
		for (unsigned int i = 0; i < NumBoostersTypes; i++) iReturn += iMaxBoosters[i];
		return iReturn;
	};
	unsigned int iOpenBoosterOfType(std::string _Type)
	{
		unsigned int iReturn = 0;
		for (unsigned int i = 0; i < vBoosters.size(); i++) if(vBoosters[i]->sType == _Type)iReturn++;
		return iReturn;
	};
	~Tome_Player() {
		for (auto card : vBoosters) {
			delete card;
		}
		vBoosters.clear();
	}
};

class Tome_Game
{
public:

	int iVersion;
	bool bHasGame;

	std::string sGameID;
	std::string sAdminID;

	bool bShowGlobalBoosterProgress;

	bool bTapShowPlayer;
	bool bTapShowPlayerBoosterOpen;
	bool bTapShowPlayerBoosterMax;

	bool bTapShowBooster;
	bool bTapShowBoosterUR;
	bool bTapShowBoosterR;
	bool bTapShowBoosterUC;
	bool bTapShowBoosterC;
	unsigned int iTapShowBoosterOrder;

	bool bTapShowCards;
	bool bTapShowCardsUR;
	bool bTapShowCardsR;
	bool bTapShowCardsUC;
	bool bTapShowCardsC;
	unsigned int iTapShowCardsOrder;

	bool bTapShowBoosterPerPlayer;
	bool bTapShowBoosterPerPlayerUR;
	bool bTapShowBoosterPerPlayerR;
	bool bTapShowBoosterPerPlayerUC;
	bool bTapShowBoosterPerPlayerC;
	bool bTapShowBoosterPerPlayerBooster;
	unsigned int iTapShowBoosterPerPlayerOrder;

	bool bAllowOpening;
	bool bNoDoubleBooster;

	bool bAllowRefroging;	
	bool bNoDoubleReforging;

	bool bNoAffinities;
	bool bNoPromos;


	std::vector <Tome_Player*> vPlayer;

	Tome_Game();
	Tome_Game(std::string _sGameID);

	void Init();
	void AddPlayer();
	unsigned int AllBoosters();
	unsigned int AllBoostersMax();

	bool bNewGame();	
	bool bCheckPlayer(std::string sPlayer);

	bool bLoadGame(std::string _sGameID);
	bool bSaveGame();
	int iGetPlayerIndex(std::string sPlayerID);
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	~Tome_Game() {
		for (auto card : vPlayer) {
			delete card;
		}
		vPlayer.clear();
	}

};


#endif // WEB_Tome_Debug_H
