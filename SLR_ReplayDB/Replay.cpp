//#define DF_Debug

#include "stdafx.h"

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

	if (!Open(sFile))
	{
		MISERROR("<-- error opening PMV");
		return false;
	}
	FileName = get_file_name(sFile);

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

	if (SetCharges() == false)
	{
		MISERROR("<-- SetCharges faild");
		return false;
	}

	if (FillPlayerIDInAction() == false)
	{
		MISERROR("<-- FillPlayerIDInAction faild");
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

	//MISD("Vars");
	ActionBlock = readUnsignedLong() + PMVPosition;
	Unknow3 = readUnsignedChar();
	Unknow4 = readUnsignedChar();
	MapID = readUnsignedLong(); // PVR = 101 / Titans = 29 /// MAPID
	DifficultyID = readUnsignedChar(); // Std=1,Adv=2,Exp=3,PVR1=5 ...
	PlayModeID = readUnsignedShort(); // PvE = 1 / PvP = 2
	PMVPlayerID = readUnsignedLongLong();
	GroupCount = readUnsignedChar();

	//MISD("Matrix");
	MatrixCount = readUnsignedShort();	
	for (int i = 0; i < MatrixCount; i++)
	{		
		Allied_TEMP = new Allied;
		Allied_TEMP->i = readUnsignedChar();
		Allied_TEMP->j = readUnsignedChar();
		Allied_TEMP->v = readUnsignedChar();
		AlliedMatrix.push_back(Allied_TEMP);
	}

	//MISD("Team");
	TeamCount = readUnsignedShort();
	for (int i = 0; i < TeamCount; i++)
	{
		Team_TEMP = new Team;
		Team_TEMP->Name = readString();
		Team_TEMP->GroupID = readUnsignedLong();
		Team_TEMP->Value = readUnsignedShort();
		TeamMatrix.push_back(Team_TEMP);
	}
	
	//MISD("Player");
	while (PMVPosition < ActionBlock)
	{
		Player_TEMP = new Player;
		Player_TEMP->Name = readWString();
		Player_TEMP->PlayerID = readUnsignedLongLong();
		Player_TEMP->GroupID = readUnsignedChar();
		Player_TEMP->IDinGroup = readUnsignedChar();
		Player_TEMP->Type = readUnsignedChar();
		Player_TEMP->Cards = readUnsignedChar();
		Player_TEMP->CardsTotal = readUnsignedChar();
		PlayerMatrix.push_back(Player_TEMP);				

		for (int i = 0; i < PlayerMatrix[PlayerMatrix.size() - 1]->Cards; i++)
		{
			Card_TEMP = new Card;
			
			Card_TEMP->CardFull = readUnsignedLong();
			Card_TEMP->CardID = Card_TEMP->CardFull % 1000000;
			Card_TEMP->Upgrade = Card_TEMP->CardFull / 1000000;
			//Card_TEMP->DeckCardID = readUnsignedShort();
			//Card_TEMP->CardID = Card_TEMP->DeckCardID % 0x4240;
			//Card_TEMP->Upgrade = readUnsignedShort() / 15;
			Card_TEMP->Charges = readUnsignedChar();
			PlayerMatrix[PlayerMatrix.size() - 1]->Deck.push_back(Card_TEMP);

		}		
	}

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
	
	Action * Action_TEMP;
	unsigned long SollPos = 0;
	unsigned long tempCount;
	unsigned long MainTime;
	unsigned long MainSize;

	if (ActionBlock== 0)
	{
		MISERROR("<-- no Acion Blokc?");
		return false;
	}

	while (PMVPosition < length)
	{
		MainTime = readUnsignedLong();
		MainSize = readUnsignedLong();
		SollPos = PMVPosition + MainSize;

		while (PMVPosition < SollPos)
		{
			Action_TEMP = new Action;
			Action_TEMP->Time = MainTime;
			Action_TEMP->Position = PMVPosition;
			Action_TEMP->Type = readUnsignedLong();

			switch (Action_TEMP->Type)
			{
			case 4001: //REALLY_UNKNOWN_A1						
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); //zero
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				break;
				///###
			case 4002: //leave game		
				Action_TEMP->ActionPlayer = readUnsignedLong();
				break;
				///###
			case 4004: //12 Player Map Special	(Sync von Maps 1 bis 3 ? )		// Anzahl von Gegnern auf der Map?					
				readUnsignedLong(); //Unit
				this->readUnsignedChar(); // ??? number between 0 and 16?				
				break;
				///###
			case 4006: //GOLD	
				Action_TEMP->PlayerID = readUnsignedLongLong(); // wer hat eingesammelt
				readUnsignedLong(); // Unit
				tempCount = readUnsignedLong();
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLongLong(); // wer erhält gold
					readUnsignedLong(); // menge gold
				}
				break;
				///###
			case 4007: //Objective OK 
				readUnsignedLong(); // ObjectiveID ?
				break;

			case 4008: //PVE_UNKNOWN_A8	
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;

				break;
				///###
			case 4009: //summon unit
				Action_TEMP->CardFull = readUnsignedLong();
				Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
				Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
				Action_TEMP->ActionPlayer = readUnsignedLong();
				this->readUnsignedChar(); //Unknow8
				readUnsignedShort(); //Cardy
				readUnsignedShort(); //Cardz
				Action_TEMP->Charges = this->readUnsignedChar(); // Nur beim erstenmal rufen
				readUnsignedLong(); //X
				readUnsignedLong(); //Y
				readUnsignedLong(); //Zero
				break;
				///###
			case 4010: //cast spell
				Action_TEMP->CardFull = readUnsignedLong();
				Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
				Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
				Action_TEMP->ActionPlayer = readUnsignedLong();
				this->readUnsignedChar(); //Unknow8
				readUnsignedShort(); //Cardy
				readUnsignedShort(); //Cardz
				Action_TEMP->Charges = this->readUnsignedChar(); // Nur beim erstenmal rufen			
				readUnsignedLong(); //???
				this->readUnsignedChar(); //???
				readUnsignedLong(); //Value
				readUnsignedLong(); //Zero
				readUnsignedLong(); //Traget
				readUnsignedLong(); //X
				readUnsignedLong(); //Y
				break;
				///###
			case 4011: //cast line spell
				Action_TEMP->CardFull = readUnsignedLong();
				Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
				Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); //???
				this->readUnsignedChar(); //Unknow8 (immer 0 ?)
				Action_TEMP->Charges = this->readUnsignedChar(); // Nur beim erstenmal rufen
				this->readUnsignedChar(); //Unknow8 (immer 1 ?)
				readUnsignedLong(); //ummer 2 
				readUnsignedLong(); //Type 8 = line Spell?
				readUnsignedLong(); //Zero
				readUnsignedLong(); //Zero
				readUnsignedLong(); //X
				readUnsignedLong(); //Y
				readUnsignedLong(); //Type 8 = line Spell?
				readUnsignedLong(); //Zero
				readUnsignedLong(); //Zero
				readUnsignedLong(); //X
				readUnsignedLong(); //Y
				break;
				///###
			case 4012: //cast building
				Action_TEMP->CardFull = readUnsignedLong();
				Action_TEMP->Card = Action_TEMP->CardFull % 1000000;
				Action_TEMP->Upgrade = Action_TEMP->CardFull / 1000000;
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedShort(); //Cardy
				readUnsignedShort(); //Cardz
				readUnsignedLong(); //X
				readUnsignedLong(); //Y
				readUnsignedLong(); //Z
				readUnsignedLong(); //Zero
				readUnsignedShort(); //Carda
				readUnsignedShort(); //Cardb	
				Action_TEMP->Charges = this->readUnsignedChar(); // Nur beim erstenmal rufen	
				break;

				///X###X GGF. andere Movment Types analysieren?
			case 4013: //move unit
				Action_TEMP->ActionPlayer = readUnsignedLong();
				
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}

				tempCount = readUnsignedShort(); // Position Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // X
					readUnsignedLong(); // Y
				}
				this->readUnsignedChar(); //Move Type 2=Nomarl Move; 6=waypoint; 7=patrulie
				this->readUnsignedChar(); // Alwayse 1 ?
				readUnsignedLong(); // 0, 0, 0, ,0?
				break;
				
				///X###X GGF. Abbility Type analysieren?
			case 4014: //use unit ability
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
				readUnsignedLong(); // Abbility ID
				this->readUnsignedChar(); // immer 1
				readUnsignedLong(); // immer 1
				readUnsignedLong(); // Abbility Type - 2=Buldig Global Efffect / 6=Fier on the Ground / 8=Comet Catcher
				readUnsignedLong(); // Zero
				readUnsignedLong(); // Traget
				readUnsignedLong(); // X
				readUnsignedLong(); // Y				
				break;
				
				///X###X GGF. attac Type analysieren?
			case 4015: //attack				
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				this->readUnsignedChar(); // immer 1
				readUnsignedLong(); // immer 1
				readUnsignedLong(); // attac Type? Type - 1=normal / 6 Building?
				readUnsignedLong(); // Zero
				readUnsignedLong(); // Traget
				readUnsignedLong(); // X
				readUnsignedLong(); // Y				
				this->readUnsignedChar(); // immer 0

				break;
				///###
			case 4019: //stop unit
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				break;
				///###
			case 4020: //hold unit position
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				break;

				///X###X GGF. PING Type analysieren?
			case 4027: // PING (Meet / Help / ...)
				Action_TEMP->ActionPlayer = readUnsignedLong();
				this->readUnsignedChar(); // immer 1
				readUnsignedLong(); // immer 1
				readUnsignedLong(); // Ping Type? 8=
				readUnsignedLong(); // Zero
				readUnsignedLong(); // Zero (traget)
				readUnsignedLong(); // X
				readUnsignedLong(); // Y	
				readUnsignedShort(); // Ping Type? 4=				
				break;

				///###
			case 4028: //toggle wall gate
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
				break;

				///X###X GGF. letzter wert nicht immer zero
			case 4029: //build wall
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
				this->readUnsignedChar(); // Zero???				
				break;

				///###
			case 4030: //create mana
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); //Unit				
				break;
				///###
			case 4031: //create orb
				// 1 = Shadow
				// 2 = Green
				// 3 = Frost
				// 4 = Red
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); //Unit
				Action_TEMP->Color = this->readUnsignedChar();				
				break;
				
				///X###X Immer Zero?
			case 4033: //Unit move on Wall
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				readUnsignedLong(); // Unit WALL
				readUnsignedLong(); // Zero
				break;

				///###
			case 4034: //Switch Abbility (Stone Tempest)
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
				readUnsignedLong(); // Abbylity ID
				break;

				///x###x immer Zero?
			case 4035: //Trigger Reparier
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit / Building
				readUnsignedLong(); // Zero
				break;
				
				///###
			case 4036: //Move unit in decomposer // TESTEN ander key wenn man die abbiliti nutzt?
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}				
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit Decomposer
				break;

				///x###x Same bei T4 Schatten gebäude?
			case 4037: //Place Nexus Exit (oder generell Bulding?) // TESTEN T4 Schatten
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Nexus
				readUnsignedLong(); // X
				readUnsignedLong(); // Y	
				break;

				///###
			case 4038: //Go in Nexus
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				readUnsignedLong(); // Nexus				
				break;
				
				///###
			case 4040: // Switch Nexusportal Back
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Nexus				
				break;

				///###
			case 4041: //Killed own Unit
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedLong(); // Unit Count !!! Wiso ein Long???
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				break;

				///###
			case 4043: // go to Gold but not able to collect
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedLong(); // Unit Count !!! Wiso ein Long???
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				readUnsignedLong(); // Gold Chest		
				break;

				///###
			case 4044: // TW Unit Switch
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Ziel Card ID
				readUnsignedLong(); // Unknow - ändert sich - KP wann, BZW 1,3,4 bleiben gleich ? bei gleicher Ziel Unit?
				readUnsignedShort(); // immer 0 und 255 ?
				readUnsignedLong(); // Abbility ID
				this->readUnsignedChar(); // immer 1
				readUnsignedLong(); // immer 1
				readUnsignedLong(); // Type ? = 1
				readUnsignedLong(); // Zero
				readUnsignedLong(); // Traget
				readUnsignedLong(); // X
				readUnsignedLong(); // Y	
				break;
			
			default:
				MISERROR(FileName);
					MISERROR(sTime(Action_TEMP->Time) + "#" +
						to_string(Action_TEMP->Type) + "#" +
						to_string(PMVPosition) + " # " +
						to_string(MainSize) +
						"Unknow");
				
				//PMVPosition = SollPos;
				
			}			
			ActionMatrix.push_back(Action_TEMP);
		}			
		
		if (PMVPosition != SollPos)
		{
			MISERROR(FileName);
			MISERROR("wir sind off, soll:" + to_string(SollPos) + " ist:" + to_string(PMVPosition));
			MISERROR("Befor:" + to_string(ActionMatrix[ActionMatrix.size() - 1]->Type));
			PMVPosition = SollPos;
		}		
	}

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

	for (unsigned int i = 0; i < ActionMatrix.size(); i++)if (ActionMatrix[i]->ActionPlayer != 0 && ActionMatrix[i]->ActionPlayer < minActionPlayer)minActionPlayer = ActionMatrix[i]->ActionPlayer;

	//MISD("minActionPlayer:" + to_string(minActionPlayer));
	if (minActionPlayer == 4294967295 - 1) 
	{
		MISERROR("<-- cant find min Action Player");
		return false;
	}

	for (unsigned int i = 0; i < PlayerMatrix.size(); i++)PlayerMatrix[i]->ActionPlayer = minActionPlayer + i;	

	MISE;
	return true;
}

bool Replay::FillPlayerIDInAction()
{
	MISS;
	for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
	{
		for (unsigned int j = 0; j < ActionMatrix.size(); j++)
			if (ActionMatrix[j]->ActionPlayer == PlayerMatrix[i]->ActionPlayer)
			{
				ActionMatrix[j]->PlayerID = PlayerMatrix[i]->PlayerID;
			}
	}
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
			if (PlayerMatrix[i]->ActionPlayer == ActionMatrix[iPosOfUnit]->ActionPlayer &&
				(ActionMatrix[iPosOfUnit]->Type == 4012 //Building
					|| ActionMatrix[iPosOfUnit]->Type == 4011 //Spell 2
					|| ActionMatrix[iPosOfUnit]->Type == 4010 //Spell 1
					|| ActionMatrix[iPosOfUnit]->Type == 4009 //Unit
					))break;
		}
		if (iPosOfUnit == ActionMatrix.size())
		{
			//MISD("No Unit Played " + PlayerMatrix[i]->Name);
			continue;
		}

		Action_TEMP = new Action;
		Action_TEMP->Time = ActionMatrix[iPosOfUnit]->Time;
		//Action_TEMP->Size = 13;
		Action_TEMP->Type = 4031;
		Action_TEMP->ActionPlayer = ActionMatrix[iPosOfUnit]->ActionPlayer;
		Action_TEMP->Color = Bro->C_GetActionOrbForCardID(ActionMatrix[iPosOfUnit]->Card);
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


bool Replay::SetCharges()
{
	MISS;

	for (unsigned iActionMain = 0; iActionMain < ActionMatrix.size(); iActionMain++)
	{
		if ( (     ActionMatrix[iActionMain]->Type == 4012 //Building
			    || ActionMatrix[iActionMain]->Type == 4011 //Spell 2
				|| ActionMatrix[iActionMain]->Type == 4010 //Spell 1
				|| ActionMatrix[iActionMain]->Type == 4009 //Unit
			  ) && ActionMatrix[iActionMain]->Charges == 255)
		{
			for (unsigned iActionSub = 0; iActionSub < iActionMain; iActionSub++)
			{
				if (ActionMatrix[iActionMain]->Card == ActionMatrix[iActionSub]->Card
					&& ActionMatrix[iActionMain]->ActionPlayer == ActionMatrix[iActionSub]->ActionPlayer)
				{
					ActionMatrix[iActionMain]->Charges = ActionMatrix[iActionSub]->Charges;
					break;
				}
			}
		}		
	}

	MISE;
	return true;
}



string Replay::get_file_name(string pfad)
{
	pfad = pfad.substr(pfad.find("\\") + 1, pfad.length() - pfad.find("\\") + 1);
	if (pfad.find("\\") != pfad.npos) pfad = get_file_name(pfad);
	return pfad;
}



void Replay::EchoHead()
{
	MISS;
	MISD("Playtime:   " + to_string(Playtime));
	MISD("FileVersion:" + to_string(FileVersion));
	MISD("GameVersion:" + to_string(GameVersion));
	MISD("Playtime:   " + to_string(Playtime));
	MISD("Unknow3:    " + to_string(Unknow3));
	MISD("Unknow4:    " + to_string(Unknow4));
	MISD("MapName:    " + MapName);
	MISD("Seed:       " + to_string(Seed));
	MISD("MapID:      " + to_string(MapID));
	MISD("difficulty: " + to_string(DifficultyID));
	MISD("PlayMode:   " + to_string(PlayModeID));
	MISD("ActionBlock:" + to_string(ActionBlock));
	MISD("PMVFromPlay:" + to_string(PMVPlayerID));
	MISD("GroupCount: " + to_string(GroupCount));
	MISE;
}

void Replay::EchoAllied()
{
	MISS;
	MISD("MatrixCount:" + to_string(MatrixCount));
	MISD("count # i # j # v");
	for (unsigned int i = 0; i < MatrixCount; i++)
	{		
		MISD(to_string(i) + "#"
			+ to_string(AlliedMatrix[i]->i) + "#"
			+ to_string(AlliedMatrix[i]->j) + "#"
			+ to_string(AlliedMatrix[i]->v));
	}
	MISE;
}

void Replay::EchoTeam()
{
	MISS;
	MISD("TeamCount:" + to_string(TeamCount));
	MISD("Count # Name # GroupID # Value");
	for (unsigned int i = 0; i < TeamCount; i++)
	{
		MISD(to_string(i) + "#"
			+ TeamMatrix[i]->Name + "#"
			+ to_string(TeamMatrix[i]->GroupID) + "#"
			+ to_string(TeamMatrix[i]->Value));
	}
	MISE
}
	
void Replay::EchoPlayer()
{
	MISS;
	MISD("countP # Name # PlayerID # ActionPlayer # GroupID # IDinGroup # Type # Cards # CardsTotal")
		for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
		{
			MISD(to_string(i) + "#"
				+ PlayerMatrix[i]->Name + "#"
				+ to_string(PlayerMatrix[i]->PlayerID) + "#"
				+ to_string(PlayerMatrix[i]->ActionPlayer) + "#"
				+ to_string(PlayerMatrix[i]->GroupID) + "#"
				+ to_string(PlayerMatrix[i]->IDinGroup) + "#"
				+ to_string(PlayerMatrix[i]->Type) + "#"
				+ to_string(PlayerMatrix[i]->Cards) + "#"
				+ to_string(PlayerMatrix[i]->CardsTotal));
		}
	MISE;
}
	
void Replay::EchoPlayerDecks()
{
	MISS;
	MISD("countP # Name # PlayerID # ActionPlayer # GroupID # IDinGroup # Type # Cards # CardsTotal")
		for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
		{
			MISD(to_string(i) + "#"	+ PlayerMatrix[i]->Name );

			MISD("Count # DeckCardID # CardID # Upgrade # Charges")
				for (unsigned int j = 0; j < PlayerMatrix[i]->Deck.size(); j++)
				{
					MISD(to_string(j) + "#"
						+ to_string(PlayerMatrix[i]->Deck[j]->DeckCardID) + "#"
						+ to_string(PlayerMatrix[i]->Deck[j]->CardID) + "#"
						+ to_string(PlayerMatrix[i]->Deck[j]->Upgrade) + "#"
						+ to_string(PlayerMatrix[i]->Deck[j]->Charges));
				}

		}
	MISE;
}