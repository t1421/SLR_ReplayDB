//#define DF_Debug

#include "..\incl\Broker.h" 

#include "..\incl\MIS_Rank.h" 

#include <fstream>
#include <algorithm>

broker *(MIS_Rank::Bro) = NULL;

bool comparePlayer(const ROW *a, const ROW *b)
{
	return a->Time < b->Time;
}

MIS_Rank::MIS_Rank(int iRankList, int _RankMode): sFile(std::to_string(iRankList) + ".csv"), RankMode(_RankMode)
{
	MISS;

	//Load List
	std::string line;
	ROW* R_Temp;
	std::ifstream ifFile;
	
	
	ifFile.open(Bro->L_getRANK_PATH() + sFile.c_str(), std::ios::binary);
	if (!ifFile.good())
	{
		MISEA("Error for Rank list");
		return;
	}
	mtx.lock();
	while (getline(ifFile, line))
	{
		R_Temp = new ROW();
		R_Temp->Player = atoi(line.substr(0, line.find(";")).c_str());
		line.erase(0, line.find(";") + 1);
		R_Temp->Time = std::stod(line.substr(0, line.find(";")).c_str());
		line.erase(0, line.find(";") + 1);
		R_Temp->Name = line.substr(0, line.find(";")).c_str();
		
		RankRows.push_back(R_Temp);
		ifFile.clear();
	}
	mtx.unlock();
	ifFile.close();
	
	MISE;
}

MIS_Rank::~MIS_Rank()
{
	MISS;
	
	MISE;
}

void MIS_Rank::SaveList()
{
	MISS;
	std::ofstream ofFile;
	ofFile.open(Bro->L_getRANK_PATH() + sFile.c_str(), std::ios::binary);
	if (ofFile.good())
	{
		mtx.lock();
		for (unsigned int i = 0; i < RankRows.size(); i++)
		{
			ofFile << RankRows[i]->Player << ";" << RankRows[i]->Time << ";" << RankRows[i]->Name << std::endl;
		}
		mtx.unlock();
		ofFile.close();

	}
	else MISEA("Error for Rank list");
	MISE;
}


void MIS_Rank::SortList()
{
	MISS;

	mtx.lock();
	std::sort(RankRows.begin(), RankRows.end(), comparePlayer);
	mtx.unlock();

	MISE;
}


int MIS_Rank::AddPlayer(unsigned long long PMVPlayerID, double Playtime, std::string &sRankName)
{
	MISS;
	int iReturn = 0;
	unsigned int i;

	mtx.lock();
	for (i = 0; i < RankRows.size(); i++)
	{
		if (RankRows[i]->Player == PMVPlayerID)
		{
			if (RankRows[i]->Time > Playtime)
			{
				MISD("Player vorhanden, Time Updated");
				if (RankMode != 1)RankRows[i]->Time = Playtime;
				iReturn = 10;
				break;
			}
			else if (RankRows[i]->Time == Playtime)
			{
				MISD("Player vorhanden, Time Gleich");
				RankRows[i]->Time = Playtime;
				iReturn = 9;
				break;
			}
			else
			{
				MISD("Player vorhanden, Time Slower");
				iReturn = 5;
				break;
			}
		}
	}
	if (iReturn == 0)
	{
		MISD("New Player");
		ROW* R_Temp = new ROW();
		R_Temp->Player = PMVPlayerID;
		R_Temp->Time = Playtime;
		if (RankMode == 1)sRankName = "Player"; 
		else
		{
			R_Temp->Name = Bro->getName();
			sRankName = R_Temp->Name;
		}
		
		RankRows.push_back(R_Temp);
		i = RankRows.size() - 1;
		iReturn = 15;
	}
	else sRankName = RankRows[i]->Name;
	if (RankMode == 1 && iReturn == 15)RankRows.pop_back();
	
	
	mtx.unlock();

	if (iReturn > 9
		&& RankMode != 1)
	{		
		SortList();
		SaveList();
	}
	
	MISE;
	return iReturn;
}


