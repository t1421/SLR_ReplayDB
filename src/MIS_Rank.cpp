#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Utility.h"
#include "..\incl\DataTypes.h"

#include "..\incl\MIS_Rank.h" 

#include <fstream>
#include <algorithm>

#define MaxReplaysPerTeam 1

broker *(MIS_Rank::Bro) = NULL;
/*
bool comparePlayer(const ROW * a, const ROW * b)
{
	unsigned long aa = 0;
	unsigned long bb = 0;
	for (unsigned int i = 0; i < RankRowStamps; i++)aa += a->Stamps[i];
	for (unsigned int i = 0; i < RankRowStamps; i++)bb += b->Stamps[i];
	return aa < bb;
}


bool comparePlayerX(const ROW& a, const ROW& b)
{
	unsigned long aa = 0;
	unsigned long bb = 0;
	for (unsigned int i = 0; i < RankRowStamps; i++)aa += a.Stamps[i];
	for (unsigned int i = 0; i < RankRowStamps; i++)bb += b.Stamps[i];
	return aa < bb;
}
*/

bool comparePlayerFieldID(const ROW * a, const ROW * b) { return atoi(a->ID.c_str()) < atoi(b->ID.c_str()); }
bool comparePlayerField0(const ROW * a, const ROW * b) { return a->Stamps[0] < b->Stamps[0]; }
bool comparePlayerField1(const ROW * a, const ROW * b) { return a->Stamps[1] < b->Stamps[1]; }
bool comparePlayerField0Rev(const ROW * a, const ROW * b) { return a->Stamps[0] > b->Stamps[0]; }
/*
bool comparePlayerXField0(const ROW& a, const ROW& b) { return a.Stamps[0] < b.Stamps[0]; }
bool comparePlayerXField1(const ROW& a, const ROW& b) { return a.Stamps[1] < b.Stamps[1]; }
bool comparePlayerXField2(const ROW& a, const ROW& b) { return a.Stamps[2] < b.Stamps[2]; }
bool comparePlayerXField3(const ROW& a, const ROW& b) { return a.Stamps[3] < b.Stamps[3]; }
bool comparePlayerXField4(const ROW& a, const ROW& b) { return a.Stamps[4] < b.Stamps[4]; }
*/

bool comparePlayerField1_0(const ROW * a, const ROW * b) 
{ 
	if (a->Stamps[1] < b->Stamps[1]) return true;
	else if (a->Stamps[1] > b->Stamps[1]) return false;

	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	return true;
}

bool comparePlayerFieldStage(const ROW * a, const ROW * b)
{
	for (unsigned int i = 0; i < RankRowStamps; i++)
	{
		if (a->Stamps[i] > b->Stamps[i]) return true;
		else if (a->Stamps[i] < b->Stamps[i]) return false;
	}	
	return true;
}

bool comparePlayerFieldEEE_DEF(const ROW * a, const ROW * b)
{ 
	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	return true;
}

bool comparePlayerFieldEEE_3_5(const ROW * a, const ROW * b)
{
	if (a->Stamps[0] > b->Stamps[0]) return true;
	else if (a->Stamps[0] < b->Stamps[0]) return false;

	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	return true;
}

bool comparePlayerFieldEEE_7(const ROW * a, const ROW * b)
{
	if (a->Stamps[0] > b->Stamps[0]) return true;
	else if (a->Stamps[0] < b->Stamps[0]) return false;

	if (a->Stamps[1] < b->Stamps[1]) return true;
	else if (a->Stamps[1] > b->Stamps[1]) return false;

	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	return true;
}

bool comparePlayerFieldEEE_2(const ROW * a, const ROW * b)
{
	if (a->Stamps[1] < b->Stamps[1]) return true;
	else if (a->Stamps[1] > b->Stamps[1]) return false;

	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	return true;
}


bool compare_1HL_0LH(const ROW* a, const ROW* b)
{	
	if (a->Stamps[1] > b->Stamps[1]) return true;
	else if (a->Stamps[1] < b->Stamps[1]) return false;

	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	return true;
}

bool compare_2LH_1LH_0LH(const ROW* a, const ROW* b)
{
	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	if (a->Stamps[1] < b->Stamps[1]) return true;
	else if (a->Stamps[1] > b->Stamps[1]) return false;

	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	return true;
}

bool compare_2LH_0LH(const ROW* a, const ROW* b)
{
	if (a->Stamps[2] < b->Stamps[2]) return true;
	else if (a->Stamps[2] > b->Stamps[2]) return false;

	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	return true;
}

bool compare_0LH_1HL_2HL(const ROW* a, const ROW* b)
{
	if (a->Stamps[0] < b->Stamps[0]) return true;
	else if (a->Stamps[0] > b->Stamps[0]) return false;

	if (a->Stamps[1] > b->Stamps[1]) return true;
	else if (a->Stamps[1] < b->Stamps[1]) return false;

	if (a->Stamps[2] > b->Stamps[2]) return true;
	else if (a->Stamps[2] < b->Stamps[2]) return false;	

	return true;
}


unsigned int RANKtoPOINTS(unsigned int iRank)
{
	switch (iRank)	{
	case 1: return 15;
	case 2: return 12;
	case 3: return 10;
	case 4: return 8;
	case 5: return 6;
	case 6: return 5;
	case 7: return 4;
	case 8: return 3;
	case 9: return 2;
	case 10: return 1;
	}
	return 0;
}


MIS_Rank::MIS_Rank(int iRankList): sFile(std::to_string(iRankList) + ".csv"), RankList(iRankList)
{
	MISS;
	MISD("RankList:" + std::to_string(iRankList));
	RankMode = 90;
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
	switch (RankList)
	{
	case 0:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerField0Rev);
		break;
	case 2:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldEEE_2);
		break;
	case 3:
	case 5:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldEEE_3_5);
		break;
	case 7:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldEEE_7);
		break;
	case 1:	
	case 4:
	case 6:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldEEE_DEF);
		break;
	case 8:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerField1_0);
		break;		
	case 9:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldID);
		break;
	case 10:
	case 15:
		std::sort(RankRows.begin(), RankRows.end(), compare_1HL_0LH);
		break;
	case 11:
		std::sort(RankRows.begin(), RankRows.end(), compare_2LH_0LH);
		break;
	case 13:		
		std::sort(RankRows.begin(), RankRows.end(), compare_0LH_1HL_2HL);
		break;
	default:
		std::sort(RankRows.begin(), RankRows.end(), comparePlayerFieldStage);
		break;
	}
	mtx.unlock();
	
	MISE;
}

int MIS_Rank::AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps])
{
	unsigned long BestRunStamps[RankRowStamps];
	return AddPlayer(_ID, _ReplayID, _Stamps, BestRunStamps);
}

int MIS_Rank::AddPlayer(std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps], unsigned long BestRunStamps[RankRowStamps])
{
	MISS;
	int iReturn = 0;
	bool bUpdate = false;
	mtx.lock();

	MISD(RankMode);
	ROW* R_Temp = new ROW();
	R_Temp->ID = _ID;
	R_Temp->ReplayID = _ReplayID;
	for (unsigned int j = 0; j < RankRowStamps; j++) R_Temp->Stamps[j] = _Stamps[j];			
	RankRows.push_back(R_Temp);	

	if (RankMode == 1)RankRows.pop_back();

	mtx.unlock();

	if (RankMode > 1 && RankMode < 10)
	{	
		SortList();
		if (RankList == 101)FusionList();
		CleanList();
		SaveList();

		iReturn = 0;		
		//for (auto R : RankRows)
		for ( unsigned int i = 0; i < RankRows.size(); i++)
		{
			if (RankRows[i]->ID == _ID)
			{
				for (unsigned int j = 0; j < RankRowStamps; j++)BestRunStamps[j] = RankRows[i]->Stamps[j] ;
				BestRunStamps[RankRowStamps - 1] = i;
				
			}
			if (RankRows[i]->ReplayID == _ReplayID)iReturn = 1;
		}
		
		
	}
	
	MISD(std::to_string(iReturn));
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


std::vector<ROW> MIS_Rank::getRankeROW(std::string _ID_Filter)
{	
	MISS;
	std::vector<ROW> vReturn;	
	SortList();
	for (const auto& rowPtr : RankRows) vReturn.push_back(*rowPtr);	
	if (_ID_Filter != "")for (unsigned int i = 0; i < vReturn.size(); i++)
	{
		if (!(i > 0 && vReturn[i - 1].ID == _ID_Filter
			|| i < vReturn.size() - 1 && vReturn[i + 1].ID == _ID_Filter
			|| vReturn[i].ID == _ID_Filter))
		{
			vReturn.erase(vReturn.begin() + i--);
		}
	}

	MISE;
	return vReturn;
}


void MIS_Rank::FusionList()
{
	MISS;

	for (unsigned int i = 0; i < RankRows.size(); i++)
	{
		for (unsigned int j = i + 1; j < RankRows.size(); j++)
		{
			if (RankRows[i]->ID == RankRows[j]->ID)
			{
				RankRows[i]->Stamps[0] = (RankRows[i]->Stamps[0] == 1 || RankRows[j]->Stamps[0] == 1);
				RankRows[i]->Stamps[1] = (RankRows[i]->Stamps[1] == 1 || RankRows[j]->Stamps[1] == 1);
				RankRows[i]->Stamps[2] = (RankRows[i]->Stamps[2] == 1 || RankRows[j]->Stamps[2] == 1);
				RankRows[i]->Stamps[3] = (RankRows[i]->Stamps[3] == 1 || RankRows[j]->Stamps[3] == 1);
				RankRows[i]->Stamps[4] = (RankRows[i]->Stamps[4] == 1 || RankRows[j]->Stamps[4] == 1);
				RankRows[i]->Stamps[5] = (RankRows[i]->Stamps[5] == 1 || RankRows[j]->Stamps[5] == 1);
				RankRows.erase(RankRows.begin() + j);
			}
		}
	}
	MISE;
}