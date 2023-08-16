#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"
#include "..\..\incl\Utility.h"

#include "..\..\incl\DataTypes.h"

#include <fstream>

broker *(Tome_Game::Bro) = NULL;

Tome_Game::Tome_Game()
{
	MISS;
	Init();
	MISE;
}

Tome_Game::Tome_Game(std::string _sGameID)
{
	MISS;
	bLoadGame(_sGameID);
	MISE;
}


bool Tome_Game::bLoadGame(std::string _sGameID)
{
	MISS;
	std::string line;
	std::string sName = Bro->L_getTOME_SAVE_PATH() + _sGameID;

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);
	
	Init();

	if (ifFile.good())
	{
		MISD("good");
		bHasGame = true;

		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			//MISD(line);

			//Game Settings
			if (INI_Value_Check(line, "G"))
			{												
				sGameID = entry(line, 0);
				sAdminID = entry(line, 1);
				bShowBoosters = atoi(entry(line, 2).c_str());
				bShowBoostersOfPlayer = atoi(entry(line, 3).c_str());
				bShowBoostersOpenStatus = atoi(entry(line, 4).c_str());
			}
			//Player
			if (INI_Value_Check(line, "P"))
			{
				vPlayer.push_back(new Tome_Player(entry(line, 0), entry(line, 1)));
				for (unsigned int i = 0; i < NumBoostersTypes;i++ )
					vPlayer[vPlayer.size() - 1]->iMaxBoosters[i] = atoi(entry(line, 2 + i).c_str());				
			}

			//Player Booster
			if (INI_Value_Check(line, "PB"))
			{
				vPlayer[vPlayer.size() - 1]->vBoosters.push_back(
					new Tome_Booster(atoi(entry(line, 0).c_str())));

				for (unsigned int i = 0; i < 8; i++)
					vPlayer[vPlayer.size() - 1]->vBoosters[vPlayer[vPlayer.size() - 1]->vBoosters.size() - 1]->vCards.push_back(
						Bro->J_GetSMJCard(atoi(entry(line, 1 + i).c_str())));
			}
				
			ifFile.clear();
		}

		

		//getline(ifFile, line);
		//line.erase(line.size() - 1);
		//TSOUT->GameID = line;
		//ifFile.clear();

		ifFile.close();
	}
	else
	{
		MISEA("No Game");
		return false;
	}

	MISE;
	return true;
}


void Tome_Game::Init()
{
	MISS;
	bHasGame = false;
	bShowBoosters = false;
	bShowBoostersOfPlayer = false;
	bShowBoostersOpenStatus = false;
	sGameID = "";
	sAdminID = "";
	sPlayerID = "";

	vPlayer.clear();
	MISE;
}



bool Tome_Game::bSaveGame()
{
	MISS;
	if (!bHasGame)
	{
		MISEA("No Game")
		return false;
	}
	std::string line;
	std::string sName = Bro->L_getTOME_SAVE_PATH() + sGameID;

	std::ofstream ofFile;
	ofFile.open(sName.c_str(), std::ios::binary);

	if (ofFile.good())
	{
		MISD("good");
		ofFile << "G=" << sGameID
			<< ";" << sAdminID
			<< ";" << bShowBoosters
			<< ";" << bShowBoostersOfPlayer
			<< ";" << bShowBoostersOpenStatus
			<< "\n";
		for (unsigned int i = 0; i < vPlayer.size(); i++)
		{
			ofFile << "P=" << vPlayer[i]->sPlayerID
				<< ";" << vPlayer[i]->sPlayerName << ";";
			for (unsigned int j = 0; j < NumBoostersTypes; j++)
				ofFile << vPlayer[i]->iMaxBoosters[j] << ";";
			ofFile << "\n";

			for (unsigned j = 0; j < vPlayer[i]->vBoosters.size(); j++)
			{
				ofFile << "PB=" << vPlayer[i]->vBoosters[j]->iType << ";";
				for (unsigned k = 0; k < vPlayer[i]->vBoosters[j]->vCards.size(); k++)
					ofFile << vPlayer[i]->vBoosters[j]->vCards[k]->cardId << ";";
				ofFile << "\n";
			}			
		}

		ofFile.close();
	}
	
	MISE;
	return true;
}