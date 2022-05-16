//#define DF_Debug

#include "stdafx.h"

#include "SQL_MIS_New.h"
#include "Replay.h" 

broker *(Replay::Bro) = NULL;

Replay::Replay()
{
	MISS;
	OK = false;
	MISE;
}

Replay::~Replay()
{
	MISS;
	
	MISE;
}

bool Replay::LoadPMV(string sFile)
{
	MISS;

	if (!Open(PMV_path + sFile))
	{
		MISERROR("<-- error opening PMV");
		return false;
	}
	FileName = sFile;

	if (ReadHeader() == false)
	{
		MISERROR("<-- ReadHeader faild");
		return false;
	}

	if (ReadActions() == false)
	{
		MISERROR("<-- ReadActions faild");
		return false;
	}

	if (ConnectActionToPlayer() == false)
	{
		MISERROR("<-- ConnectActionToPlayer faild");
		return false;
	}

	if (AddFirstOrb() == false)
	{
		MISERROR("<-- AddFirstOrb faild");
		return false;
	}

	if (SetMinLeaveTime() == false)
	{
		MISERROR("<-- SetMinLeaveTime faild");
		return false;
	}

	OK = true;


	MISE;
	return true;
}

bool Replay::ReadHeader()
{
	MISS;

	Allied* Allied_TEMP;
	Team* Team_TEMP;
	Player* Player_TEMP;
	Card* Card_TEMP;

	FileVersion = readUnsignedLong();
	if (FileVersion > 200)GameVersion = readUnsignedLong();
	Playtime = readUnsignedLong();
	if (FileVersion > 213)Seed = readUnsignedLong(); // Seed - wichtig für RPVE
		
	MapName = get_file_name(readString());
	if(MapName=="")
	{
		MISERROR("<-- No Map Name? ");
		return false;
	}

	MISD("Vars");
	ActionBlock = readUnsignedLong() + PMVPosition;
	Unknow3 = readUnsignedChar();
	Unknow4 = readUnsignedChar();
	MapID = readUnsignedLong(); // PVR = 101 / Titans = 29 /// MAPID
	DifficultyID = readUnsignedChar(); // Std=1,Adv=2,Exp=3,PVR1=5 ...
	PlayModeID = readUnsignedShort(); // PvE = 1 / PvP = 2
	HostID = readUsignedLongLong();
	GroupCount = readUnsignedChar();

	MISD("Matrix");
	MatrixCount = readUnsignedShort();	
	for (int i = 0; i < MatrixCount; i++)
	{		
		Allied_TEMP = new Allied;
		Allied_TEMP->i = readUnsignedChar();
		Allied_TEMP->j = readUnsignedChar();
		Allied_TEMP->v = readUnsignedChar();
		AlliedMatrix.push_back(Allied_TEMP);
	}

	MISD("Team");
	TeamCount = readUnsignedShort();
	for (int i = 0; i < TeamCount; i++)
	{
		Team_TEMP = new Team;
		Team_TEMP->Name = readString();
		Team_TEMP->GroupID = readUnsignedLong();
		Team_TEMP->Value = readUnsignedShort();
		TeamMatrix.push_back(Team_TEMP);
	}
	
	MISD("Player");
	while (PMVPosition < ActionBlock)
	{
		Player_TEMP = new Player;
		Player_TEMP->Name = readWString();
		Player_TEMP->PlayerID = readUsignedLongLong();
		Player_TEMP->GroupID = readUnsignedChar();
		Player_TEMP->IDinGroup = readUnsignedChar();
		Player_TEMP->Type = readUnsignedChar();
		Player_TEMP->Cards = readUnsignedChar();
		Player_TEMP->CardsTotal = readUnsignedChar();
		PlayerMatrix.push_back(Player_TEMP);				

		for (int i = 0; i < PlayerMatrix[PlayerMatrix.size() - 1]->Cards; i++)
		{
			Card_TEMP = new Card;
			Card_TEMP->DeckCardID = readUnsignedShort();
			Card_TEMP->CardID = Card_TEMP->DeckCardID % 0x4240;
			Card_TEMP->Upgrade = readUnsignedShort() / 15;
			Card_TEMP->Charges = readUnsignedChar();
			PlayerMatrix[PlayerMatrix.size() - 1]->Deck.push_back(Card_TEMP);

		}		
	}

	
	//MISD("Playtime:   " + to_string(Playtime));	
	//MISD("FileVersion:" + to_string(FileVersion));
	//MISD("GameVersion:" + to_string(GameVersion));
	//MISD("Playtime:   " + to_string(Playtime));
	MISD("Unknow3:    " + to_string(Unknow3));
	MISD("Unknow4:    " + to_string(Unknow4));
	/*
	MISD("MapName:    " + MapName);
	MISD("Seed:       " + to_string(Seed));
	MISD("MapID:      " + to_string(MapID));
	MISD("difficulty: " + to_string(DifficultyKEY));
	MISD("PlayMode:   " + to_string(PlayModeKEY));
	*/
	
	/*
	MISD("ActionBlock:" + to_string(ActionBlock));
	
	MISD("HostID:     " + to_string(HostID));
	MISD("GroupCount: " + to_string(GroupCount));

	MISD("MatrixCount:" + to_string(MatrixCount));
	for (unsigned int i = 0; i < MatrixCount; i++)
	{
		MISD(to_string(i) + "#" 
			+ to_string(AlliedMatrix[i]->i) + "#" 
			+ to_string(AlliedMatrix[i]->j) + "#" 
			+ to_string(AlliedMatrix[i]->v));
	}
		*/
	MISD("###");
	MISD("TeamCount:" + to_string(TeamCount));
	for (unsigned int i = 0; i < TeamCount; i++)
	{
		MISD(to_string(i) + "#" 
			+ TeamMatrix[i]->Name + "#" 
			+ to_string(TeamMatrix[i]->GroupID) + "#" 
			+ to_string(TeamMatrix[i]->Value));
	}
	

	
	MISD("###");
	for (unsigned int i = 0; i < PlayerMatrix.size() ; i++)
	{
		MISD(to_string(i) + "#" 
			+ PlayerMatrix[i]->Name + "#"
			+ to_string(PlayerMatrix[i]->PlayerID) + "#"
			+ to_string(PlayerMatrix[i]->GroupID) + "#"
			+ to_string(PlayerMatrix[i]->IDinGroup) + "#"
			+ to_string(PlayerMatrix[i]->Type) + "#"
			+ to_string(PlayerMatrix[i]->Cards) + "#"
			+ to_string(PlayerMatrix[i]->CardsTotal));
		/*
		for (unsigned int j = 0; j < PlayerMatrix[i]->Deck.size(); j++)
		{
			MISD(to_string(i) + "#"
				+ to_string(j) + "#"
				+ to_string(PlayerMatrix[i]->Deck[j]->DeckCardID) + "#"
				+ to_string(PlayerMatrix[i]->Deck[j]->CardID) + "#"
				+ to_string(PlayerMatrix[i]->Deck[j]->Upgrade) + "#"
				+ to_string(PlayerMatrix[i]->Deck[j]->Charges));
		}
		*/
	}
	
	/*
	MISD("ActionBlock:" + to_string(ActionBlock));
	MISD("NOW        :" + to_string(PMVPosition));
	*/
	if (ActionBlock != PMVPosition)
	{
		MISERROR("<-- ActionBlockOffsetError soll:" + to_string(ActionBlock) + " ist:" + to_string(PMVPosition));
		return false;
	}
	
	MISE;
	return true;
}

bool Replay::ReadActions()
{
	MISS;
	MISD("ActionBlock:" + to_string(ActionBlock));
	MISD("NOW        :" + to_string(PMVPosition));
	MISD("length     :" + to_string(length));

	Action * Action_TEMP;
	unsigned long SollPos = 0;

	if (ActionBlock== 0)
	{
		MISERROR("<-- no Acion Blokc?");
		return false;
	}

	while (PMVPosition < length)
	{
		Action_TEMP = new Action;
		Action_TEMP->Time = readUnsignedLong();
		Action_TEMP->Size = readUnsignedLong();
		SollPos = PMVPosition + Action_TEMP->Size;

		Action_TEMP->Type = readUnsignedLong();
		
		//MISD(to_string(Action_TEMP->Time) + " +++");

		switch(Action_TEMP->Type)
		{
		case 4001: //REALLY_UNKNOWN_A1						
			//Action_TEMP->Player = readUnsignedLong();
			MISERROR(FileName);
			MISERROR(sTime(Action_TEMP->Time) + "#" + 
				to_string(Action_TEMP->Type) + "#" + 
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) +
				" ???");
			break;
		case 4002: //leave game		
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4004: //12 Player Map Special	(Sync von Maps 1 bis 3 ? )
			/*
			MISERROR(FileName);
			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) +
				" ???");
			*/
			break;
		case 4006: //GOLD	
			break;
		case 4007: //Objective OK 
			break;
		case 4008: //PVE_UNKNOWN_A8	
			MISERROR(FileName);
			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) +
				" ???");
			break;
		case 4009: //summon unit
			Action_TEMP->CardFull = readUnsignedLong();
			Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
			Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
			Action_TEMP->Player = readUnsignedLong();
			/*Action_TEMP->Unknow8 =*/ readUnsignedChar();
			/*Action_TEMP->Cardy =*/ readUnsignedShort();
			/*Action_TEMP->Cardz =*/ readUnsignedShort();
			Action_TEMP->Charges = readUnsignedChar(); // Nur beim erstenmal rufen
			break;
		case 4010: //cast spell
			Action_TEMP->CardFull = readUnsignedLong();
			Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
			Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
			Action_TEMP->Player = readUnsignedLong();
			/*Action_TEMP->Unknow8 =*/ readUnsignedChar();
			/*Action_TEMP->Cardy =*/ readUnsignedShort();
			/*Action_TEMP->Cardz =*/ readUnsignedShort();
			Action_TEMP->Charges = readUnsignedChar(); // Nur beim erstenmal rufen
			

			break;
		case 4011: //cast line spell
			Action_TEMP->CardFull = readUnsignedLong();
			Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
			Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;			
			Action_TEMP->Player = readUnsignedLong();
			/*Action_TEMP->Unknow8 =*/ readUnsignedChar();
			/*Action_TEMP->Cardy =*/ readUnsignedShort();
			/*Action_TEMP->Cardz =*/ readUnsignedShort();
			Action_TEMP->Charges = readUnsignedChar(); // Nur beim erstenmal rufen

			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->CardFull) + " # " +
				to_string(Action_TEMP->Size) + " # " +
				to_string(Action_TEMP->Card) + " # " +
				to_string(Action_TEMP->Upgrade) + " # " +
				to_string(Action_TEMP->Charges));
			break;
		case 4012: //cast building
			Action_TEMP->CardFull = readUnsignedLong();
			Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
			Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
			Action_TEMP->Player = readUnsignedLong();
			/*Action_TEMP->Cardy =*/ readUnsignedShort();
			/*Action_TEMP->Cardz =*/ readUnsignedShort();
			/*Action_TEMP->X =*/ readUnsignedLong();
			/*Action_TEMP->Z =*/ readUnsignedLong();
			/*Action_TEMP->Y =*/ readUnsignedLong();
			/*Action_TEMP->Cardz =*/ readUnsignedShort();
			/*Action_TEMP->CardA =*/ readUnsignedShort();
			Action_TEMP->Charges = readUnsignedChar(); // Nur beim erstenmal rufen	
			/*
			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) + " # " +
				to_string(Action_TEMP->Card) + " # " +
				to_string(Action_TEMP->Upgrade) + " # " +
				to_string(Action_TEMP->Charges) );
				*/
			break;
		case 4013: //move unit
			Action_TEMP->Player = readUnsignedLong();			
			break;
		case 4014: //use unit ability
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4015: //attack			
			Action_TEMP->Player = readUnsignedLong();			
			break;
		case 4019: //stop unit
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4020: //hold unit position
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4027: // PING (Meet / Help / ...)
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4028: //toggle wall gate
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4029: //build wall
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4030: //create mana
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4031: //create orb
			// 1 = Shadow
			// 2 = Green
			// 3 = Frost
			// 4 = Red
			Action_TEMP->Player = readUnsignedLong();
			/*Action_TEMP->Unit =*/ readUnsignedLong();
			Action_TEMP->Color = readUnsignedChar();			
			break;
		case 4033: //Unit move on Wall			
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4034: //Switch Abbility (Stone Tempest)
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4035: //Trigger Reparier
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4036: //???
			//Action_TEMP->Player = readUnsignedLong();
			MISERROR(FileName);
			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) +
				" ???");
			break;
		case 4041: //Killed own Unit
			Action_TEMP->Player = readUnsignedLong();
			break;
		case 4043: // go to Gold but not able to collect
			Action_TEMP->Player = readUnsignedLong();
			break;
		
		default:
			MISERROR(FileName);
			MISERROR(sTime(Action_TEMP->Time) + "#" +
				to_string(Action_TEMP->Type) + "#" +
				to_string(PMVPosition) + " # " +
				to_string(Action_TEMP->Size) +
				" SUPER UNKNOW!!!!");
		}
		PMVPosition = SollPos;		
		
		/*
		MISD(to_string(Action_TEMP->Time) + "#" + 
			sTime(Action_TEMP->Time) + "#" +
			to_string(Action_TEMP->Type) + " # " + 
			"Player:" + to_string(Action_TEMP->Player));
		*/
		
		if (PMVPosition != SollPos)
		{
			MISERROR("wir sind off, soll:" + to_string(SollPos) + " ist:" + to_string(PMVPosition));
			PMVPosition = SollPos;
		}
		ActionMatrix.push_back(Action_TEMP);

	}

	MISD("NOW        :" + to_string(PMVPosition));

	MISE;
}

string Replay::sTime(unsigned long ulTime)
{
	MISS;
	char cOut[6];	
	snprintf(cOut, 6, "%02d:%02d", int(floor(ulTime / 600)), int(ulTime / 10 %60));
	MISE;
	return cOut;
}

bool Replay::ConnectActionToPlayer()
{
	MISS;
	unsigned long minActionPlayer = 4294967295 - 1;

	for (unsigned int i = 0; i < ActionMatrix.size(); i++)if (ActionMatrix[i]->Player != 0 && ActionMatrix[i]->Player < minActionPlayer)minActionPlayer = ActionMatrix[i]->Player;

	MISD("minActionPlayer:" + to_string(minActionPlayer));
	if (minActionPlayer == 4294967295 - 1) 
	{
		MISERROR("<-- cant find min Action Player");
		return false;
	}

	for (unsigned int i = 0; i < PlayerMatrix.size(); i++)PlayerMatrix[i]->ActionPlayer = minActionPlayer + i;	

	MISE;
	return true;
}

bool Replay::AddFirstOrb()
{
	MISS;
	
	unsigned int iPosOfUnit;
	Action * Action_TEMP;

	for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
	{
		for ( iPosOfUnit = 0; iPosOfUnit < ActionMatrix.size(); iPosOfUnit++)
		{
			if (PlayerMatrix[i]->ActionPlayer == ActionMatrix[iPosOfUnit]->Player &&
				(ActionMatrix[iPosOfUnit]->Type == 4012 //Building
					|| ActionMatrix[iPosOfUnit]->Type == 4011 //Spell 2
					|| ActionMatrix[iPosOfUnit]->Type == 4010 //Spell 1
					|| ActionMatrix[iPosOfUnit]->Type == 4009 //Unit
					))break;
		}
		if (iPosOfUnit == ActionMatrix.size())
		{
			MISD("No Unit Played " + PlayerMatrix[i]->Name);
			continue;
		}

		Action_TEMP = new Action;
		Action_TEMP->Time = ActionMatrix[iPosOfUnit]->Time;
		Action_TEMP->Size = 13;
		Action_TEMP->Type = 4031;
		Action_TEMP->Player = ActionMatrix[iPosOfUnit]->Player;
		Action_TEMP->Color = Bro->C_GetActionOrbForCardID(ActionMatrix[iPosOfUnit]->Card);
		//MISD(sTime(Action_TEMP->Time) + "#" + to_string(Action_TEMP->Type) + " Player:" + to_string(Action_TEMP->Player) + " Color:" + to_string(Action_TEMP->Color));
		ActionMatrix.insert(ActionMatrix.begin() + iPosOfUnit, Action_TEMP);				
	}

	MISE;
	return true;
}

bool Replay::SetMinLeaveTime()
{
	MISS;

	for (MinLeaveGame = 0; MinLeaveGame < ActionMatrix.size(); MinLeaveGame++)
		if (ActionMatrix[MinLeaveGame]->Type == 400 )break;
				
	MISE;
	return true;
}

void Replay::ECHO()
{
	//MISS;
	MISERROR(MapName);
	
	MISERROR("Unknow3  :" + to_string(Unknow3));
	MISERROR("Unknow4  :" + to_string(Unknow4));
	MISERROR("SEED     :" + to_string(Seed));
	MISERROR("MapID    :" + to_string(MapID));
	MISERROR("difficu  :" + to_string(DifficultyID));
	MISERROR("PlayMode :" + to_string(PlayModeID));
	//MISE;
}


string Replay::get_file_name(string pfad)
{
	pfad = pfad.substr(pfad.find("\\") + 1, pfad.length() - pfad.find("\\") + 1);
	if (pfad.find("\\") != pfad.npos) pfad = get_file_name(pfad);
	return pfad;
}