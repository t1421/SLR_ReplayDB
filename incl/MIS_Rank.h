#ifndef MIS_Rank_H
#define MIS_Rank_H

#include <mutex> 
#include <vector>





class MIS_Rank
{
public:
	MIS_Rank(int iRankList);
	~MIS_Rank();

	void SaveList();
	void SortList();
	void CleanList();
	void FusionList();
			
	int AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	int AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps], unsigned long BestRunStamps[RankRowStamps]);
	std::vector<ROW> getRankeROW(std::string _ID_Filter);
	int RankMode;
	int RankList;

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


