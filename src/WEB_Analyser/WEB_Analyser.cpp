#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Replay.h" 
#include "..\..\incl\Utility.h" 

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Head.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Deck.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Acti.h"

#include <Wt/WImage.h>
#include <Wt/WColor.h>
#include <Wt/WCssDecorationStyle.h>
#include <algorithm>

#define SCard_Size_X 92
#define SCard_Size_Y 127
#define BOT4_IMG_SIZE 50

bool comparePlayerID(const unsigned long long a, const unsigned long long b)
{
	return a < b;
}

broker *(WEB_Analyser::Bro) = NULL;

WEB_Analyser::WEB_Analyser(): R(new Replay()), WA_Debug(false)
{
	MISS;
	
	ActionSum* ActionSum_Tmp;
	for (unsigned int i = 4000; i <= 4045; i++)
	{
		ActionSum_Tmp = new ActionSum();
		ActionSum_Tmp->ActionID = i;
		ActionSum_Tmp->sActionName = R->SwitchType(i);
		ActionSum_Tmp->iCount = 0;
		ActionSum_Tmp->wcBox = new Wt::WCheckBox();
		ActionSum_Tmp->wcBox->setChecked(true);
		ActionSums.push_back(ActionSum_Tmp);
	}
	
	MISD("#1");

	Head = new WEB_Analyser_Head(this);
	Deck = new WEB_Analyser_Deck(this);
	Acti = new WEB_Analyser_Acti(this);

	MISE;
}

void WEB_Analyser::ReNewTaps()
{
	MISS;

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
		ActionSums[i]->wcBox = new Wt::WCheckBox();
		ActionSums[i]->wcBox->setChecked(true);
	}

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if ((R->ActionMatrix[i]->Type == 4001 ||
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
			R->ActionMatrix[i]->Type == 4045) && WA_Debug==false
			) continue;

		Action_Temp = new ActionWeb();
		Action_Temp->Time = R->ActionMatrix[i]->Time;
		Action_Temp->sActionName = R->SwitchType(R->ActionMatrix[i]->Type);
		Action_Temp->sPlayerName = GetPlayerName(R->ActionMatrix[i]->PlayerID);
		
		switch (R->ActionMatrix[i]->Type)
		{
		case 4002:
			//Action_Temp->WImage = Pfeil / T�re
			break;
		case 4004: //12 Player Map Special	(Sync von Maps 1 bis 3 ? )		// Anzahl von Gegnern auf der Map?					
			Action_Temp->Info = R->ActionMatrix[i]->AdditionalInfo;
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
			if (WA_Debug) Action_Temp->Info = R->ActionMatrix[i]->AdditionalInfo;
			else switch (atoi(R->ActionMatrix[i]->AdditionalInfo.substr(0, R->ActionMatrix[i]->AdditionalInfo.find(";")).c_str()))
			{
			case 1: Action_Temp->Info = "Shadow"; break;
			case 2: Action_Temp->Info = "Nature"; break;
			case 3: Action_Temp->Info = "Frost"; break;
			case 4: Action_Temp->Info = "Fire"; break;
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
		case 4045: // SLR Data
			Action_Temp->Info = "figures/entities: " + R->ActionMatrix[i]->AdditionalInfo;
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

unsigned long long WEB_Analyser::getPMVPlayerID()
{
	if (!R->OK)return 0;
	return R->PMVPlayerID;
}

unsigned long long WEB_Analyser::getPlaytime()
{
	if (!R->OK)return 0;
	return R->Playtime;
}


std::string WEB_Analyser::Kalk_BOT4(Wt::WTable *wtTabelle, Wt::WTable *wtInfos, unsigned long iTimes[RankRowStamps])
{
	MISS;

	unsigned iRow = 0;
	unsigned iCol = 0;
	std::string sColorError = "";
	std::string sCountError = "";
	std::string sAffinError = "";
	std::string sFlyerError = "";
	bool dublette = false;

	unsigned int iNumberOfCardsPlayed = 0;
	unsigned int iNumberOfTransforms = 0;
	unsigned int iActionsPlayer = 0;
	std::vector<std::pair<std::string, unsigned long>> Stamps;

	if (!R->OK)return "No Replay";

	

	
	for (unsigned int i = 0; i < Players.size(); i++)
	{
		
		if(Players[i]->PlayerID == getPMVPlayerID() && Players[i]->Type == 1)
		for (unsigned int j = 0; j < Players[i]->Deck.size(); j++)
		{
			
			if (Players[i]->Deck[j]->count == 0) continue;
			MISD("###" + std::to_string(Players[i]->Deck[j]->CardID));
			MISD("1#" + std::to_string(Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->color));
			MISD("2#" + std::to_string(Players[i]->Deck[j]->count));

			if (Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->color =! 6) 
				sColorError += Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->cardName + ",";
			if (Players[i]->Deck[j]->count > 1) 
				sCountError += Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->cardName + ",";

			if (   Players[i]->Deck[j]->CardID == 1486 //Deathglider [B]
				|| Players[i]->Deck[j]->CardID == 1224 //Deathglider [G]
				|| Players[i]->Deck[j]->CardID == 1487 //Skycatcher [B]
				|| Players[i]->Deck[j]->CardID == 1226 //Skycatcher [G]				
				)
				sFlyerError += Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->cardName + ",";

			for (unsigned int k = j + 1; k < Players[i]->Deck.size(); k++)
			{
				if (Players[i]->Deck[k]->count == 0) continue;
				if (Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->cardNameSimple == Bro->J_GetSMJCard(Players[i]->Deck[k]->CardID)->cardNameSimple)
					sAffinError += Bro->J_GetSMJCard(Players[i]->Deck[j]->CardID)->cardName + ",";
			}

			iNumberOfCardsPlayed += Players[i]->Deck[j]->count;
			
		}
	}

	std::vector<std::pair<std::string, unsigned long>> Orb;
	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type != 4031) continue;
		MISD(R->ActionMatrix[i]->AdditionalInfo);
		if (entry(R->ActionMatrix[i]->AdditionalInfo, 2) == "0") continue; // STart Orbs
		dublette = false;
		for (unsigned int j = 0; j < Orb.size(); j++)
			if (entry(R->ActionMatrix[i]->AdditionalInfo, 2) == Orb[j].first)
			dublette = true;

		if (!dublette)Orb.push_back(std::make_pair(entry(R->ActionMatrix[i]->AdditionalInfo, 2), R->ActionMatrix[i]->Time));		
	}

	// Info Collection	
	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type == 4044)iNumberOfTransforms++;
		if (R->ActionMatrix[i]->Type == 4004)Stamps.push_back(std::make_pair(R->ActionMatrix[i]->AdditionalInfo, R->ActionMatrix[i]->Time));
		if (R->ActionMatrix[i]->PlayerID == getPMVPlayerID())iActionsPlayer++;
	}
	
	for (unsigned int i = 0; i < Stamps.size(); i++)
	{
		if (Stamps[i].first == "0")Stamps[i].second = 0;
		if (Stamps[i].first == "40")Stamps[i].second = R->Playtime;
	}

	//FIll Infos
	iCol = 0;
	iRow = 0;
	wtInfos->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>Cards Played:</h4>"))));
	wtInfos->elementAt(iRow++, iCol--)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(iNumberOfCardsPlayed)))));
	
	wtInfos->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>Transformations:</h4>"))));
	wtInfos->elementAt(iRow++, iCol--)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(iNumberOfTransforms)))));
	
	wtInfos->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>Actions:</h4>"))));
	wtInfos->elementAt(iRow++, iCol--)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(iActionsPlayer)))));

	wtInfos->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));

	iTimes[0] = getPlaytime();
	for (unsigned int i = 1; i < Stamps.size(); i++)
	{
		if(i<RankRowStamps) iTimes[i] = Stamps[i].second - Stamps[i - 1].second;
		wtInfos->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>Stamp " + std::to_string(i) + ":</h4>"))));
		wtInfos->elementAt(iRow++, iCol--)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(Stamps[i].second - Stamps[i-1].second)))));
	}	

	//Fill Table
	iCol = 0;
	iRow = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Gameversion:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(R->GameVersion)))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), R->GameVersion == 400042);

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Map:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	//wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(R->MapName))));
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), R->MapName == "11441_pve_12p_passagetodarkness.map");

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Difficulty:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(R->DifficultyID)))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), R->DifficultyID == 2);
	
	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Only TW Cards:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sColorError))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), sColorError == "");

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Play Cards only once:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sCountError))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), sCountError == "");

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Only one affinity:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sAffinError))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), sAffinError == "");

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>No Flyers:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sFlyerError))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), sFlyerError == "");

	iCol = 0;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Win:</h3>"))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));
	wtTabelle->elementAt(iRow, iCol++)->setContentAlignment(Wt::AlignmentFlag::Middle);
	AddIMG(wtTabelle->elementAt(iRow++, iCol++), Orb.size() >= 4);
	

	wtTabelle->columnAt(0)->setWidth(250);
	wtTabelle->columnAt(1)->setWidth(200);
	wtTabelle->columnAt(2)->setWidth(BOT4_IMG_SIZE);

	for (int i = 0; i < iRow; i++)
	{
		if (dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, 2)->widget(0))->imageLink() == Wt::WLink("./resources/0.png"))
		{		
			MISEA("Not all green");
			return "ERROR";
		}		
		
	}
	MISE;
	return "";
}

void  WEB_Analyser::AddIMG(Wt::WTableCell *wtCell, bool bValue)
{
	wtCell->setHeight(BOT4_IMG_SIZE);
	wtCell->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage("./resources/" + std::to_string(bValue) + ".png"))));
	//widget(0))->setImageLink("./resources/1.png");
	wtCell->widget(0)->setHeight(BOT4_IMG_SIZE);
	wtCell->widget(0)->setWidth(BOT4_IMG_SIZE);
	wtCell->widget(0)->resize(BOT4_IMG_SIZE, BOT4_IMG_SIZE);
	wtCell->widget(0)->setMaximumSize(BOT4_IMG_SIZE, BOT4_IMG_SIZE);
}




std::string WEB_Analyser::GetTeamID()
{
	std::string sReturn;
	std::vector <unsigned long long> TeamPlayer;
	for (unsigned int i = 0; i < Players.size(); i++)
		if (Players[i]->Type == 1)TeamPlayer.push_back(Players[i]->PlayerID);

	for (unsigned int i = TeamPlayer.size(); i <= 4; i++)TeamPlayer.push_back(0);

	std::sort(TeamPlayer.begin(), TeamPlayer.end(), comparePlayerID);

	for (unsigned int i = 0; i < TeamPlayer.size(); i++)
		sReturn += std::to_string(TeamPlayer[i]) + "#";

	return sReturn;
}

unsigned long WEB_Analyser::getReplayHash()
{
	return R->Unknow3 * 1000 + R->Unknow4;
}