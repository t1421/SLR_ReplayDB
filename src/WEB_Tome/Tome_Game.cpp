#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"
#include "..\..\incl\Utility.h"

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

	unsigned int iPlayerCound = 0;

	Init();

	if (ifFile.good())
	{
		MISD("good");
		bHasGame = true;

		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			if (INI_Value_Check(line, "GameID"))sGameID = line.c_str();
			if (INI_Value_Check(line, "AdminID"))sAdminID = line.c_str();
			if (INI_Value_Check(line, "ShowBoosters"))bShowBoosters = atoi(line.c_str());
			if (INI_Value_Check(line, "ShowBoostersOfPlayer"))bShowBoostersOfPlayer = atoi(line.c_str());
			if (INI_Value_Check(line, "ShowBoostersOpenStatus"))bShowBoostersOpenStatus = atoi(line.c_str());

			if (INI_Value_Check(line, "Players"))
			{
				iPlayerCound = atoi(line.c_str());
				ifFile.clear();
				break;
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