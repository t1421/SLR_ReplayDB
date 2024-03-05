#ifndef LottoWeek_H
#define LottoWeek_H

#include "..\DataTypes.h"

#include <numeric>

struct Lotto_Player
{
	std::string sPlayerID;
	std::string sPlayerName;
	std::string sGameID;
	unsigned int iMapID;
	unsigned int iMapPoint;
	
	std::vector<std::string> vSimpleDeck;
	std::vector<unsigned int> vPoints;	

	Lotto_Player(std::string _sPlayerID, std::string _sPlayerName, std::string _sGameID, unsigned int _iMapID) :
		sPlayerID(_sPlayerID), sPlayerName(_sPlayerName), sGameID(_sGameID), iMapID(_iMapID), iMapPoint(0){};
	Lotto_Player() :
		sPlayerID(""), sPlayerName(""), sGameID(""), iMapID(0), iMapPoint(0) {};
	unsigned int iPoints()
	{
		return std::accumulate(vPoints.begin(), vPoints.end(), 0) + iMapPoint;
	}
};

class LottoWeek
{
public:

	std::vector <Lotto_Player*> vPlayer;
	std::vector<std::string> vCardsPulled;
	unsigned int iMapPull;
	unsigned int iWeek;
	unsigned int iBFP;
	unsigned int iStatus;

	LottoWeek() : iWeek(0), iBFP(0), iStatus(0){};
	
	bool bLoadGame(unsigned int _iWeek);
	bool bSaveGame();
	std::mutex mx;
	
	bool CheckPlayer(std::string PlayerID);
	std::string JoinWeek(Lotto_Player *inPlayer);
	void CalcPulls();

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // LottoWeek_H
