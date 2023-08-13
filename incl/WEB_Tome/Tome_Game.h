#ifndef Tome_Game_H
#define Tome_Game_H

struct Tome_Booster
{
	unsigned int iType;
	std::vector <SMJCard*> vCards;
	Tome_Booster(unsigned int _iType) :iType(_iType) {};
};

struct Tome_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	unsigned int iMaxBoosters[12] = {0};
	//unsigned int iOpendBoosters[12] = { 0 };
	std::vector<Tome_Booster*> vBoosters;

	Tome_Player(std::string _sPlayerID, std::string _sPlayerName): sPlayerID(_sPlayerID), sPlayerName(_sPlayerName){};
};

class Tome_Game
{
public:

	bool bHasGame;
	bool bShowBoosters;
	bool bShowBoostersOfPlayer;
	bool bShowBoostersOpenStatus;
	std::string sGameID;
	std::string sAdminID;
	std::string sPlayerID;
	std::vector <Tome_Player*> vPlayer;

	Tome_Game();
	Tome_Game(std::string _sGameID);
	void Init();

	bool bLoadGame(std::string _sGameID);
	bool bSaveGame();
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // WEB_Tome_Debug_H
