#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Utility.h"

#include "..\incl\MIS_Rank.h" 

#include <fstream>
#include <algorithm>

broker *(MIS_Rank::Bro) = NULL;

bool comparePlayer(const ROW *a, const ROW *b)
{
	unsigned long aa = 0;
	unsigned long bb = 0;
	for (unsigned int i = 0; i < RankRowStamps; i++)aa += a->Stamps[i];
	for (unsigned int i = 0; i < RankRowStamps; i++)bb += b->Stamps[i];
	return aa < bb;
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
		MISEA("Error for Rank list: " + std::to_string(iRankList));
		return;
	}
	mtx.lock();
	while (getline(ifFile, line))
	{
		R_Temp = new ROW();
		R_Temp->ID = entry(line, 0);
		R_Temp->ReplayID = std::atoi(entry(line, 1).c_str());
		for (unsigned int i = 0; i < RankRowStamps; i++) R_Temp->Stamps[i] = std::atoi(entry(line, 2 + i).c_str());
				
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
			//ofFile << RankRows[i]->Player << ";" << RankRows[i]->Time << ";" << RankRows[i]->Name << std::endl;
			ofFile << RankRows[i]->ID << ";" << RankRows[i]->ReplayID << ";";
			for (unsigned int j = 0; j < RankRowStamps; j++) ofFile << RankRows[i]->Stamps[j] << ";";
			ofFile << std::endl;
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

//int MIS_Rank::AddPlayer(std::string PMVPlayerID, unsigned long _Order, std::string &sRankName, unsigned long _Points, unsigned long _Time)
int MIS_Rank::AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps])
{
	MISS;
	int iReturn = 0;
	unsigned int i;
	bool bUpdate = false;
	//MISD(sRankName);
	mtx.lock();
	for (i = 0; i < RankRows.size(); i++)
	{
		if (RankRows[i]->ID == _ID && RankRows[i]->ReplayID == _ReplayID)
		{
			for (unsigned int j = 0; j < RankRowStamps; j++) if (RankRows[i]->Stamps[j] > _Stamps[j]) bUpdate = true;
			if (bUpdate)
			{
				MISD("Player vorhanden, Time Updated");
				if (RankMode != 1)
				{
					for (unsigned int j = 0; j < RankRowStamps; j++) RankRows[i]->Stamps[j] = _Stamps[j];
				}
				iReturn = 10;
				break;
			}
			else //if (RankRows[i]->Order == _Order)
			{
				MISD("Player vorhanden, Time Gleich / schlechtere zeit");
				//RankRows[i]->Order = _Order;
				//RankRows[i]->Time = _Time;
				//RankRows[i]->Points = _Points;
				iReturn = 9;
				break;
			}
			/*
			else
			{
				MISD("Player vorhanden, Time Slower");
				iReturn = 5;
				break;
			}*/
		}
	}
	if (iReturn == 0)
	{
		MISD("New Player");
		ROW* R_Temp = new ROW();
		R_Temp->ID = _ID;
		R_Temp->ReplayID = _ReplayID;
		for (unsigned int j = 0; j < RankRowStamps; j++) R_Temp->Stamps[j] = _Stamps[j];		
		
		//Team name definieren
		if (RankMode != 1)Bro->GetTeamName(_ID);
		/*
		if (RankMode == 1)sRankName = "Player"; 
		else
		{
			if (sRankName == "")R_Temp->Name = Bro->getName();
			else R_Temp->Name = sRankName;
			sRankName = R_Temp->Name;
			
		}
		*/
		RankRows.push_back(R_Temp);
		i = RankRows.size() - 1;
		iReturn = 15;
	}
	//else if(sRankName=="")sRankName = RankRows[i]->Name;
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


