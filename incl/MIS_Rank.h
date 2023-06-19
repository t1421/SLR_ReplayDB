#ifndef MIS_Rank_H
#define MIS_Rank_H

#include <mutex> 
#include <vector>

#define RankRowStamps 3
struct ROW {
	std::string ID;
	unsigned long ReplayID;
	unsigned long Stamps[RankRowStamps];
	ROW() {}
	ROW(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps], unsigned long _Points, unsigned long _Order) :
		ID(_ID), ReplayID(_ReplayID) { for (unsigned int i = 0; i < RankRowStamps; i++)Stamps[i] = _Stamps[i]; }
	/*
	//unsigned long long Player;
	std::string Player;
	unsigned long Time;
	unsigned long Points;
	unsigned long Order;
	std::string Name;
	
	ROW() {}
	ROW(std::string _Player, unsigned long _Time,	std::string _Name, unsigned long _Points, unsigned long _Order)  :
		Player( _Player), Time ( _Time), Name (_Name), Points(_Points), Order(_Order){}
		*/
};


class MIS_Rank
{
public:
	MIS_Rank(int iRankList, int _RankMode);
	~MIS_Rank();

	void SaveList();
	void SortList();
		
	//int AddPlayer(std::string PMVPlayerID, double Playtime, std::string &sRankName);
	//int AddPlayer(std::string PMVPlayerID, unsigned long _Order, std::string &sRankName, unsigned long _Points, unsigned long _Time);
	int MIS_Rank::AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	int RankMode;

	std::vector<ROW*> RankRows;
	
	
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	

private:
	std::string sFile;
	std::mutex mtx;
	
};

#endif //MIS_Rank_H


