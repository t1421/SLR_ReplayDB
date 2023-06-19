#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Utility.h"

#include "..\incl\MIS_Rank.h" 

#include <fstream>
#include <algorithm>

#define MaxReplaysPerTeam 3

broker *(MIS_Rank::Bro) = NULL;

bool comparePlayer(const ROW *a, const ROW *b)
{
	unsigned long aa = 0;
	unsigned long bb = 0;
	for (unsigned int i = 0; i < RankRowStamps; i++)aa += a->Stamps[i];
	for (unsigned int i = 0; i < RankRowStamps; i++)bb += b->Stamps[i];
	return aa < bb;
}

bool comparePlayerField0(const ROW *a, const ROW *b) { return a->Stamps[0] < a->Stamps[0]; }
bool comparePlayerField1(const ROW *a, const ROW *b) { return a->Stamps[1] < a->Stamps[1]; }
bool comparePlayerField2(const ROW *a, const ROW *b) { return a->Stamps[2] < a->Stamps[2]; }
bool comparePlayerField3(const ROW *a, const ROW *b) { return a->Stamps[3] < a->Stamps[3]; }
bool comparePlayerField4(const ROW *a, const ROW *b) { return a->Stamps[4] < a->Stamps[4]; }
/*
bool comparePair(std::pair<std::string, unsigned long> *a, std::pair<std::string, unsigned long> *b)
{	
	return a->second < b->second;
}
*/

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
		CleanList();
		SaveList();
	}
	
	MISE;
	return iReturn;
}

void MIS_Rank::CleanList()
{
	MISS;
	unsigned int iCount = 0;
	for (unsigned int i = 0; i < RankRows.size(); i++)
	{
		iCount = 0;
		for (unsigned int j = i; j < RankRows.size(); j++)
		{
			if (RankRows[i]->ID == RankRows[j]->ID)
			{
				iCount++;
				if (iCount > MaxReplaysPerTeam) RankRows.erase(RankRows.begin() + j);
			}
		}
	}
	MISE;
}


std::vector<ROW*> MIS_Rank::getRankeROW(int iRanking)
{
	if (iRanking == KOTGLIST4) return getRankeKOTG();
	MISS;
	std::vector<ROW*> vReturn;

	for (unsigned int i = 0; i < RankRows.size(); i++)
		vReturn.push_back(RankRows[i]);

	switch (iRanking)
	{
	case KOTGLIST1:
		std::sort(vReturn.begin(), vReturn.end(), comparePlayerField0);
		break;
	case KOTGLIST2:
		std::sort(vReturn.begin(), vReturn.end(), comparePlayerField1);
		break;
	case KOTGLIST3:
		std::sort(vReturn.begin(), vReturn.end(), comparePlayerField2);
		break;
	}
	
	MISE;
	return vReturn;
}


std::vector<ROW*> MIS_Rank::getRankeKOTG()
{
	MISS;
	std::vector<ROW*> vRank0;
	for (unsigned int i = 0; i < RankRows.size(); i++)
		vRank0.push_back(RankRows[i]);
	std::sort(vRank0.begin(), vRank0.end(), comparePlayerField0);

	std::vector<ROW*> vRank1;
	for (unsigned int i = 0; i < RankRows.size(); i++)
		vRank1.push_back(RankRows[i]);
	std::sort(vRank1.begin(), vRank1.end(), comparePlayerField1);

	std::vector<ROW*> vRank2;
	for (unsigned int i = 0; i < RankRows.size(); i++)
		vRank2.push_back(RankRows[i]);
	std::sort(vRank2.begin(), vRank2.end(), comparePlayerField2);


	std::vector<ROW*> vReturn;
	for (unsigned int j = 0; j < RankRows.size(); j++)
	{
		vReturn.push_back(RankRows[j]);
		for (unsigned int i = 0; i < vRank0.size(); i++)		
			if (vReturn[j]->ID == vRank0[i]->ID && vReturn[j]->ReplayID == vRank0[i]->ReplayID)
			{
				vReturn[j]->Stamps[4] = vRank0[i]->Stamps[0];
				vReturn[j]->Stamps[0] = i * 1000000;
				vReturn[j]->Stamps[3] += i;				
			}

		for (unsigned int i = 0; i < vRank1.size(); i++)
			if (vReturn[j]->ID == vRank1[i]->ID && vReturn[j]->ReplayID == vRank1[i]->ReplayID)
			{
				vReturn[j]->Stamps[4] = vRank1[i]->Stamps[1];
				vReturn[j]->Stamps[0] = i * 1000000;
				vReturn[j]->Stamps[3] += i;
			}

		for (unsigned int i = 0; i < vRank2.size(); i++)
			if (vReturn[j]->ID == vRank2[i]->ID && vReturn[j]->ReplayID == vRank2[i]->ReplayID)
			{
				vReturn[j]->Stamps[4] = vRank2[i]->Stamps[2];
				vReturn[j]->Stamps[0] = i * 1000000;
				vReturn[j]->Stamps[3] += i;
			}	
	}

	std::sort(vReturn.begin(), vReturn.end(), comparePlayer);

	MISE;
	return vReturn;
}