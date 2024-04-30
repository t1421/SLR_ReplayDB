//#define DF_Debug

#include "..\incl\Broker.h" 

#include "..\incl\Replay.h" 
#include "..\incl\Utility.h" 

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

#ifndef BrokerPVP
bool Replay::LoadPMV(std::string sFile)
{
	MISS;

	OK = true;

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
#endif 

bool Replay::ReadHeader()
{
	MISS;

	Allied* Allied_TEMP;
	Team* Team_TEMP;
	Player* Player_TEMP;
	Card* Card_TEMP;
MISD("#1");
	FileVersion = readUnsignedLong();
	MISD(std::to_string(FileVersion));
	MISD("#2");	
	if (FileVersion > 200)GameVersion = readUnsignedLong();
	MISD(std::to_string(GameVersion));
	MISD("#3");	
	Playtime = readUnsignedLong();
	MISD(std::to_string(Playtime));
	MISD("#4");	
	if (FileVersion > 213)Seed = readUnsignedLong(); // Seed - wichtig f�r RPVE
	MISD(std::to_string(Seed));
	MISD("#5");	
MISD(std::to_string(PMVPosition));		
MISD("#10");	
	MapName = get_file_name(readString());
	MISD(MapName);	
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
	PMVPlayerID = readUnsignedLongLong();
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
	MISD("Teams:" + std::to_string(TeamCount));
	for (int i = 0; i < TeamCount; i++)
	{
		MISD("#NR  :" + std::to_string(i));
		Team_TEMP = new Team;
		MISD("#NR  :" + std::to_string(i) + "#1");
		Team_TEMP->Name = readString();
		MISD("#NR  :" + std::to_string(i) + "#2");
		Team_TEMP->GroupID = readUnsignedLong();
		MISD("#NR  :" + std::to_string(i) + "#3");
		Team_TEMP->Value = readUnsignedShort();
		MISD("#NR  :" + std::to_string(i) + "#4");
		TeamMatrix.push_back(Team_TEMP);
		MISD("#NR  :" + std::to_string(i) + "#5");
	}
	
	MISD("Player");
	
	while (PMVPosition < ActionBlock)
	{
		Player_TEMP = new Player;
		Player_TEMP->Name = readWString();
		Player_TEMP->PlayerID = readUnsignedLongLong();
		Player_TEMP->GroupID = readUnsignedChar();
		Player_TEMP->IDinGroup = readUnsignedChar();
		Player_TEMP->Type = readUnsignedChar();
		Player_TEMP->CardsTotal = readUnsignedShort();

		PlayerMatrix.push_back(Player_TEMP);	
		
		MISD("Player_TEMP->Name    " + Player_TEMP->Name);
		MISD("Player_TEMP->PlayerID" + std::to_string(Player_TEMP->PlayerID));
		MISD("Player_TEMP->GroupID" + std::to_string(Player_TEMP->GroupID));
		MISD("Player_TEMP->IDinGroup" + std::to_string(Player_TEMP->IDinGroup));
		MISD("Player_TEMP->Type" + std::to_string(Player_TEMP->Type));
		MISD("Player_TEMP->CardsTotal" + std::to_string(Player_TEMP->CardsTotal));

MISD("PlayerX");

		for (int i = 0; i < PlayerMatrix[PlayerMatrix.size() - 1]->CardsTotal; i++)
		{
			//MISD(std::to_string(i) + " / " + std::to_string(PlayerMatrix[PlayerMatrix.size() - 1]->CardsTotal));
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
#if defined BrokerPVP
		PlayerMatrix[PlayerMatrix.size() - 1]->Deck.clear();
#endif 
	}

	if (ActionBlock != PMVPosition)
	{
		MISERROR("<-- ActionBlockOffsetError soll:" + std::to_string(ActionBlock) + " ist:" + std::to_string(PMVPosition));
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
		if (MainTime == 2147483647)
		{			
			readUnsignedLong(); // 4
			readUnsignedLong(); // 666
			continue;
		}
		MainSize = readUnsignedLong();
		SollPos = PMVPosition + MainSize;

		while (PMVPosition < SollPos)
		{
			Action_TEMP = new Action;
			Action_TEMP->Time = MainTime;
			Action_TEMP->Position = PMVPosition;
			Action_TEMP->Type = readUnsignedLong();
			//MISERROR(std::to_string(Action_TEMP->Type));
			switch (Action_TEMP->Type)
			{
			case 4001: //SLR-TEAM: 4001 - Irrelevant (Ist bei mir einfach auskommentiert)
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
				///###
			case 4002: //leave game		
				Action_TEMP->ActionPlayer = readUnsignedLong();
				break;
				///###
			case 4003: //SLR-TEAM: 4003 - Desync
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4004: //12 Player Map Special	(Sync von Maps 1 bis 3 ? )		// Anzahl von Gegnern auf der Map?					
				readUnsignedLong(); //Unit
				Action_TEMP->AdditionalInfo = std::to_string(this->readUnsignedChar()); // ??? number between 0 and 16?				
				break;
				///###
			case 4005: //SLR-TEAM: 4005 - Hat was mit Loot Verteilung zu tun					
				Action_TEMP->ActionPlayer = readUnsignedLong(); //Player
				readUnsignedLong(); //zero?
				readUnsignedLong(); //loot_target
				readUnsignedLong(); //map_loot_id
				break;
			case 4006: //GOLD	
				Action_TEMP->PlayerID = readUnsignedLongLong(); // wer hat eingesammelt
				readUnsignedLong(); // Unit
				tempCount = readUnsignedLong();
				for (unsigned int i = 0; i < tempCount; i++)
				{
					readUnsignedLongLong(); // wer erh�lt gold					
					if(i==0)Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); // menge gold
					else readUnsignedLong(); // menge gold
				}
				break;
				///###
			case 4007: //Objective OK 
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); //ObjectiveID
				break;

			case 4008: //SLR-TEAM: 4008 - Hat was mit Scripting zu tun (wahrsch. iwas zum Map scripts debuggen oder so)
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
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
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); // Abbility ID
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
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4017: //SLR-TEAM: 4017 - Glaube das sind ultrakrasse GM Hacks
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4018: //SLR-TEAM: 4018 - Auskommentiert (KillEntity - glaube unn�tig, da es and GroupKillEntity gibt)
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
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
			case 4021: //SLR-TEAM: 4021 - Auskommentiert (PlaceSquad - wahrscheinlich auch durch was anderes �berschrieben
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4022: //SLR-TEAM: 4022 - Irgendwas mit Mapscripts
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4023: //SLR-TEAM: 4023 - Auskommentiert (CancelCutScene)
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4024: //SLR-TEAM:4024 - Relevant f�r die Schmiede
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4025: //SLR-TEAM: 4025 - Relevant f�r die Schmiede
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
					" ???");
				PMVPosition = SollPos;
				break;
			case 4026: //SLR-TEAM: 4026 - SetGameDifficulty - glaube nicht, dass man das w�hrend des Spiels machen kann
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
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
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedShort()); // Ping Type
				//0=Ping,1=Attack,2=Def,3=Help,4=Meet
				break;

				///###
			case 4028: //toggle wall gate
				Action_TEMP->ActionPlayer = readUnsignedLong();
				readUnsignedLong(); // Unit
				break;

				///X###X GGF. letzter wert nicht immer zero
			case 4029: //build wall
				Action_TEMP->ActionPlayer = readUnsignedLong();
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); //Unit	
				this->readUnsignedChar(); // Zero???				
				break;

				///###
			case 4030: //create mana
				Action_TEMP->ActionPlayer = readUnsignedLong();
				Action_TEMP->AdditionalInfo = std::to_string( readUnsignedLong() ); //Unit				
				break;
				///###
			case 4031: //create orb
				// 1 = Shadow
				// 2 = Green
				// 3 = Frost
				// 4 = Red
				Action_TEMP->ActionPlayer = readUnsignedLong();
				tempCount = readUnsignedLong(); //Unit
				Action_TEMP->AdditionalInfo = std::to_string(this->readUnsignedChar()) + ";" + std::to_string(tempCount);
				break;
			case 4032: //SLR-TEAM: 4032 - SquadRefill - Dachte das passiert automatisch?
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(Action_TEMP->Position) + " # " +
					std::to_string(MainSize) +
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
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); // Abbylity ID
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

				///x###x Same bei T4 Schatten geb�ude?
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
					Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + std::to_string(this->readUnsignedLong()) + ";" ; // Unit
					//readUnsignedLong(); // Unit
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
				Action_TEMP->AdditionalInfo = std::to_string(readUnsignedLong()); // Ziel Card ID
				readUnsignedLong(); // Unknow - �ndert sich - KP wann, BZW 1,3,4 bleiben gleich ? bei gleicher Ziel Unit?
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
			case 4045: // SLR desync
#if defined BrokerPVP
				PMVPosition = SollPos;
				goto SKIP;
#else

				readUnsignedShort(); //Size of Data
				switch (this->readUnsignedChar()) //ID of inner Data
				{
					case 2: // Desync
						Action_TEMP->AdditionalInfo = "2;";
						readUnsignedLongLong(); // state health_hasher
						readUnsignedLongLong(); // state position_hasher
						readUnsignedLongLong(); // state power_hasher
						readUnsignedLongLong(); // state health_rounded_hasher
						readUnsignedLongLong(); // state position_rounded_hasher
						readUnsignedLongLong(); // state power_rounded_hasher
						Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + std::to_string(this->readUnsignedLong()) + ";"; // Count figures on map
						Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + std::to_string(this->readUnsignedLong()) + ";"; // Count entities on map
						readUnsignedLong(); // Steps
						break;

					case 3: //Pause tracker
						Action_TEMP->AdditionalInfo = "3;";
						readUnsignedLong(); // Pause Time
						break;

					case 4: //Goal Checker
						Action_TEMP->AdditionalInfo = "4;";
						Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + readString() + ";"; // Goal Name
						Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + std::to_string(this->readUnsignedChar()) + ";"; // Goal Status
						break;
					case 5: //MapModifirer?
						Action_TEMP->AdditionalInfo = "5;";
						Action_TEMP->AdditionalInfo = std::to_string(this->readUnsignedLong()) + ";"; // Player ID
						Action_TEMP->AdditionalInfo = Action_TEMP->AdditionalInfo + std::to_string(this->readUnsignedLong()) + ";"; // SPELL ID
						break;
					case 6: //BotsStats 
						Action_TEMP->AdditionalInfo = "6;";
						tempCount = this->readUnsignedChar(); // BotCount
						MISD(tempCount);
						for (unsigned int i = 0; i < tempCount; i++)
						{
							Action_TEMP->AdditionalInfo += readString() + ";"; //BOT NAME
							readUnsignedLong(); //Time Spend
							readUnsignedLong(); //Actions
							readUnsignedLong(); //InvActions
							this->readUnsignedChar(); //Errors
						}						
						break;

					default:
						MISERROR(FileName);
						MISERROR(sTime(Action_TEMP->Time) + "#" +
							std::to_string(Action_TEMP->Type) + "#" +
							std::to_string(PMVPosition) + " # " +
							std::to_string(MainSize) +
							"NEW SLR KEY: ");
						PMVPosition = SollPos;

				}
				break;
#endif
			default:
				MISERROR(FileName);
				MISERROR(sTime(Action_TEMP->Time) + "#" +
					std::to_string(Action_TEMP->Type) + "#" +
					std::to_string(PMVPosition) + " # " +
					std::to_string(MainSize) +
					"Unknow");
				PMVPosition = SollPos;
				OK = false;								
			}			
			ActionMatrix.push_back(Action_TEMP);
		SKIP:;
		}			

	}

	MISE;
	return true;
}


bool Replay::ConnectActionToPlayer()
{
	MISS;
	unsigned long minActionPlayer = 4294967295 - 1;

	for (unsigned int i = 0; i < ActionMatrix.size(); i++)if (ActionMatrix[i]->ActionPlayer != 0 && ActionMatrix[i]->ActionPlayer < minActionPlayer)minActionPlayer = ActionMatrix[i]->ActionPlayer;

	//MISD("minActionPlayer:" + std::to_string(minActionPlayer));
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
		Action_TEMP->AdditionalInfo = std::to_string(Bro->J_GetActionOrbForCardID(ActionMatrix[iPosOfUnit]->Card));
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



std::string Replay::get_file_name(std::string pfad)
{
	pfad = pfad.substr(pfad.find("\\") + 1, pfad.length() - pfad.find("\\") + 1);
	if (pfad.find("\\") != pfad.npos) pfad = get_file_name(pfad);
	return pfad;
}



void Replay::EchoHead()
{
	MISS;
	printf("Playtime:   %lu\n", Playtime);
	printf("FileVersion:%lu\n", FileVersion);
	printf("GameVersion:%lu\n", GameVersion);;
	printf("Unknow3:    %u\n", Unknow3);
	printf("Unknow4:    %u\n", Unknow4);
	printf("MapName:    %s\n", MapName.c_str());
	printf("Seed:       %lu\n", Seed);
	printf("MapID:      %lu\n", MapID);
	printf("difficulty: %u\n", DifficultyID);
	printf("PlayMode:   %u\n", PlayModeID);
	printf("ActionBlock:%lu\n", ActionBlock);
	printf("PMVFromPlay:%llu\n", PMVPlayerID);
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
		printf("%u # %s # %lu # %u \n", 
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
	printf("countP # Name # PlayerID # ActionPlayer # GroupID # IDinGroup # Type # CardsTotal\n");
		for (unsigned int i = 0; i < PlayerMatrix.size(); i++)
		{
			printf("%u # %s # %llu # %lu # %u # %u # %u # %u # %u\n",
			i ,
			PlayerMatrix[i]->Name.c_str() ,
			PlayerMatrix[i]->PlayerID ,
			PlayerMatrix[i]->ActionPlayer ,
			PlayerMatrix[i]->GroupID ,
			PlayerMatrix[i]->IDinGroup ,
			PlayerMatrix[i]->Type ,
			//PlayerMatrix[i]->Cards ,
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

void Replay::EchoAction(std::string sAction)
{
	MISS;
	printf("count # Time # Position # Type # ActionPlayer # PlayerID # Card # AdditionalInfo \n");
	for (unsigned int i = 0; i < ActionMatrix.size(); i++)
	{
		if (ActionMatrix[i]->Type == 4045 && sAction != std::to_string(4045))continue;
		if (std::to_string(ActionMatrix[i]->Type) == sAction || sAction == "*")
		{
			printf("%u # %s # %u # %lu  # %lu # %llu  # %lu # %s \n", 
				i,
				sTime(ActionMatrix[i]->Time).c_str() ,
				ActionMatrix[i]->Position, 
				ActionMatrix[i]->Type ,
				ActionMatrix[i]->ActionPlayer ,
				ActionMatrix[i]->PlayerID ,
				ActionMatrix[i]->Card ,
				ActionMatrix[i]->AdditionalInfo.c_str() 
			);
		}

	}
	MISE;
}


std::string Replay::FindWinningTeam()
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
		if (std::to_string(ActionMatrix[i]->Type) == "4002") //Leave game
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

bool Replay::getPMVinSS(std::string sFile)
{
	MISS;
	//For SQL Upload
	std::ifstream ifs;
	ifs.open(sFile, std::ifstream::binary | std::ifstream::in);
	if (ifs)
	{
		ssPMVFile << ifs.rdbuf();
		ifs.clear();
		ifs.close();
		MISEA("X1");
		return true;
	}

	MISEA("X2");
	return false;
}


std::string Replay::SwitchType(unsigned long inType)
{
	//MISS;

	switch(inType)
	{
	case 4001: 	
		return "?4001 ?";
	case 4002: 
		return "Surrender ";
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
		return "SLR Function";
	default:
		return "NO IDEA!!!";
	}
	
	return "";
	//MISE;
}


int Replay::CountActions(std::string sAction)
{
	MISS;
	int iOut = 0;
	for (unsigned int i = 0; i < ActionMatrix.size(); i++)
	{
		if (ActionMatrix[i]->Type == 4045)continue;
		if (std::to_string(ActionMatrix[i]->Type) == sAction || sAction == "*")iOut++;
	}
	
	MISE;
	return iOut;
}

#if defined BrokerPVP
int Replay::readDelta()
{
	MISS;
	int PMVReturn = 0;
	
	if (!OK)
	{
		MISEA("Kein Delat befor head");
		return -1;
	}

	PMVReturn = readDeltaPMV();
	if (PMVReturn == 0 || PMVReturn == -1)
	{
		MISEA("Nichts neues");
		return PMVReturn;
	}
	//PMVPosition = 0;

	ReadActions();


	MISE;
	return 1;
}

bool Replay::LoadPMV(std::string sFile)
{
	MISS;

	OK = true;

	if (!Open(sFile))
	{
		MISERROR("<-- error opening PMV");
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
	/*
	if (ConnectActionToPlayer() == false)
	{
		MISERROR("<-- ConnectActionToPlayer faild");
		OK = false;
		return false;
	}
	*/
	/*
	if (FillPlayerIDInAction() == false)
	{
		MISERROR("<-- FillPlayerIDInAction faild");
		OK = false;
		return false;
	}
	*/

	//WinningTeam = FindWinningTeam();

	MISE;
	return OK;
}
#endif