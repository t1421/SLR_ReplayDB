//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Replay.h" 
#include "..\..\incl\Utility.h" 

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#if defined BrokerWeb
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Head.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Deck.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser_Acti.h"
#endif

#if defined BrokerTome
#include "..\..\incl\WEB_Tome\Tome_Game.h"
#include "..\..\incl\WEB\WEB_Utility.h"
#endif

#if defined BrokerLotto
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#endif

#include <Wt/WImage.h>
#include <Wt/WCheckBox.h>
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

WEB_Analyser::WEB_Analyser(): R(new Replay()), WA_Debug(false), WA_Admin(false)
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
#if defined BrokerWeb
	Head = new WEB_Analyser_Head(this);
	Deck = new WEB_Analyser_Deck(this);
	Acti = new WEB_Analyser_Acti(this);
#endif
	MISE;
}

void WEB_Analyser::ReNewTaps()
{
	MISS;
#if defined BrokerWeb
	Head = new WEB_Analyser_Head(this);
	Deck = new WEB_Analyser_Deck(this);
	Acti = new WEB_Analyser_Acti(this);
#endif
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
			//Action_Temp->WImage = Pfeil / Türe
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
			Action_Temp->Info = R->ActionMatrix[i]->AdditionalInfo;
			break;
		}

		Actions.push_back(Action_Temp);

		ActionSums[R->ActionMatrix[i]->Type - 4000]->iCount++;
	}
	
#if defined BrokerWeb
	Head->newData = true;
	Deck->newData = true;
	Acti->newData = true;
#endif

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

std::string WEB_Analyser::getMapName()
{
	if (!R->OK)return "";
	return R->MapName;
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

bool WEB_Analyser::SaveReplay(std::string sFile)
{
	return R->SavePMV(sFile);
}

#if defined BrokerTome

int WEB_Analyser::TomeAnalyser(Wt::WTable *wtReplayResultCard, unsigned int iGameID)
{
	MISS;
	unsigned int iRow;
	unsigned int iCol = 0;
	bool CardError = false;
	int PlayerError = 0;
	std::string sPlayer = "";
	bool CardOK;

	for (unsigned int i = 0; i < Players.size(); i++)
	{
		if (Players[i]->Type != 1)continue;
		iRow = 0;
		wtReplayResultCard->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Players[i]->Name))));
		//for (unsigned int j = 0; j < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); j++)
		for each (Tome_Player* TP in Bro->vTomeGames[iGameID]->vPlayer)
		{
			if (TP->sPlayerName == Players[i]->Name)
			{
				for each (Card* RD in Players[i]->Deck)
				{
					if (RD->count == 0)continue;
					wtReplayResultCard->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
						DrawImg(Bro->J_GetImage(
							RD->CardID,
							3,
							4,
							1,
							false),
							SCard_Size_X, SCard_Size_Y
						))));

					CardOK = false;
					for each(Tome_Booster* TP_TB in TP->vBoosters)
						for each(SMJCard* TP_TB_TC in TP_TB->vCards)
						{
							if (TP_TB_TC->cardId == RD->CardID)
							{
								CardOK = true;
								break;
							}
						}
					if (CardOK)wtReplayResultCard->elementAt(iRow, iCol + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3 style='color:Green;'>OK</h3>"))));
					else wtReplayResultCard->elementAt(iRow, iCol + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3 style='color:Tomato;'>Error</h3>"))));
					if (CardOK == false)CardError = true;

					wtReplayResultCard->elementAt(iRow++, iCol + 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

					if (sPlayer != Players[i]->Name)
					{
						sPlayer = Players[i]->Name;
						PlayerError++;
					}
				}
			}
		}

		wtReplayResultCard->columnAt(iCol)->setWidth(SCard_Size_X);
		wtReplayResultCard->columnAt(iCol + 1)->setWidth(25);
		iCol += 2;

	}

	
	if (PlayerError<2)
	{
		MISEA("Player");
		return 1;
	}
	if (CardError)
	{
		MISEA("Card");
		return 2;
	}

	MISE;
	return 0;
}

#endif


// No Orb Switching?
std::string WEB_Analyser::Kalk_EEE0(unsigned long iTimes[RankRowStamps])
{
	MISS;


	MISE;
	return "XXX";
}

std::string WEB_Analyser::Kalk_EEE_Def(unsigned long iTimes[RankRowStamps],std::string sMapName)
{
	
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != sMapName)return "Wrong Map";
	if (!isEEEwin() )return "Was not a win";

	iTimes[0] = getPlaytime();
	iTimes[2] = usedPower();
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE3(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "sss3.map")return "Wrong Map";
	if (!isEEEwin())return "Was not a win";

	for (auto A : R->ActionMatrix)
	{
		if (A->Type == 4045 && A->AdditionalInfo == "4;MIS_WIN;1;")break;
		if (A->Type == 4045 && entry(A->AdditionalInfo, 0) == "4")
			if (entry(A->AdditionalInfo, 1)[0] == 'G')iTimes[0] = STRtoNUM(entry(A->AdditionalInfo, 1));
	}

	iTimes[2] = usedPower();
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE5(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "sss5.map")return "Wrong Map";
	if (!isEEEwin())return "Was not a win";

	for (auto A : R->ActionMatrix)
		if (A->Type == 4045 && entry(A->AdditionalInfo, 0) == "2")
			if(STRtoNUM(entry(A->AdditionalInfo, 1)) > iTimes[0]) iTimes[0] = STRtoNUM(entry(A->AdditionalInfo, 1));

	iTimes[2] = usedPower();
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE7(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "sss7.map")return "Wrong Map";
	if (!isEEEwin())return "Was not a win";

	for (auto A : R->ActionMatrix)
		if (A->Type == 4045 && entry(A->AdditionalInfo, 0) == "4")
		{
			if (entry(A->AdditionalInfo, 1)[0] == 'M')
				iTimes[0] = STRtoNUM(entry(A->AdditionalInfo, 1));
			if (entry(A->AdditionalInfo, 1)[0] == 'O')
				iTimes[1] = STRtoNUM(entry(A->AdditionalInfo, 1));
		}

	iTimes[2] = usedPower();

	MISE;
	return "";
}


bool WEB_Analyser::isEEEwin()
{
	for (auto A : R->ActionMatrix)if (A->Type == 4045 && A->AdditionalInfo == "4;MIS_WIN;1;")return true;
	return false;
}

unsigned long long WEB_Analyser::usedPower()
{
	MISS;

	unsigned long long ullReturn = 0;

	for (unsigned int i = 0; i < Players.size(); i++)
	{
		if (Players[i]->Type != 1)continue;
		//if (Players[i]->PlayerID != getPMVPlayerID())continue;

		for each (Card* C in Players[i]->Deck)
			ullReturn += Bro->J_GetSMJCard(C->CardID)->powerCost[C->Upgrade] * C->count;
	}

	MISE;
	return ullReturn;
}

std::string WEB_Analyser::Kalk_Event0(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "restoringlyr_4.map")return "Wrong Map";
	if (R->DifficultyID != 2)return "Wrong Difficulty";
	if (R->GameVersion != 400047)return "Wrong GameVersion";
	bool bWin = false;
	for (auto A : R->ActionMatrix)if (A->Type == 4045 && A->AdditionalInfo == "4;Goal5;1;")bWin = true;
	if (!bWin)return "Was not a win";

	iTimes[0] = getPlaytime();
	iTimes[1] = usedPower();
	MISE;
	return "";
}


#if defined BrokerLotto
Lotto_Player *WEB_Analyser::getLottoPlayer()
{
	MISS;
	
	if (!R->OK)
	{
		MISEA("No replay");
		return new Lotto_Player();
	}

	Lotto_Player *lpReturn = new Lotto_Player(
		std::to_string(R->PMVPlayerID),
		GetPlayerName(R->PMVPlayerID),
		std::to_string(getReplayHash()),
		R->MapID);

	for (unsigned int i = 0; i < Players.size(); i++)
	{
		if (Players[i]->Type != 1)continue;
		if (Players[i]->PlayerID != getPMVPlayerID())continue;
		
		for each (Card* C in Players[i]->Deck)
		{
			lpReturn->vSimpleDeck.push_back(Bro->J_GetSMJCard(C->CardID)->cardNameSimple);
			lpReturn->vPoints.push_back(0);
		}
	}

	std::sort(lpReturn->vSimpleDeck.begin(), lpReturn->vSimpleDeck.end());
	lpReturn->vSimpleDeck.erase(std::unique(lpReturn->vSimpleDeck.begin(), lpReturn->vSimpleDeck.end()), lpReturn->vSimpleDeck.end());
	/*
	MISD(lpReturn->sPlayerID);
	MISD(lpReturn->sPlayerName);
	MISD(lpReturn->sGameID);
	MISD(lpReturn->iMapID);
	MISD(lpReturn->vSimpleDeck.size());
	*/
	MISE;
	return lpReturn;
}
#endif