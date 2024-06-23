#ifndef MIS_Rank_H
#define MIS_Rank_H

#include <mutex> 
#include <vector>


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


class MIS_Rank
{
public:
	MIS_Rank(int iRankList, int _RankMode);
	~MIS_Rank();

	void SaveList();
	void SortList();
	void CleanList();
			
	int AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	std::vector<ROW> getRankeROW();
	//std::vector<ROW> getRankeMultiList();
	int RankMode;
	int RankList;

	std::vector<ROW*> RankRows;
	bool ReCalTotalEEE();
	
	
	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	

private:
	std::string sFile;
	std::mutex mtx;
	
};

#endif //MIS_Rank_H


