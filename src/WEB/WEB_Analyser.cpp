//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Replay.h" 

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_Analyser_Head.h"
#include "..\..\incl\WEB\WEB_Analyser_Deck.h"
#include "..\..\incl\WEB\WEB_Analyser_Acti.h"


broker *(WEB_Analyser::Bro) = NULL;

WEB_Analyser::WEB_Analyser(): R(new Replay())
{
	MISS;
	
	ActionSum* ActionSum_Tmp;
	for (unsigned int i = 4000; i <= 4045; i++)
	{
		ActionSum_Tmp = new ActionSum();
		ActionSum_Tmp->ActionID = i;
		ActionSum_Tmp->sActionName = R->SwitchType(i);
		ActionSum_Tmp->iCount = 0;
		ActionSum_Tmp->wcBox = new Wt::WCheckBox(ActionSum_Tmp->sActionName);
		ActionSum_Tmp->wcBox->setChecked(true);
		ActionSums.push_back(ActionSum_Tmp);
	}
	
	MISD("#1");

	Head = new WEB_Analyser_Head(this);
	Deck = new WEB_Analyser_Deck(this);
	Acti = new WEB_Analyser_Acti(this);

	MISE;
}

bool WEB_Analyser::isOK() 
{ 
	return R->OK; 
};

bool WEB_Analyser::NewReplay(std::string sFile)
{
	R = new Replay();
	if(R->LoadPMV(sFile))return getData();
	else return false;
}

bool WEB_Analyser::getData()
{
	MISS;

	Players.clear();
	Players.clear();
	Actions.clear();

	Player *Player_Temp;
	Card *Card_Temp;
	ActionWeb *Action_Temp;

	unsigned int CardLoop;
	bool Found;

	for (unsigned int i = 0; i < R->PlayerMatrix.size(); i++)
	{
		MISD(std::to_string(R->PlayerMatrix[i]->Deck.size()));
		Player_Temp = new Player;
		//Player_Temp = R->PlayerMatrix[i];
		Player_Temp->Name = R->PlayerMatrix[i]->Name;
		Player_Temp->PlayerID = R->PlayerMatrix[i]->PlayerID;
		Player_Temp->ActionPlayer = R->PlayerMatrix[i]->ActionPlayer;
		Player_Temp->GroupID = R->PlayerMatrix[i]->GroupID;
		Player_Temp->IDinGroup = R->PlayerMatrix[i]->IDinGroup;
		Player_Temp->Type = R->PlayerMatrix[i]->Type;
		Player_Temp->wcBox = new Wt::WCheckBox(Player_Temp->Name);
		Player_Temp->iActionCount = 0;
		Player_Temp->wcBox->setChecked(true);
		Player_Temp->Deck.clear();
		for (unsigned int j = 0; j < R->ActionMatrix.size(); j++)
		{
			if (R->ActionMatrix[j]->PlayerID != R->PlayerMatrix[i]->PlayerID)continue;
			if (R->ActionMatrix[j]->Type != 4012 //Building
				&& R->ActionMatrix[j]->Type != 4011 //Spell 2
				&& R->ActionMatrix[j]->Type != 4010 //Spell 1
				&& R->ActionMatrix[j]->Type != 4009 //Unit
				)continue;

			Found = false;
			for (CardLoop = 0; CardLoop < Player_Temp->Deck.size(); CardLoop++)
				if (Player_Temp->Deck[CardLoop]->CardID == R->ActionMatrix[j]->Card)
				{
					Found = true;
					break;
				}

			if (Found == false)
			{
				//MISD("ADD   :" + std::to_string(R->ActionMatrix[j]->Card));
				Card_Temp = new Card;
				Card_Temp->CardID = R->ActionMatrix[j]->Card;
				Card_Temp->Charges = R->ActionMatrix[j]->Charges;
				Card_Temp->Upgrade = R->ActionMatrix[j]->Upgrade;
				Card_Temp->count = 0;
				Player_Temp->Deck.push_back(Card_Temp);
			}
			Player_Temp->Deck[CardLoop]->count++;
		}

		//Get Deck of Hosting Player
		if (R->PlayerMatrix[i]->PlayerID == R->PMVPlayerID)
		{
			MISD(std::to_string(R->PlayerMatrix[i]->Deck.size()));
			for (int j = 0; j < R->PlayerMatrix[i]->Deck.size(); j++)
			{
				Found = false;
				for (CardLoop = 0; CardLoop < Player_Temp->Deck.size(); CardLoop++)
					if (Player_Temp->Deck[CardLoop]->CardID == R->PlayerMatrix[i]->Deck[j]->CardID)
					{
						Found = true;
						break;
					}

				if (Found == false)
				{
					//MISD("ADD   :" + std::to_string(R->ActionMatrix[j]->Card));
					Card_Temp = new Card;
					Card_Temp->CardID = R->PlayerMatrix[i]->Deck[j]->CardID;
					Card_Temp->Charges = R->PlayerMatrix[i]->Deck[j]->Charges;
					Card_Temp->Upgrade = R->PlayerMatrix[i]->Deck[j]->Upgrade;
					Card_Temp->count = 0;
					Player_Temp->Deck.push_back(Card_Temp);
				}

			}

		}

		Players.push_back(Player_Temp);
	}

	MISD("#2");
	for (unsigned int i = 0; i < ActionSums.size(); i++)
	{
		ActionSums[i]->iCount = 0;
		ActionSums[i]->wcBox->setChecked(true);
	}

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type == 4001 ||
			R->ActionMatrix[i]->Type == 4003 ||
			R->ActionMatrix[i]->Type == 4004 ||
			R->ActionMatrix[i]->Type == 4005 ||
			R->ActionMatrix[i]->Type == 4008 ||
			R->ActionMatrix[i]->Type == 4016 ||
			R->ActionMatrix[i]->Type == 4017 ||
			R->ActionMatrix[i]->Type == 4018 ||
			R->ActionMatrix[i]->Type == 4021 ||
			R->ActionMatrix[i]->Type == 4022 ||
			R->ActionMatrix[i]->Type == 4023 ||
			R->ActionMatrix[i]->Type == 4024 ||
			R->ActionMatrix[i]->Type == 4025 ||
			R->ActionMatrix[i]->Type == 4026 ||
			R->ActionMatrix[i]->Type == 4032 ||
			R->ActionMatrix[i]->Type == 4045 
			) continue;

		Action_Temp = new ActionWeb();
		Action_Temp->Time = R->ActionMatrix[i]->Time;
		Action_Temp->sActionName = R->SwitchType(R->ActionMatrix[i]->Type);
		Action_Temp->sPlayerName = GetPlayerName(R->ActionMatrix[i]->PlayerID);
		
		switch (R->ActionMatrix[i]->Type)
		{
		case 4002:
			//Action_Temp->WImage = Pfeil / Türe
			break;
		case 4006: //GOLD	
			//Action_Temp->WImage GOLD Truhe
			Action_Temp->Info = R->ActionMatrix[i]->AdditionalInfo + " Gold";
			break;
		case 4007: //Objective OK 
			//Action_Temp->WImage HAKEN
			Action_Temp->Info = "ID: " + R->ActionMatrix[i]->AdditionalInfo;
			break;
		case 4009: //summon unit
		case 4010: //cast spell
		case 4011: //cast line spell
		case 4012: //cast building
			//Action_Temp->WImage Card
			Action_Temp->Info = Bro->J_GetSMJCard(R->ActionMatrix[i]->Card)->cardName;
			break;
		case 4013: //move unit
			//Action_Temp->WImage = Pfeil ? Way Point
			break;
		case 4014: //use unit ability
		    //Action_Temp->WImage = ???
			Action_Temp->Info = "ID: " + R->ActionMatrix[i]->AdditionalInfo;
			break;
		case 4015: //attack
			//Action_Temp->WImage = Schwert
			break;
		case 4019: //stop unit
			//Action_Temp->WImage = Hand
			break;
		case 4020: //hold unit position
			//Action_Temp->WImage = Schild
			break;
		case 4027: // PING (Meet / Help / ...)
		    //Action_Temp->WImage = Ping
			break;
		case 4028: //toggle wall gate
				   //Action_Temp->WImage = Gate
			break;
		case 4029: //build wall
				   //Action_Temp->WImage = WALL
			break;
		case 4030: //create mana
				   //Action_Temp->WImage = WELL
			break;
		case 4031: //create orb
				   //Action_Temp->WImage = Orb Coloro
			switch (atoi(R->ActionMatrix[i]->AdditionalInfo.substr(0, R->ActionMatrix[i]->AdditionalInfo.find(";")).c_str()))
			{
			case 1: Action_Temp->Info = "Shadow"; break;
			case 2: Action_Temp->Info = "Nature"; break;
			case 3: Action_Temp->Info = "Frost"; break;
			case 4: Action_Temp->Info = "SHadow"; break;
			}
			break;
		case 4033: //Unit move on Wall
				   //Action_Temp->WImage = Pfeil auf Wall
			break;
		case 4034: //Switch Abbility (Stone Tempest)
				   //Action_Temp->WImage = ???
			Action_Temp->Info = "ID: " + R->ActionMatrix[i]->AdditionalInfo;
			break;
		case 4035: //Trigger Reparier
				   //Action_Temp->WImage = Hammer
			break;
		case 4036: //Move unit in decomposer // TESTEN ander key wenn man die abbiliti nutzt?
				   //Action_Temp->WImage = decomposer abbility
			break;
		case 4037: //Place Nexus Exit (oder generell Bulding?) // TESTEN T4 Schatten			
				   //Action_Temp->WImage = NexusAbbylity 1
			break;
		case 4038: //Use Tunnel
				   //Action_Temp->WImage = Move Tunell icon
			break;
		case 4039: // Switch Tunnel
				   //Action_Temp->WImage = Switch icon
			break;
		case 4040: // Switch Nexusportal Back
				   //Action_Temp->WImage = NexusAbbylity 2
			break;

		case 4041: //Killed own Unit
				   //Action_Temp->WImage = toten kopf
			break;
		case 4042: // Placing Altar Of Chaos Totem
				   //Action_Temp->WImage = Chaos Icon
			break;
		case 4043: // go to Gold but not able to collect
				   //Action_Temp->WImage = Gold mit X
			break;
		case 4044: // TW Unit Switch
				   //Action_Temp->WImage = TW ICON
			break;
		}

		Actions.push_back(Action_Temp);

		ActionSums[R->ActionMatrix[i]->Type - 4000]->iCount++;
	}
	

	Head->newData = true;
	Deck->newData = true;
	Acti->newData = true;

	MISE;
	return true;
}

std::string WEB_Analyser::GetPlayerName(unsigned long inPlayer)
{
	for (unsigned int i = 0; i < Players.size(); i++)if (Players[i]->PlayerID == inPlayer)return Players[i]->Name;
	return "pl_Enemy1";
}
