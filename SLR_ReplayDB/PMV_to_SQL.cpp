//#define DF_Debug

#include "stdafx.h"

#include "SQL_MIS_New.h"
#include "PMV_to_SQL.h" 
#include "Replay.h" 

broker *(PMV_to_SQL::Bro) = NULL;

PMV_to_SQL::PMV_to_SQL()
{
	MISS;
	NN = new SQL_MIS_New("PMV_to_SQL");
	MISE;
}

PMV_to_SQL::~PMV_to_SQL()
{
	MISS;
	//delete NN;
	MISE;
}

bool PMV_to_SQL::UseThisPMV(Replay * inReplay)
{
	MISS;
	
	RR = inReplay;
	if (!RR->OK) 
	{
		MISEA("Replay not OK");
		return false;
	}

	if(!DublettenCheck())
	{
		MISEA("Dublette");
		return false;
	}

	if(NewMasterData())
		MISD("New Master Stuff");

	string iNewHeadID = UploadHead();

	if (iNewHeadID == "0") 
	{
		MISEA("ERROR while Uploading Head");
		return false;
	}

	if (!UploadPlayers(iNewHeadID))
	{
		MISEA("ERROR while Uploading Players");
		return false;
	}


	MISE;
	return true;
}


bool PMV_to_SQL::NewMasterData()
{
	MISS;
	bool bReturn = false;

	NN->ssSQL << "SELECT ID FROM playmode WHERE ID = " << int(RR->PlayModeID);
	if (NN->send() <= 0)
	{
		MISD("New playmode:" + to_string(RR->PlayModeID));
		NN->ssSQL << "INSERT INTO playmode (ID) VALUES(" << int(RR->PlayModeID) << ")";
		NN->send();
		bReturn = true;
	}

	NN->ssSQL << "SELECT ID FROM difficulty WHERE ID = " << int(RR->DifficultyID) ;
	if (NN->send() <= 0)
	{
		MISD("New difficulty:" + to_string(RR->DifficultyID));
		NN->ssSQL << "INSERT INTO difficulty (ID) VALUES(" << int(RR->DifficultyID) <<")";
		NN->send();
		bReturn = true;
	}

	NN->ssSQL << "SELECT ID FROM map WHERE ID = " << int(RR->MapID);
	if (NN->send() <= 0)
	{
		MISD("New Map:" + RR->MapName);
		NN->ssSQL << "INSERT INTO map (ID,Name) ";
		NN->ssSQL << "VALUES(" << int(RR->MapID) << ", '";
		NN->ssSQL << NN->clearString(RR->MapName) << "')";
		NN->send();
		bReturn = true;
	}

	for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
	{
		NN->ssSQL << "SELECT ID FROM player WHERE ID = " << int(RR->PlayerMatrix[i]->PlayerID);
		if (NN->send() <= 0)
		{
			MISD("New Player:" + RR->PlayerMatrix[i]->Name);
			NN->ssSQL << "INSERT INTO player (ID,Name) ";
			NN->ssSQL << "VALUES(" << int(RR->PlayerMatrix[i]->PlayerID) << ", '";
			NN->ssSQL << RR->PlayerMatrix[i]->Name << "')";
			NN->send();
			bReturn = true;
		}
	}

	MISE;
	return bReturn;
}


string PMV_to_SQL::UploadHead()
{
	MISS;

	NN->ssSQL << "INSERT INTO game (difficultyID, ";
	NN->ssSQL << "                  FileVersion, ";
	NN->ssSQL << "                  GameVersion, ";
	NN->ssSQL << "                  Playtime, ";
	NN->ssSQL << "                  Seed, ";
	NN->ssSQL << "                  mapID, ";
	NN->ssSQL << "                  playmodeID, ";
	NN->ssSQL << "                  HostPlayerID, ";
	NN->ssSQL << "                  MinLeaveGame, ";
	NN->ssSQL << "                  FileName) ";
	NN->ssSQL << "VALUES(" << int(RR->DifficultyID) << ", ";
	NN->ssSQL << RR->FileVersion << ", ";
	NN->ssSQL << RR->GameVersion << ", ";
	NN->ssSQL << RR->Playtime << ", ";
	NN->ssSQL << RR->Seed << ", ";
	NN->ssSQL << RR->MapID << ", ";
	NN->ssSQL << RR->PlayModeID << ", ";
	NN->ssSQL << RR->HostID << ", ";
	NN->ssSQL << RR->MinLeaveGame << ", ";
	NN->ssSQL << "'" << RR->FileName << "')";
	NN->send();	
	
	/// UNKNOWS

	MISE;
	return NN->get_LAST_INSERT_ID();
}

bool PMV_to_SQL::UploadPlayers(string iNewHeadID)
{
	MISS;

	int findTeam;
	
	for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
	{
		if (RR->PlayerMatrix[i]->Type != 1)continue; //KI überspringen

		for (findTeam = 0; findTeam < RR->TeamMatrix.size() && RR->TeamMatrix[findTeam]->GroupID != RR->PlayerMatrix[i]->GroupID; findTeam++);
		
		NN->ssSQL << "INSERT INTO gameplayers (";
		NN->ssSQL << "  gameID , ";
		NN->ssSQL << "  playerID  , ";		
		NN->ssSQL << "  PosInTeam , ";
		NN->ssSQL << "  Team) ";
		NN->ssSQL << "VALUES(";
		NN->ssSQL << iNewHeadID << " , ";
		NN->ssSQL << RR->PlayerMatrix[i]->PlayerID << " , ";		
		NN->ssSQL << int(RR->PlayerMatrix[i]->IDinGroup) << " , '";
		NN->ssSQL << RR->TeamMatrix[findTeam]->Name << "' ) ";		
		NN->send();
	}

	
	MISE;
	return true;
}


bool PMV_to_SQL::DublettenCheck()
{
	MISS;
	
	NN->ssSQL << "SELECT ID ";
	NN->ssSQL << "FROM game ";
	NN->ssSQL << "WHERE difficultyID = " << int(RR->DifficultyID);
	NN->ssSQL << "  AND FileVersion =  " << RR->FileVersion;
	NN->ssSQL << "  AND GameVersion =  " << RR->GameVersion;
	NN->ssSQL << "  AND Seed =         " << RR->Seed;
	NN->ssSQL << "  AND mapID =        " << RR->MapID;
	NN->ssSQL << "  AND playmodeID =   " << RR->PlayModeID;
	NN->ssSQL << "  AND HostPlayerID = " << RR->HostID;
	NN->ssSQL << "  AND playmodeID   = " << RR->PlayModeID;
	NN->ssSQL << "  AND MinLeaveGame = " << RR->MinLeaveGame;
	if (NN->send() > 0)return false;
	//PLAYER!!! Sicher ist sicher ?
	
	

	MISE;
	return true;
}