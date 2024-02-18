#ifndef LottoWeek_H
#define LottoWeek_H

#include "..\DataTypes.h"


struct Lotto_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	std::string sGameID;
	std::vector<std::string> vSimpleDeck;

	Lotto_Player(std::string _sPlayerID, std::string _sPlayerName, std::string _sGameID) :
		sPlayerID(_sPlayerID), sPlayerName(_sPlayerName), sGameID(_sGameID){};
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
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // LottoWeek_H
