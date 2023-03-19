#ifndef MIS_Rank_H
#define MIS_Rank_H

#include <mutex> 
#include <vector>


struct ROW {
	unsigned long long Player;
	double Time;
	std::string Name;
};


class MIS_Rank
{
public:
	MIS_Rank(int iRankList, int _RankMode);
	~MIS_Rank();

	void SaveList();
	void SortList();
	int AddPlayer(unsigned long long PMVPlayerID, double Playtime, std::string &sRankName);
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


