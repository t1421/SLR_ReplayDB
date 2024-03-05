#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <fstream>
#include <algorithm>

broker *(LottoWeek::Bro) = NULL;

bool comparePlayer(Lotto_Player * a, Lotto_Player * b) { return a->iPoints() < b->iPoints(); }

bool LottoWeek::bLoadGame(unsigned int _iWeek)
{
	MISS;
	std::string line;
	std::string sName = Bro->L_getLOTTO_SAVE_PATH() + std::to_string(_iWeek);

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
			}

			//PulledCards
			if (INI_Value_Check(line, "C"))
			{
				iCountSemi = 0;
				for (char character : line)
					if (character == ';')
						iCountSemi++;

				for (unsigned int i = 0; i < iCountSemi; i++)
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

				for (unsigned int i = 0; i < iCountSemi - 1; i++)
				{
					vPlayer[vPlayer.size() - 1]->vSimpleDeck.push_back(entry(line, 2 + i).c_str());
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
	std::string sName = Bro->L_getLOTTO_SAVE_PATH() + std::to_string(iWeek);
	
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
			<< ";\n";

		ofFile << "C=";
		for each(std::string C in vCardsPulled) ofFile << C << ";";
		ofFile << "\n";

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
			for each(std::string C in vCardsPulled)
			{
				if (P->vSimpleDeck[i] == C)P->vPoints[i] = 1;
			}
		}
		if (P->iMapID == iMapPull)P->iMapPoint = 1;
	}

	std::sort(vPlayer.begin(), vPlayer.end(), comparePlayer);
	MISE;
}