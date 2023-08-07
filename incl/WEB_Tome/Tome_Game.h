#ifndef Tome_Game_H
#define Tome_Game_H

struct Tome_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	unsigned int iMaxBoosters[12];
	unsigned int iOpendBoosters[12];
	std::vector<std::pair<int, SMJCard*>> vBoosters;
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
	void Init();

	bool bLoadGame(std::string _sGameID);
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // WEB_Tome_Logout_H
