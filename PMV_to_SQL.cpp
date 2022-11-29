//#define DF_Debug

#include "Broker.h"

#include "SQL_MIS_New.h"
#include "PMV_to_SQL.h" 
#include "Replay.h" 

broker *(PMV_to_SQL::Bro) = NULL;

PMV_to_SQL::PMV_to_SQL()
{
	MISS;
	sEvent = "";
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
	MISE;
	return true;
}

bool PMV_to_SQL::Upload()
{
	MISS;

	std::string HeadID = "";

	HeadID = DublettenCheck();
	//MISD("X" + HeadID + "X");
	if (HeadID != "0")
	{
		MISD("Dublette: " + HeadID);
		if (UploadPMVPlayerDeck(HeadID))
		{
			MISD("NEW Deck Old Head");
		}
		MISEA("V1")
		return false;
	}





	if(NewMasterData())
		MISD("New Master Stuff");

	HeadID = UploadHead();

	if (HeadID == "0")
	{
		MISEA("ERROR while Uploading Head");
		return false;
	}

	if (!PMVtoSQL(HeadID))
	{
		MISEA("ERROR while Uploading PMV File");
		return false;
	}
	

	if (!UploadPlayers(HeadID))
	{
		MISEA("ERROR while Uploading Players");
		return false;
	}

	if (!UploadActions(HeadID))
	{
		MISEA("ERROR while Uploading Actions");
		return false;
	}

	if (!UploadPMVPlayerDeck(HeadID))
	{
		MISEA("ERROR while UploadPMVPlayerDeck");
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
		MISD("New playmode:" + std::to_string(RR->PlayModeID));
		NN->ssSQL << "INSERT INTO playmode (ID) VALUES(" << int(RR->PlayModeID) << ")";
		NN->send();
		bReturn = true;
	}

	NN->ssSQL << "SELECT ID FROM difficulty WHERE ID = " << int(RR->DifficultyID) ;
	if (NN->send() <= 0)
	{
		MISD("New difficulty:" + std::to_string(RR->DifficultyID));
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


std::string PMV_to_SQL::UploadHead()
{
	MISS;

	NN->ssSQL << "INSERT INTO game (difficultyID, ";
	NN->ssSQL << "                  FileVersion, ";
	NN->ssSQL << "                  GameVersion, ";
	NN->ssSQL << "                  Playtime, ";
	NN->ssSQL << "                  Seed, ";
	NN->ssSQL << "                  mapID, ";
	NN->ssSQL << "                  playmodeID, ";
	//NN->ssSQL << "                  PMVPlayerID, ";
	NN->ssSQL << "                  MinLeaveGame, ";
	NN->ssSQL << "                  WinningTeam, ";
	NN->ssSQL << "                  Event, ";
	NN->ssSQL << "                  FileName) ";
	NN->ssSQL << "VALUES(" << int(RR->DifficultyID) << ", ";
	NN->ssSQL << RR->FileVersion << ", ";
	NN->ssSQL << RR->GameVersion << ", ";
	NN->ssSQL << RR->Playtime << ", ";
	NN->ssSQL << RR->Seed << ", ";
	NN->ssSQL << RR->MapID << ", ";
	NN->ssSQL << RR->PlayModeID << ", ";
	//NN->ssSQL << RR->PMVPlayerID << ", ";
	NN->ssSQL << RR->MinLeaveGame << ", ";
	NN->ssSQL << "'" << RR->WinningTeam << "', ";
	NN->ssSQL << "'" << sEvent << "', ";
	NN->ssSQL << "'" << RR->FileName << "')";
	NN->send();	
	
	/// UNKNOWS

	MISE;
	return NN->get_LAST_INSERT_ID();
}

bool PMV_to_SQL::UploadPlayers(std::string iNewHeadID)
{
	MISS;

	unsigned int findTeam;
	
	for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
	{
		if (RR->PlayerMatrix[i]->Type != 1)continue; //KI �berspringen

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

std::string PMV_to_SQL::DublettenCheck()
{
	MISS;

	unsigned long long iPlayerIDSUM = 0;
	for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
		if (RR->PlayerMatrix[i]->Type == 1)iPlayerIDSUM += RR->PlayerMatrix[i]->PlayerID;
		
	NN->ssSQL << " SELECT ID ";
	NN->ssSQL << "   FROM game ";
	NN->ssSQL << "   LEFT JOIN gameplayers ";
	NN->ssSQL << "     ON gameplayers.gameID = game.ID ";
	NN->ssSQL << "  WHERE difficultyID = " << int(RR->DifficultyID);	
	NN->ssSQL << "    AND FileVersion =  " << RR->FileVersion;
	NN->ssSQL << "    AND GameVersion =  " << RR->GameVersion;
	NN->ssSQL << "    AND Seed =         " << RR->Seed;
	NN->ssSQL << "    AND mapID =        " << RR->MapID;
	NN->ssSQL << "    AND playmodeID =   " << RR->PlayModeID;
	NN->ssSQL << "    AND MinLeaveGame = " << RR->MinLeaveGame;	
	NN->ssSQL << "  GROUP BY ID " ;
	NN->ssSQL << " HAVING SUM(gameplayers.playerID) = " << iPlayerIDSUM;

	if (NN->send() > 0)
	{
		NN->res->next();
		
		MISEA("Already Here");
		return NN->res->getString(1);
	}

	MISE;
	return "0";
}


bool PMV_to_SQL::UploadActions(std::string iNewHeadID)
{
	MISS;

	for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
	{
		NN->ssSQL << "INSERT INTO action (";
		NN->ssSQL << "  gameID , ";
		NN->ssSQL << "  Time  , ";
		NN->ssSQL << "  ActionTypeID , ";
		NN->ssSQL << "  CardID , ";
		NN->ssSQL << "  Charges , ";
		NN->ssSQL << "  AdditionalInfo , ";
		NN->ssSQL << "  Upgrade , ";
		NN->ssSQL << "  playerID) ";
		NN->ssSQL << "VALUES(";
		NN->ssSQL << iNewHeadID << " , ";
		NN->ssSQL << RR->ActionMatrix[i]->Time << " , ";
		NN->ssSQL << RR->ActionMatrix[i]->Type << " , ";
		NN->ssSQL << RR->ActionMatrix[i]->Card << " , ";
		NN->ssSQL << int(RR->ActionMatrix[i]->Charges) << " , ";
		NN->ssSQL << "'"<<RR->ActionMatrix[i]->AdditionalInfo << "' , ";
		NN->ssSQL << RR->ActionMatrix[i]->Upgrade << " , ";
		NN->ssSQL << RR->ActionMatrix[i]->PlayerID <<" ) ";
		NN->send();
	}


	MISE;
	return true;
}

bool PMV_to_SQL::UploadPMVPlayerDeck(std::string iNewHeadID)
{
	MISS;

	NN->ssSQL << "SELECT gameID ";
	NN->ssSQL << "  FROM pmvdeck ";
	NN->ssSQL << " WHERE gameID = " << iNewHeadID;
	NN->ssSQL << "   AND playerID = " << RR->PMVPlayerID;

	if (NN->send() > 0)
	{
		MISEA("Deck already in DB");
		return false;
	}

	//Bei allen Spielern steht das gleiche Deck drinnen und zwar von dem der das PMV aufnimt
	for (unsigned int i = 0; i < RR->PlayerMatrix[0]->Deck.size(); i++)
	{
		NN->ssSQL << "INSERT INTO pmvdeck (";
		NN->ssSQL << "  gameID , ";
		NN->ssSQL << "  CardID , ";
		NN->ssSQL << "  Charges , ";
		NN->ssSQL << "  Upgrade , ";
		NN->ssSQL << "  playerID) ";
		NN->ssSQL << "VALUES(";
		NN->ssSQL << iNewHeadID << " , ";		
		NN->ssSQL << RR->PlayerMatrix[0]->Deck[i]->CardID << " , ";
		NN->ssSQL << int(RR->PlayerMatrix[0]->Deck[i]->Charges) << " , ";
		NN->ssSQL << RR->PlayerMatrix[0]->Deck[i]->Upgrade << " , ";
		NN->ssSQL << RR->PMVPlayerID << " ) ";
		NN->send();
	}


	MISE;
	return true;
}


void PMV_to_SQL::UseThisSQL(SQL_MIS_New * inSQL)
{
	MISS;
	NN = inSQL;
	MISE;
}

bool PMV_to_SQL::Download(std::string sGameID)
{
	MISS;

	Player* Player_TEMP;
	Action * Action_TEMP;

	NN->ssSQL << "SELECT difficultyID, ";
	NN->ssSQL << "       FileVersion, ";
	NN->ssSQL << "       GameVersion, ";
	NN->ssSQL << "       Playtime, ";
	NN->ssSQL << "       Seed, ";
	NN->ssSQL << "       mapID , ";
	NN->ssSQL << "       playmodeID , ";
	NN->ssSQL << "       MinLeaveGame, ";
	NN->ssSQL << "       FileName, ";
	NN->ssSQL << "       WinningTeam, ";
	NN->ssSQL << "       map.Name, ";
	NN->ssSQL << "       game.ID ";
	NN->ssSQL << " FROM game ";
	NN->ssSQL << " left join map on map.ID = game.mapID";
	NN->ssSQL << " WHERE game.ID = " << sGameID;
	if (NN->send() <= 0)
	{		
		MISEA("GAME ID invalide: " + sGameID);
		return false;
	}
	Bro->N->res->next();

	RR->DifficultyID = NN->res->getInt(1);
	RR->FileVersion = NN->res->getInt(2);
	RR->GameVersion = NN->res->getInt(3);
	RR->Playtime = NN->res->getInt(4);
	RR->Seed = NN->res->getInt(5);
	RR->MapID = NN->res->getInt(6);
	RR->PlayModeID = NN->res->getInt(7);
	RR->MinLeaveGame = NN->res->getInt(8);
	RR->FileName = NN->res->getString(9);
	RR->WinningTeam = NN->res->getString(10);
	RR->MapName = NN->res->getString(11);
	RR->sSQLGameID = NN->res->getString(12);




	NN->ssSQL << "SELECT playerID, ";
	//NN->ssSQL << "       Team, ";
	NN->ssSQL << "       PosInTeam, ";
	NN->ssSQL << "       player.Name ";	
	NN->ssSQL << " FROM gameplayers ";
	NN->ssSQL << " left join player on player.ID = gameplayers.playerID";
	NN->ssSQL << " WHERE gameplayers.gameID = " << sGameID;
	if (NN->send() <= 0)
	{
		MISEA("No Players: " + sGameID);
		return false;
	}

	while (Bro->N->res->next())
	{
		Player_TEMP = new Player;
		
		Player_TEMP->PlayerID = NN->res->getInt(1);
		//Player_TEMP->GroupID = readUnsignedChar();
		Player_TEMP->IDinGroup = NN->res->getInt(2);
		Player_TEMP->Name = NN->res->getString(3);		
		RR->PlayerMatrix.push_back(Player_TEMP);
	}


	NN->ssSQL << " SELECT	Time, ";
	NN->ssSQL << "			ActionTypeID , ";
	NN->ssSQL << "			CardID , ";
	NN->ssSQL << "			Charges , ";
	NN->ssSQL << "			AdditionalInfo , ";
	NN->ssSQL << "			Upgrade , ";
	NN->ssSQL << "			playerID ";
	NN->ssSQL << " FROM action ";
	NN->ssSQL << " WHERE action.gameID = " << sGameID;
	if (NN->send() <= 0)
	{
		MISEA("No action: " + sGameID);
		return false;
	}
	while (Bro->N->res->next())
	{
		Action_TEMP = new Action;
		Action_TEMP->Time = NN->res->getInt(1);
		Action_TEMP->Type = NN->res->getInt(2);
		Action_TEMP->Card = NN->res->getInt(3);
		Action_TEMP->Charges = NN->res->getInt(4);
		Action_TEMP->AdditionalInfo = NN->res->getString(5);
		Action_TEMP->Upgrade = NN->res->getInt(6);
		Action_TEMP->PlayerID = NN->res->getInt(7);
		RR->ActionMatrix.push_back(Action_TEMP);
	}

	MISE;
	return true;
}

bool PMV_to_SQL::PMVtoSQL(std::string iNewHeadID)
{
	MISS;

	Bro->N->ssSQL << " UPDATE game SET PMV = ?";
	Bro->N->ssSQL << " WHERE ID = " << iNewHeadID;
	Bro->N->SendBLOB(RR->ssPMVFile.str());


	MISE;
	return true;
}