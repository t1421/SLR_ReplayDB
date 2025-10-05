#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\CardBaseSMJ.h"
#include "..\..\incl\LOAD.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <fstream>
#include <algorithm>
#include <random>

broker *(LottoWeek::Bro) = NULL;

bool comparePlayer(Lotto_Player * a, Lotto_Player * b) { return a->iPoints() > b->iPoints(); }

bool LottoWeek::bLoadGame(unsigned int _iWeek)
{
	MISS;
	std::string line;
	std::string sName = Bro->L->sLOTTO_SAVE_PATH + std::to_string(_iWeek);

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);
	unsigned int iCountSemi;
	
	mx.lock();
	if (ifFile.good())
	{
		
		MISD("good");

		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			//MainSettings
			if (INI_Value_Check(line, "W"))
			{												
				iWeek = atoi(entry(line, 0).c_str()); 
				iBFP = atoi(entry(line, 1).c_str());
				iStatus = atoi(entry(line, 2).c_str());
				iMapPull = atoi(entry(line, 3).c_str());
				iNumBoosters = atoi(entry(line, 4).c_str());
			}

			//PulledCards
			if (INI_Value_Check(line, "C"))
			{
				iCountSemi = 0;
				for (char character : line)
					if (character == ';')
						iCountSemi++;

				for (unsigned int i = 0; i < iCountSemi +1; i++)
					vCardsPulled.push_back(entry(line, 0 + i).c_str());
				
			}

			//Player
			if (INI_Value_Check(line, "P"))
			{
				vPlayer.push_back(new Lotto_Player(
					entry(line, 0), 
					entry(line, 1),
					entry(line, 2),
					atoi(entry(line, 3).c_str())));
			}

			//Player Cards
			if (INI_Value_Check(line, "PC"))
			{
				iCountSemi = 0;
				for (char character : line) 
					if (character == ';') 
						iCountSemi++;

				for (unsigned int i = 0; i < iCountSemi + 1; i++)
				{
					vPlayer[vPlayer.size() - 1]->vSimpleDeck.push_back(entry(line, 0 + i).c_str());
					vPlayer[vPlayer.size() - 1]->vPoints.push_back(0);
				}
			}
				
			ifFile.clear();
		}
		ifFile.close();
		
	}
	else
	{
		MISEA("No Game");
		mx.unlock();
		return false;
	}
	mx.unlock();

	CalcPulls();

	
	
	MISE;	
	return true;
}


bool LottoWeek::bSaveGame()
{
	MISS;

	std::string line;
	std::string sName = Bro->L->sLOTTO_SAVE_PATH + std::to_string(iWeek);
	
	std::ofstream ofFile;
	ofFile.open(sName.c_str(), std::ios::binary);

	mx.lock();
	if (ofFile.good())
	{
		
		MISD("good");
		ofFile << "W=" << iWeek
			<< ";" << iBFP
			<< ";" << iStatus
			<< ";" << iMapPull
			<< ";" << iNumBoosters
			<< ";\n";

		if (vCardsPulled.size() > 0)
		{
			ofFile << "C=";
			for each(std::string C in vCardsPulled) ofFile << C << ";";
			ofFile << "\n";
		}

		for (unsigned int i = 0; i < vPlayer.size(); i++)
		{
			ofFile << "P=" << vPlayer[i]->sPlayerID
				<< ";" << vPlayer[i]->sPlayerName 
				<< ";" << vPlayer[i]->sGameID
				<< ";" << vPlayer[i]->iMapID
			    << ";\n";
#
			ofFile << "PC=";
			for each (std::string C in vPlayer[i]->vSimpleDeck)ofFile << C << ";";
			ofFile << "\n";	
		}
		ofFile.close();
	}
	
	MISE;
	mx.unlock();
	return true;
}


bool LottoWeek::CheckPlayer(std::string PlayerID)
{
	for each(Lotto_Player* P in vPlayer)
		if (P->sPlayerID == PlayerID)
			return false;		
	return true;
}


std::string LottoWeek::JoinWeek(Lotto_Player *inPlayer)
{
	MISS;
	
	if (!CheckPlayer(inPlayer->sPlayerID))
	{
		MISEA("Already Joined");
		return "Already Joined this Week";
	}

	if(iStatus != 1)
	{
		MISEA("Wrong Status to Join");
		return "Week is Inactiv";
	}

	mx.lock();
	vPlayer.push_back(inPlayer);
	
	//for each(std::string C in Deck)
	//	vPlayer[vPlayer.size() - 1]->vSimpleDeck.push_back(C);
	
	mx.unlock();

	bSaveGame();
	
	MISE;
	return "";
}


void LottoWeek::CalcPulls()
{
	MISS;
	for each(Lotto_Player* P in vPlayer)
	{
		for (unsigned int i = 0; i < P->vSimpleDeck.size(); i++)
		{
			P->vPoints[i] = 0;
			for each(std::string C in vCardsPulled)
			{
				if (P->vSimpleDeck[i] == C)P->vPoints[i] = 1;
			}
		}
		if (P->iMapID == iMapPull)P->iMapPoint = 1;
		else P->iMapPoint = 0;
	}

	std::sort(vPlayer.begin(), vPlayer.end(), comparePlayer);
	MISE;
}

void LottoWeek::setStatus(unsigned int iIN)
{
	MISS;
	if (iIN == 3)	for each (LottoWeek *W in Bro->vWeek)if (W->iStatus == 3)
	{
		W->iStatus = 2;
		W->bSaveGame();
	}
	iStatus = iIN;
	bSaveGame();
	MISE;
}
/*
void LottoWeek::RemovePull(std::string sRmoveCard)
{
	MISS;	
	for (std::vector<std::string>::iterator it = vCardsPulled.begin(); it != vCardsPulled.end();)
	{
		if((*it) == sRmoveCard)it = vCardsPulled.erase(it);
		else  ++it;
	}
	bSaveGame();
	CalcPulls();
	MISE;
}
*/
void LottoWeek::setBFP(unsigned int iIN)
{
	MISS;
	iBFP = iIN;
	bSaveGame();
	MISE;
}
/*
void LottoWeek::AddPull(std::string sRmoveCard)
{
	MISS;
	for (std::string C : vCardsPulled)if (C == sRmoveCard)
	{
		MISEA("Dubeltte")
		return;
	}
	vCardsPulled.push_back(sRmoveCard);
	bSaveGame();
	CalcPulls();
	MISE;
}
*/
void LottoWeek::setMap(unsigned int iIN)
{
	MISS;
	iMapPull = iIN;
	bSaveGame();
	CalcPulls();
	MISE;
}

bool LottoWeek::PullCard()
{
	MISS;
	int iRandome;
	if (vCardPool.size() == 0)
	{
		for (auto* C : Bro->J->SMJMatrix)vCardPool.push_back(C->cardNameSimple);
		sort(vCardPool.begin(), vCardPool.end());
		vCardPool.erase(unique(vCardPool.begin(), vCardPool.end()), vCardPool.end());

		for each(std::string C in vCardsPulled)RemoveFromPool(C);
	}
	if (vCardPool.size() == 0)
	{
		MISEA("You pulled all cards xD");
		return false;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(0, vCardPool.size() - 1);

	iRandome = distr(gen);
	vCardsPulled.push_back(vCardPool[iRandome]);
	RemoveFromPool(vCardPool[iRandome]);

	MISE;
	return true;
}

void LottoWeek::RemoveFromPool(std::string sRemove)
{
	MISS;
	for (std::vector<std::string>::iterator it = vCardPool.begin(); it != vCardPool.end();)
	{
		if ((*it) == sRemove)it = vCardPool.erase(it);
		else  ++it;
	}
	MISE;
}

void LottoWeek::OpenBooster()
{
	MISS;
	
	for (unsigned int i = 0; i < 8; i++)PullCard();

	bSaveGame();
	CalcPulls();
	MISE;
}


std::string LottoWeek::OpenMap(std::vector<std::string> vMaps)
{
	MISS;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(1, vMaps.size() - 1);
	MISE;
	return vMaps[distr(gen)];
}