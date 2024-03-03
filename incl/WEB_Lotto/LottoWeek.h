#ifndef LottoWeek_H
#define LottoWeek_H

#include "..\DataTypes.h"


struct Lotto_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	std::string sGameID;
	std::string sMapName;
	
	std::vector<std::string> vSimpleDeck;

	unsigned int iPoints;

	Lotto_Player(std::string _sPlayerID, std::string _sPlayerName, std::string _sGameID, std::string _sMapName) :
		sPlayerID(_sPlayerID), sPlayerName(_sPlayerName), sGameID(_sGameID), sMapName(_sMapName), iPoints(0){};
	Lotto_Player() :
		sPlayerID(""), sPlayerName(""), sGameID(""), sMapName(""), iPoints(0) {};
};

class LottoWeek
{
public:

	std::vector <Lotto_Player*> vPlayer;
	std::vector<std::string> vCardsPulled;
	unsigned int iWeek;
	unsigned int iBFP;
	unsigned int iStatus;

	LottoWeek() : iWeek(0), iBFP(0), iStatus(0){};
	
	bool bLoadGame(unsigned int _iWeek);
	bool bSaveGame();
	std::mutex mx;
	
	bool CheckPlayer(std::string PlayerID);
	std::string JoinWeek(Lotto_Player *inPlayer);

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // LottoWeek_H
