#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"
#include "..\..\incl\Utility.h"

#include "..\..\incl\DataTypes.h"

#include <fstream>
#include <random>

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
	if (_sGameID == "NEW")bNewGame();
	else bLoadGame(_sGameID);
	MISE;
}

bool Tome_Game::bNewGame()
{
	MISS;

	Init();

	std::ifstream ifFile;
	std::string sName;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(100000, 999999 - 1);
	//iRandome = distr(gen);

	do
	{
		if (ifFile.good()) ifFile.close();
		sGameID = std::to_string(distr(gen));
		sName = Bro->L_getTOME_SAVE_PATH() + sGameID;
		ifFile.open(sName.c_str(), std::ios::binary);
	} while (ifFile.good());

	sAdminID = std::to_string(distr(gen));

	bHasGame = true;
	bSaveGame();

	MISE;
	return true;
}

bool Tome_Game::bLoadGame(std::string _sGameID)
{
	MISS;
	std::string line;
	std::string sName = Bro->L_getTOME_SAVE_PATH() + _sGameID;

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);
	unsigned int iCountSemi;
	
	Init();
	iVersion = 0;

	if (ifFile.good())
	{
		MISD("good");
		bHasGame = true;

		while (getline(ifFile, line))
		{
			
			//line.erase(line.size() - 1);
			line.erase(line.size());
			//MISD(line);
			if (INI_Value_Check(line, "V"))iVersion = atoi(line.c_str());
			
			if (INI_Value_Check(line, "GameID"))sGameID = line.c_str();
			if (INI_Value_Check(line, "AdminID"))sAdminID = line.c_str();

			if (INI_Value_Check(line, "ShowGlobalBoosterProgress"))bShowGlobalBoosterProgress = atoi(line.c_str());

			if (INI_Value_Check(line, "TapShowPlayer"))bTapShowPlayer = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowPlayerBoosterOpen"))bTapShowPlayerBoosterOpen = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowPlayerBoosterMax"))bTapShowPlayerBoosterMax = atoi(line.c_str());

			if (INI_Value_Check(line, "TapShowBooster"))bTapShowBooster = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterUR"))bTapShowBoosterUR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterR"))bTapShowBoosterR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterUC"))bTapShowBoosterUC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterC"))bTapShowBoosterC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterOrder"))iTapShowBoosterOrder = atoi(line.c_str());

			if (INI_Value_Check(line, "TapShowCards"))bTapShowCards = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowCardsUR"))bTapShowCardsUR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowCardsR"))bTapShowCardsR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowCardsUC"))bTapShowCardsUC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowCardsC"))bTapShowCardsC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowCardsOrder"))iTapShowCardsOrder = atoi(line.c_str());

			if (INI_Value_Check(line, "TapShowBoosterPerPlayer"))bTapShowBoosterPerPlayer = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterPerPlayerUR"))bTapShowBoosterPerPlayerUR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterPerPlayerR"))bTapShowBoosterPerPlayerR = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterPerPlayerUC"))bTapShowBoosterPerPlayerUC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterPerPlayerC"))bTapShowBoosterPerPlayerC = atoi(line.c_str());
			if (INI_Value_Check(line, "TapShowBoosterPerPlayerOrder"))iTapShowBoosterPerPlayerOrder = atoi(line.c_str());
				

			if (INI_Value_Check(line, "AllowOpening"))bAllowOpening = atoi(line.c_str());
			if (INI_Value_Check(line, "AllowRefroging"))bAllowRefroging = atoi(line.c_str());
			
			if (INI_Value_Check(line, "NoDouble"))bNoDouble = atoi(line.c_str());
			if (INI_Value_Check(line, "NoAffinities"))bNoAffinities = atoi(line.c_str());
			if (INI_Value_Check(line, "NoPromos"))bNoPromos = atoi(line.c_str());
			
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
				iCountSemi = 0;
				for (char character : line) 
					if (character == ';') 
						iCountSemi++;

				vPlayer[vPlayer.size() - 1]->vBoosters.push_back(
					new Tome_Booster(entry(line, 0).c_str()));
				vPlayer[vPlayer.size() - 1]->vBoosters[vPlayer[vPlayer.size() - 1]->vBoosters.size() - 1]->iLfdnr = atoi(entry(line,1).c_str());

				for (unsigned int i = 0; i < iCountSemi - 1; i++)
					if(atoi(entry(line, 2 + i).c_str()) != 0)
						vPlayer[vPlayer.size() - 1]->vBoosters[vPlayer[vPlayer.size() - 1]->vBoosters.size() - 1]->vCards.push_back(
							Bro->J_GetSMJCard(atoi(entry(line, 2 + i).c_str())));
			}
				
			ifFile.clear();
		}
		ifFile.close();
	}
	else
	{
		MISEA("No Game");
		return false;
	}

	if (iVersion == 0)
	{
		Init();
		MISEA("No Version in File");
		return false;
	}

	MISE;
	return true;
}


void Tome_Game::Init()
{
	MISS;

	iVersion = 1;
	bHasGame = false;

	sGameID = "";
	sAdminID = "";

	bool bShowGlobalBoosterProgress = true;

	bTapShowPlayer = true;
	bTapShowPlayerBoosterOpen = false;
	bTapShowPlayerBoosterMax = false;

	bTapShowBooster = false;
	bTapShowBoosterUR = false;
	bTapShowBoosterR = false;
	bTapShowBoosterUC = false;
	bTapShowBoosterC = false;
	iTapShowBoosterOrder = 0;

	bTapShowCards = false;
	bTapShowCardsUR = false;
	bTapShowCardsR = false;
	bTapShowCardsUC = false;
	bTapShowCardsC = false;
	iTapShowCardsOrder = 0;

	bTapShowBoosterPerPlayer = false;
	bTapShowBoosterPerPlayerUR = false;
	bTapShowBoosterPerPlayerR = false;
	bTapShowBoosterPerPlayerUC = false;
	bTapShowBoosterPerPlayerC = false;
	iTapShowBoosterPerPlayerOrder = 0;

	bAllowOpening = false;
	bAllowRefroging = false;

	bNoDouble = false;
	bNoAffinities = false;
	bNoPromos = false;


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
		ofFile << "V=" << iVersion<< "\n";

		ofFile << "GameID="<<sGameID << "\n";
		ofFile << "AdminID="<<sAdminID << "\n";

		ofFile << "ShowGlobalBoosterProgress="<<bShowGlobalBoosterProgress << "\n";

		ofFile << "TapShowPlayer="<<bTapShowPlayer << "\n";
		ofFile << "TapShowPlayerBoosterOpen="<<bTapShowPlayerBoosterOpen << "\n";
		ofFile << "TapShowPlayerBoosterMax="<<bTapShowPlayerBoosterMax << "\n";

		ofFile << "TapShowBooster="<<bTapShowBooster << "\n";
		ofFile << "TapShowBoosterUR="<<bTapShowBoosterUR << "\n";
		ofFile << "TapShowBoosterR="<<bTapShowBoosterR << "\n";
		ofFile << "TapShowBoosterUC="<<bTapShowBoosterUC << "\n";
		ofFile << "TapShowBoosterC="<<bTapShowBoosterC << "\n";
		ofFile << "TapShowBoosterOrder="<<iTapShowBoosterOrder << "\n";

		ofFile << "TapShowCards="<<bTapShowCards << "\n";
		ofFile << "TapShowCardsUR="<<bTapShowCardsUR << "\n";
		ofFile << "TapShowCardsR="<<bTapShowCardsR << "\n";
		ofFile << "TapShowCardsUC="<<bTapShowCardsUC << "\n";
		ofFile << "TapShowCardsC="<<bTapShowCardsC << "\n";
		ofFile << "TapShowCardsOrder="<<iTapShowCardsOrder << "\n";

		ofFile << "TapShowBoosterPerPlayer="<<bTapShowBoosterPerPlayer << "\n";
		ofFile << "TapShowBoosterPerPlayerUR="<<bTapShowBoosterPerPlayerUR << "\n";
		ofFile << "TapShowBoosterPerPlayerR="<<bTapShowBoosterPerPlayerR << "\n";
		ofFile << "TapShowBoosterPerPlayerUC="<<bTapShowBoosterPerPlayerUC << "\n";
		ofFile << "TapShowBoosterPerPlayerC="<<bTapShowBoosterPerPlayerC << "\n";
		ofFile << "TapShowBoosterPerPlayerOrder=" << iTapShowBoosterPerPlayerOrder << "\n";

		ofFile << "AllowOpening="<<bAllowOpening << "\n";
		ofFile << "AllowRefroging="<<bAllowRefroging << "\n";

		ofFile << "NoDouble="<<bNoDouble << "\n";
		ofFile << "NoAffinities="<<bNoAffinities << "\n";
		ofFile << "NoPromos="<<bNoPromos << "\n";
		
		for (unsigned int i = 0; i < vPlayer.size(); i++)
		{
			ofFile << "P=" << vPlayer[i]->sPlayerID
				<< ";" << vPlayer[i]->sPlayerName << ";";
			for (unsigned int j = 0; j < NumBoostersTypes; j++)
				ofFile << vPlayer[i]->iMaxBoosters[j] << ";";
			ofFile << "\n";

			for (unsigned j = 0; j < vPlayer[i]->vBoosters.size(); j++)
			{
				//MISD(std::to_string(vPlayer[i]->vBoosters[j]->iLfdnr));
				ofFile << "PB=" << vPlayer[i]->vBoosters[j]->sType << ";"
					<< vPlayer[i]->vBoosters[j]->iLfdnr << ";";
				for (unsigned k = 0; k < vPlayer[i]->vBoosters[j]->vCards.size(); k++)
					if(vPlayer[i]->vBoosters[j]->vCards[k]->cardId != 0)
						ofFile << vPlayer[i]->vBoosters[j]->vCards[k]->cardId << ";";
				ofFile << "\n";
			}			
		}

		ofFile.close();
	}
	
	MISE;
	return true;
}

bool Tome_Game::bCheckPlayer(std::string sPlayer)
{
	MISS;
	for (unsigned int i = 0; i < vPlayer.size(); i++)
		if (sPlayer == vPlayer[i]->sPlayerID)
		{
			MISEA("true");
			return true;
		}
	MISEA("false");
	return false;
}

void Tome_Game::AddPlayer()
{
	MISS;

	std::string sPlayerID;
	bool bFound;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(100000, 999999 - 1);

	do
	{
		bFound = false;
		sPlayerID = std::to_string(distr(gen));
		for (unsigned int i = 0; i < vPlayer.size(); i++)		
			if (sPlayerID == vPlayer[i]->sPlayerID)bFound = true;		
	} while (bFound);

	vPlayer.push_back(new Tome_Player(sPlayerID, "New Player"));

	MISE;
}

unsigned int Tome_Game::AllBoosters()
{
	MISS;
	unsigned int iReturn = 0;
	for (unsigned int i = 0; i < vPlayer.size(); i++)
	{
		//MISD(std::to_string(vPlayer[i]->vBoosters.size()))
		iReturn += vPlayer[i]->vBoosters.size();
	}
	MISE;
	return iReturn;
}

unsigned int Tome_Game::AllBoostersMax()
{
	MISS;
	unsigned int iReturn = 0;
	for (unsigned int i = 0; i < vPlayer.size(); i++)
	{
		//MISD(std::to_string(vPlayer[i]->vBoosters.size()))
		iReturn += vPlayer[i]->iMaxBoostersSum();
	}
	MISE;
	return iReturn;
}