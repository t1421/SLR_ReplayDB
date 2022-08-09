#define DF_Debug

#include "prototypes.h"

#include "Replay.h" 

#ifndef noBroker
broker *(Replay::Bro) = NULL;
#endif

Replay::Replay()
{
	MISS;
	OK = true;
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
		OK = false;
		return false;
	}
	FileName = get_file_name(sFile);


	if (getPMVinSS(sFile) == false)
	{
		MISERROR("<-- ReadHeader getPMVinSS");
		OK = false;
		return false;
	}

	if (ReadHeader() == false)
	{
		MISERROR("<-- ReadHeader faild");
		OK = false;
		return false;
	}

	if (ReadActions() == false)
	{
		MISERROR("<-- ReadActions faild");
		OK = false;
		return false;
	}

	if (ConnectActionToPlayer() == false)
	{
		MISERROR("<-- ConnectActionToPlayer faild");
		OK = false;
		return false;
	}

	if (AddFirstOrb() == false)
	{
		MISERROR("<-- AddFirstOrb faild");
		OK = false;
		return false;
	}

	if (SetMinLeaveTime() == false)
	{
		MISERROR("<-- SetMinLeaveTime faild");
		OK = false;
		return false;
	}

	if (SetCharges() == false)
	{
		MISERROR("<-- SetCharges faild");
		OK = false;
		return false;
	}

	if (FillPlayerIDInAction() == false)
	{
		MISERROR("<-- FillPlayerIDInAction faild");
		OK = false;
		return false;
	}

	WinningTeam = FindWinningTeam();

	MISE;
	return OK;
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
			case 4001: //SLR-TEAM: 4001 - Irrelevant (Ist bei mir einfach auskommentiert)
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
				///###
			case 4002: //leave game		
				Action_TEMP->SystemAction = true;
				Action_TEMP->ActionPlayer = readUnsignedLong();
				break;
				///###
			case 4003: //SLR-TEAM: 4003 - Desync
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4004: //12 Player Map Special	(Sync von Maps 1 bis 3 ? )		// Anzahl von Gegnern auf der Map?					
				Action_TEMP->SystemAction = true;
				readUnsignedLong(); //Unit
				this->readUnsignedChar(); // ??? number between 0 and 16?				
				break;
				///###
			case 4005: //SLR-TEAM: 4005 - Hat was mit Loot Verteilung zu tun					
				//Action_TEMP->ActionPlayer = readUnsignedLong();
				//readUnsignedLong(); //zero?
				//readUnsignedLong(); //Unit?
				//readUnsignedLong(); //zero?
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
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
				Action_TEMP->SystemAction = true;
				readUnsignedLong(); // ObjectiveID ?
				break;

			case 4008: //SLR-TEAM: 4008 - Hat was mit Scripting zu tun (wahrsch. iwas zum Map scripts debuggen oder so)
				Action_TEMP->SystemAction = true;
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
				readUnsignedLong(); // if (readUnsignedLong() == 6) Action_TEMP->SystemAction = true; // Type 1=normal / 2=Building / 6=AutoArack nach Spawn 
				readUnsignedLong(); // Zero
				readUnsignedLong(); // Traget
				readUnsignedLong(); // X
				readUnsignedLong(); // Y				
				this->readUnsignedChar(); // immer 0

				break;
			case 4016: //SLR-TEAM: 4016 - Ist bei mir auch auskommentiert
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4017: //SLR-TEAM: 4017 - Glaube das sind ultrakrasse GM Hacks
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4018: //SLR-TEAM: 4018 - Auskommentiert (KillEntity - glaube unnötig, da es and GroupKillEntity gibt)
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
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
			case 4021: //SLR-TEAM: 4021 - Auskommentiert (PlaceSquad - wahrscheinlich auch durch was anderes Überschrieben
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4022: //SLR-TEAM: 4022 - Irgendwas mit Mapscripts
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4023: //SLR-TEAM: 4023 - Auskommentiert (CancelCutScene)
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4024: //SLR-TEAM:4024 - Relevant für die Schmiede
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4025: //SLR-TEAM: 4025 - Relevant für die Schmiede
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4026: //SLR-TEAM: 4026 - SetGameDifficulty - glaube nicht, dass man das während des Spiels machen kann
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
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
			case 4032: //SLR-TEAM: 4032 - SquadRefill - Dachte das passiert automatisch?
				Action_TEMP->SystemAction = true;
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(Action_TEMP->Position) + " # " +
					to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
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
				readUnsignedLong(); // Unit Decomposer
				Action_TEMP->ActionPlayer = readUnsignedLong();				
				break;

				///x###x Same bei T4 Schatten gebäude?
			case 4037: //Place Nexus Exit (oder generell Bulding?) // TESTEN T4 Schatten
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Nexus
				readUnsignedLong(); // X
				readUnsignedLong(); // Y	
				break;

				///###
			case 4038: //Use Tunnel
				tempCount = readUnsignedShort(); // Unit Count
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLong(); // Unit
				}
				readUnsignedLong(); // Nexus				
				break;				
				///###
			case 4039: // Switch Tunnel
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
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
			case 4042: // Placing Altar Of Chaos Totem
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit		
				readUnsignedLong(); // X
				readUnsignedLong(); // Y	
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
			case 4045: // SLR desync???
				Action_TEMP->SystemAction = true;
				readUnsignedShort(); //Size of Data
				this->readUnsignedChar(); //ID of inner Data
				readUnsignedLongLong(); // state Hash 1
				readUnsignedLongLong(); // state Hash 2
				readUnsignedLongLong(); // state Hash 3
				readUnsignedLongLong(); // state Hash 4
				readUnsignedLongLong(); // state Hash 5
				readUnsignedLongLong(); // state Hash 6
				readUnsignedLong(); // Count figures on map
				readUnsignedLong(); // count entities on map
				readUnsignedLong(); // Steps
				break;
			
			default:
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					to_string(Action_TEMP->Type) + "#" +
					to_string(PMVPosition) + " # " +
					to_string(MainSize) +
					"Unknow");
				PMVPosition = SollPos;
				OK = false;								
			}			
			ActionMatrix.push_back(Action_TEMP);
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
	printf("Playtime:   %u\n", Playtime);
	printf("FileVersion:%u\n", FileVersion);
	printf("GameVersion:%u\n", GameVersion);;
	printf("Unknow3:    %u\n", Unknow3);
	printf("Unknow4:    %u\n", Unknow4);
	printf("MapName:    %s\n", MapName.c_str());
	printf("Seed:       %u\n", Seed);
	printf("MapID:      %u\n", MapID);
	printf("difficulty: %u\n", DifficultyID);
	printf("PlayMode:   %u\n", PlayModeID);
	printf("ActionBlock:%u\n", ActionBlock);
	printf("PMVFromPlay:%u\n", PMVPlayerID);
	printf("GroupCount :%u\n", GroupCount);
	printf("WinningTeam:%s\n", WinningTeam.c_str());
	printf("FileName   :%s\n", FileName.c_str());
	MISE;
}

void Replay::EchoAllied()
{
	MISS;
	printf("MatrixCount:%u\n", MatrixCount);
	printf("count # i # j # v\n");
	for (unsigned int i = 0; i < MatrixCount; i++)
	{		
		printf("%u # %u # %u # %u \n",
			i ,
			AlliedMatrix[i]->i ,
			AlliedMatrix[i]->j ,
			AlliedMatrix[i]->v);
	}
	MISE;
}

void Replay::EchoTeam()
{
	MISS;
	printf("TeamCount:%u\n", TeamCount);
	printf("Count # Name # GroupID # Value\n");
	for (unsigned int i = 0; i < TeamCount; i++)
	{
		printf("%u # %s # %u # %u \n", 
			i ,
			TeamMatrix[i]->Name.c_str() ,
			TeamMatrix[i]->GroupID ,
			TeamMatrix[i]->Value);
	}
	MISE
}
	
void Replay::EchoPlayer()
{
	MISS;
	printf("countP # Name # PlayerID # ActionPlayer # GroupID # IDinGroup # Type # Cards # CardsTotal\n");
		for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
		{
			printf("%u # %s # %u # %u # %u # %u # %u # %u # %u\n",
			i ,
			PlayerMatrix[i]->Name.c_str() ,
			PlayerMatrix[i]->PlayerID ,
			PlayerMatrix[i]->ActionPlayer ,
			PlayerMatrix[i]->GroupID ,
			PlayerMatrix[i]->IDinGroup ,
			PlayerMatrix[i]->Type ,
			PlayerMatrix[i]->Cards ,
			PlayerMatrix[i]->CardsTotal);
		}
	MISE;
}
	
void Replay::EchoPlayerDecks()
{
	MISS;
	printf("countP # Name\n");
		for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
		{
			printf("%u # %s\n", i , PlayerMatrix[i]->Name.c_str() );

			printf("##> Count # DeckCardID # CardID # Upgrade # Charges\n");
				for (unsigned int j = 0; j < PlayerMatrix[i]->Deck.size(); j++)
				{
					printf("##> %u # %u # %u # %u # %u \n",
						j,
						PlayerMatrix[i]->Deck[j]->DeckCardID ,
						PlayerMatrix[i]->Deck[j]->CardID ,
						PlayerMatrix[i]->Deck[j]->Upgrade ,
						PlayerMatrix[i]->Deck[j]->Charges);
				}
		}
	MISE;
}

void Replay::EchoAction(string sAction)
{
	MISS;
	printf("count # Time # Position # Type # ActionPlayer # PlayerID # Card \n");
	for (unsigned int i = 0; i < ActionMatrix.size(); i++)
	{
		if (ActionMatrix[i]->Type == 4045)continue;
		if (to_string(ActionMatrix[i]->Type) == sAction || sAction == "*")
			printf("%u # %s # %u # %u # %u # %u # %u \n",
				i ,
				sTime(ActionMatrix[i]->Time).c_str() ,
				ActionMatrix[i]->Position ,
				ActionMatrix[i]->Type ,
				ActionMatrix[i]->ActionPlayer ,
				ActionMatrix[i]->PlayerID ,			
				ActionMatrix[i]->Card );

	}
	MISE;
}


string Replay::FindWinningTeam()
{
	MISS;
	unsigned int iCountTeam1 = 0;
	unsigned int iCountLeft1 = 0;
	unsigned int iCountTeam2 = 0;
	unsigned int iCountLeft2 = 0;

	for (unsigned int i = 0; i < TeamMatrix.size(); i++)
	{
		//MISD(TeamMatrix[i]->Name);
		if (TeamMatrix[i]->Name == "TM_TEAM1") iCountTeam1++;
		if (TeamMatrix[i]->Name == "TM_TEAM2") iCountTeam2++;
	}

	if (iCountTeam1 == 0)
	{
		MISEA("#10");
		return "TM_TEAM2";
	}
	if (iCountTeam2 == 0)
	{
		MISEA("#11");
		return "TM_TEAM1";
	}

	for (unsigned int i = 0; i < ActionMatrix.size(); i++)
	{
		if (to_string(ActionMatrix[i]->Type) == "4002") //Leave game
		{
			for (unsigned int j = 0; j < PlayerMatrix.size(); j++)
			{
				if (PlayerMatrix[j]->ActionPlayer == ActionMatrix[i]->ActionPlayer)
				{
					for (unsigned int k = 0; k < TeamMatrix.size(); k++)
					{
						if (TeamMatrix[k]->GroupID == PlayerMatrix[j]->GroupID &&
							TeamMatrix[k]->Name == "TM_TEAM1")iCountLeft1++;
						if (TeamMatrix[k]->GroupID == PlayerMatrix[j]->GroupID &&
							TeamMatrix[k]->Name == "TM_TEAM2")iCountLeft2++;
					}
				}
			}
		}
	}

	if (iCountTeam1 == iCountLeft1)
	{
		MISEA("#20");
		return "TM_TEAM2";
	}
	if (iCountTeam2 == iCountLeft2)
	{
		MISEA("#21");
		return "TM_TEAM1";
	}


	for (unsigned int i = ActionMatrix.size() - 1; i > 0; i--)
	{
		if (ActionMatrix[i]->ActionPlayer != 0)
		{
			for (unsigned int j = 0; j < PlayerMatrix.size(); j++)
			{
				if (PlayerMatrix[j]->ActionPlayer == ActionMatrix[i]->ActionPlayer)
				{
					for (unsigned int k = 0; k < TeamMatrix.size(); k++)
					{
						if (TeamMatrix[k]->GroupID == PlayerMatrix[j]->GroupID &&
							TeamMatrix[k]->Name == "TM_TEAM1")
						{
							if (ActionMatrix[i]->Type == 4041 && PlayModeID == 2) // Kill Own Unit in PVP
							{
								MISEA("#40");
								return "TM_TEAM2";
							}
							MISEA("#30");
							return "TM_TEAM1";
						}
						if (TeamMatrix[k]->GroupID == PlayerMatrix[j]->GroupID &&
							TeamMatrix[k]->Name == "TM_TEAM2")
						{
							if (ActionMatrix[i]->Type == 4041 && PlayModeID == 2) // Kill Own Unit in PVP
							{
								MISEA("#41");
								return "TM_TEAM1";
							}
							MISEA("#31");
							return "TM_TEAM2";
						}
					}
				}
			}
		}
	}


	MISERROR("<-- NO WINNER!!!");
	return "";
}

bool Replay::getPMVinSS(string sFile)
{
	MISS;
	//For SQL Upload
	ifstream ifs;
	ifs.open(sFile, std::ifstream::binary | std::ifstream::in);
	if (ifs)
	{
		ssPMVFile << ifs.rdbuf();
		ifs.close();
		MISEA("X1");
		return true;
	}

	MISEA("X2");
	return false;
}


string Replay::SwitchType(unsigned long inType)
{
	//MISS;

	switch(inType)
	{
	case 4001: 	
		return "?4001 ?";
	case 4002: 
		return "Leave game";
	case 4003:
		return "Desync";
	case 4004: 
		return "12Player sync";
	case 4005: 
		return "?4005 Loot";
	case 4006: 
		return "Open Gold";
	case 4007: 
		return "Objective OK";
	case 4008: 
		return "?4008 Map Debug";
	case 4009: 
		return "Summon unit";
	case 4010: 
		return "Cast spell";
	case 4011: 
		return "Cast line spell";
	case 4012: 
		return "Cast building";
	case 4013: 
		return "Move unit";
	case 4014: 
		return "Use ability";
	case 4015: 
		return "Attack";
	case 4016:
		return "?4016 ?";
	case 4017:
		return "?4017 GM Stuf";
	case 4018:
		return "old KillEntity";
	case 4019: 
		return "Stop unit";
	case 4020:
		return "Hold position";
	case 4021:
		return "old PlaceSqua";
	case 4022:
		return "Mapscripts";
	case 4023:
		return "StopCutScene";
	case 4024:
		return "4024 Forge";
	case 4025:
		return "4025 Forge";
	case 4026:
		return "SetDifficulty";
	case 4027: 
		return "Ping";
	case 4028: 
		return "Switch Gate";
	case 4029: 
		return "Build/Rep. wall";
	case 4030: 
		return "Build well";
	case 4031:
		return "Build orb";
	case 4032:
		return "SquadRefill ";
	case 4033: 
		return "Move on wall";
	case 4034: 
		return "Switch ability";
	case 4035: 
		return "Repair building";
	case 4036: 
		return "Move into Decom.";
	case 4037: 
		return "Place Nexusexit";
	case 4038: 
		return "Use tunnel";
	case 4039: 
		return "Switch tunnel";
	case 4040: 
		return "Return Nexusexit";
	case 4041: 
		return "Kill own unit";
	case 4042: 
		return "Place Chaostotem";
	case 4043: 
		return "Cant get Gold";
	case 4044:
		return "Switch Twilight";
	case 4045:
		return "Desync Check";
	default:
		return "NO IDEA!!!";
	}
	
	return "";
	//MISE;
}

int Replay::CountActions()
{
	MISS;
	int iOut = 0;
	for (unsigned int i = 0; i < ActionMatrix.size(); i++)
	{
		if (ActionMatrix[i]->Type == 4045)continue;
		iOut++;
	}
	
	MISE;
	return iOut;
}