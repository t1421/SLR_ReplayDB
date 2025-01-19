#define DF_Debug

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
#include <Wt/WStandardItemModel.h>


class NumericItem : public Wt::WStandardItem {
public:
	virtual std::unique_ptr<Wt::WStandardItem> clone() const override {
		return std::make_unique<NumericItem>();
	}

	virtual void setData(const Wt::cpp17::any &data, Wt::ItemDataRole role = Wt::ItemDataRole::User) override {
		Wt::cpp17::any dt;

		if (role == Wt::ItemDataRole::Edit) {
			std::string s = Wt::asString(data).toUTF8();
			char *endptr;
			double d = strtod(s.c_str(), &endptr);
			if (*endptr == 0)
				dt = Wt::cpp17::any(d);
			else
				dt = data;
		}

		Wt::WStandardItem::setData(data, role);
	}
};




#define SCard_Size_X 92
#define SCard_Size_Y 127
#define BOT4_IMG_SIZE 10

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
	
	
	//Soul
	EventBuildings102.push_back(std::make_pair(4, 1456));
	EventBuildings102.push_back(std::make_pair(4, 1457));
	//Fountain
	EventBuildings102.push_back(std::make_pair(5, 1455));
	EventBuildings102.push_back(std::make_pair(5, 1454));
	//Nihil
	EventBuildings102.push_back(std::make_pair(6, 1459));
	EventBuildings102.push_back(std::make_pair(6, 1461));
	//Flesh
	EventBuildings102.push_back(std::make_pair(7, 1462));
	EventBuildings102.push_back(std::make_pair(7, 1463));
	//Garden
	EventBuildings102.push_back(std::make_pair(8, 1458));
	EventBuildings102.push_back(std::make_pair(8, 1460));
	//Wheels
	EventBuildings102.push_back(std::make_pair(9,  1451)); //1
	EventBuildings102.push_back(std::make_pair(10, 1452)); //2
	EventBuildings102.push_back(std::make_pair(11, 1453)); //3
	//MO
	EventBuildings102.push_back(std::make_pair(12, 1450));
	//Disrupt
	EventBuildings102.push_back(std::make_pair(13, 1471));
	EventBuildings102.push_back(std::make_pair(13, 1470));
	EventBuildings102.push_back(std::make_pair(13, 1472));
	//Keep
	EventBuildings102.push_back(std::make_pair(14, 1473));
	EventBuildings102.push_back(std::make_pair(14, 1475));
	EventBuildings102.push_back(std::make_pair(14, 1474));
	EventBuildings102.push_back(std::make_pair(14, 1488));
	//Infernal
	EventBuildings102.push_back(std::make_pair(15, 1467));
	EventBuildings102.push_back(std::make_pair(15, 1468));
	EventBuildings102.push_back(std::make_pair(15, 1469));
	EventBuildings102.push_back(std::make_pair(15, 1487));
	//Mask
	EventBuildings102.push_back(std::make_pair(16, 1464));
	EventBuildings102.push_back(std::make_pair(16, 1466));
	EventBuildings102.push_back(std::make_pair(16, 1465));
	EventBuildings102.push_back(std::make_pair(16, 1486));
	
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
				&& R->ActionMatrix[j]->Type != 4044 //TW SWITCH
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
		case 4044: // TW Unit Switch
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
		//case 4044: // TW Unit Switch
		//		   //Action_Temp->WImage = TW ICON
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

void  WEB_Analyser::AddIMG(Wt::WTableCell* wtCell, bool bValue)
{
	wtCell->setHeight(BOT4_IMG_SIZE);
	wtCell->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage("./resources/" + std::to_string(bValue) + ".png"))));
	//widget(0))->setImageLink("./resources/1.png");
	wtCell->widget(0)->setHeight(BOT4_IMG_SIZE);
	wtCell->widget(0)->setWidth(BOT4_IMG_SIZE);
	wtCell->widget(0)->resize(BOT4_IMG_SIZE, BOT4_IMG_SIZE);
	wtCell->widget(0)->setMaximumSize(BOT4_IMG_SIZE, BOT4_IMG_SIZE);

	wtCell->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
}

void  WEB_Analyser::AddCardIMG(Wt::WTableCell* wtCell, unsigned short CardID, unsigned int Size)
{
	std::string Path = Bro->J_GetImgOnly(CardID);

	wtCell->setHeight(Size);
	wtCell->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage(Path))));
	wtCell->widget(0)->setHeight(Size);
	wtCell->widget(0)->setWidth(Size);
	wtCell->widget(0)->resize(Size, Size);
	wtCell->widget(0)->setMaximumSize(Size, Size);

	wtCell->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
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
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	if (R->MapName != sMapName)return "Wrong Map";
	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (!isEEEwin() )return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

	iTimes[0] = getPlaytime();
	iTimes[2] = usedPower();
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE2(unsigned long iTimes[RankRowStamps])
{

	MISS;
	if (!R->OK)return "No Replay";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	if (R->MapName != "sss2.map")return "Wrong Map";
	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (!isEEEwin())return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

	iTimes[0] = getPlaytime();	
	iTimes[2] = usedPower();
	iTimes[1] = iTimes[0] + iTimes[2] / 10;
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE3(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	if (R->MapName != "sss3.map")return "Wrong Map";
	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (!isEEEwin())return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

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

std::string WEB_Analyser::Kalk_EEE5(unsigned long iTimes[RankRowStamps], Wt::Chart::WCartesianChart *chart)
{
	MISS;
	chart->setHidden(true);
	if (!R->OK)return "No Replay";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	if (R->MapName != "sss5.map")return "Wrong Map";
	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (!isEEEwin())return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

	std::vector <std::pair<int, int>> vpChartData;

	for (auto A : R->ActionMatrix)
		if (A->Type == 4045 && entry(A->AdditionalInfo, 0) == "2")
		{
			vpChartData.push_back(std::make_pair(int(A->Time / 10), STRtoNUM(entry(A->AdditionalInfo, 1))));
			if (STRtoNUM(entry(A->AdditionalInfo, 1)) > iTimes[0]) iTimes[0] = STRtoNUM(entry(A->AdditionalInfo, 1));
		}
	
	iTimes[2] = usedPower();
	
	chart->setHidden(false);
	std::shared_ptr<Wt::WStandardItemModel> model = std::make_shared<Wt::WStandardItemModel>(vpChartData.size(), 2);
	std::unique_ptr<NumericItem> prototype = std::make_unique<NumericItem>();
	model->setHeaderData(0, Wt::WString("Time"));
	model->setHeaderData(1, Wt::WString("Units"));

	for (unsigned int iRow = 0; iRow < vpChartData.size(); iRow++)
	{
		model->setData(iRow, 0, vpChartData[iRow].first);
		model->setData(iRow, 1, vpChartData[iRow].second);
	}

	chart->setModel(model);        // set the model
	chart->setXSeriesColumn(0);    // set the column that holds the X data
	chart->setLegendEnabled(true); // enable the legend
	chart->setZoomEnabled(true);
	chart->setPanEnabled(true);
	chart->setCrosshairEnabled(true);
	chart->setAutoLayoutEnabled(true);

	chart->setBackground(Wt::WColor(200, 200, 200));
	
	chart->setType(Wt::Chart::ChartType::Scatter);   // set type to ScatterPlot

	//std::unique_ptr<Wt::Chart::WDataSeries> s = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Curve);
	std::unique_ptr<Wt::Chart::WDataSeries> s = std::make_unique<Wt::Chart::WDataSeries>(1, Wt::Chart::SeriesType::Bar);
	s->setShadow(Wt::WShadow(3, 3, Wt::WColor(0, 0, 0, 127), 3));
	chart->addSeries(std::move(s));

	chart->resize(800, 300); // WPaintedWidget must be given explicit size
	//chart->setMargin(10, Wt::Side::Top | Wt::Side::Bottom);
	//chart->setMargin(Wt::WLength::Auto, Wt::Side::Left | Wt::Side::Right);

	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_EEE7(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	if (R->MapName != "sss7.map")return "Wrong Map";
	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (!isEEEwin())return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

	for (auto A : R->ActionMatrix)
		if (A->Type == 4045 && entry(A->AdditionalInfo, 0) == "4")
		{
			if (A->AdditionalInfo == "4;MIS_WIN;1;") break;

			if (entry(A->AdditionalInfo, 1)[0] == 'M' && entry(A->AdditionalInfo, 1)[1] == 'Y')
				iTimes[0] = STRtoNUM(entry(A->AdditionalInfo, 1));
			if (entry(A->AdditionalInfo, 1)[0] == 'O' && entry(A->AdditionalInfo, 1)[1] == 'P')
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

std::string WEB_Analyser::Kalk_Event100(unsigned long iTimes[RankRowStamps])
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "restoringlyr_4.map")return "Wrong Map";
	if (R->DifficultyID != 2)return "Wrong Difficulty";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	bool bWin = false;
	for (auto A : R->ActionMatrix)if (A->Type == 4045 && A->AdditionalInfo == "4;Goal5;1;")bWin = true;
	if (!bWin)return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";

	iTimes[0] = getPlaytime();
	iTimes[1] = usedPower();
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_Event101()
{
	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "20002_pve_02p_into_the_jungle.map" && R->MapName != "20001_pve_02p_unexpected_visitors.map")return "Wrong Map";
	if (R->DifficultyID != 2 && R->DifficultyID != 3)return "Wrong Difficulty";
	if (R->FileVersion != 268)return "Wrong Client";
	if (R->GameVersion != 400049)return "Wrong GameVersion";
	bool bWin = false;
	for (auto A : R->ActionMatrix)if (A->Type == 4007 && (  A->AdditionalInfo == "1025" && R->MapName == "20002_pve_02p_into_the_jungle.map"
		                                                 || A->AdditionalInfo == "1009" && R->MapName == "20001_pve_02p_unexpected_visitors.map"))bWin = true;
	if (!bWin)return "Was not a win";
	if (R->TestStriker())return "please do not abuse your power";


	
	MISE;
	return "";
}

std::string WEB_Analyser::Kalk_Event102(unsigned long iTimes[RankRowStamps])
{
	//0 = Time
	//1 = Points ingame
	//2 = Check 1
	//3 = Check 2 
	//4 - 16 Buildings

	MISS;
	if (!R->OK)return "No Replay";
	if (R->MapName != "battle_of_tactics_8.map")return "Wrong Map";
	if (R->DifficultyID != 2)return "Wrong Difficulty";
	//if (R->FileVersion != 269)return "Wrong Client";
	//if (R->GameVersion != 400050)return "Wrong GameVersion";
	if (!isEEEwin())return "Was not a win";
	//if (R->TestStriker())return "please do not abuse your power";

	bool go =  false;

	iTimes[0] = getPlaytime();

	for (auto A : R->ActionMatrix)
	{
		if (A->Type == 4045 && entry(A->AdditionalInfo, 1).substr(0, 9) == "mc_Points")
			iTimes[1] = atoi(entry(A->AdditionalInfo, 1).substr(9).c_str());

		if (A->Type == 4045 && A->AdditionalInfo == "4;12103_01_01_DestroyEnemyCamp;1;")
			iTimes[2] = A->Time;

		if (A->Type == 4045 && A->AdditionalInfo == "4;12103_03_02_DefendYourMonuments;0;")
			iTimes[3] = A->Time;

		//GO Button
		if (A->Type == 4014 && A->Time < 600 && A->AdditionalInfo == "2020010;1485")go = true;

		if (A->Type == 4014 && A->Time < 600 && go == false && entry(A->AdditionalInfo, 0) == "2020010")
			for (auto E : EventBuildings102)if (E.second == atoi(entry(A->AdditionalInfo, 1).c_str()))iTimes[E.first]++;		
	}

	unsigned int CheckSum = 0;
	CheckSum += iTimes[4] * 15;
	CheckSum += iTimes[5] * 15;
	if (iTimes[6] == 1)CheckSum += 25;
	if (iTimes[6] == 2)CheckSum += 75;
	if (iTimes[7] == 1)CheckSum += 10;
	if (iTimes[7] == 2)CheckSum += 30;
	if (iTimes[8] == 1)CheckSum += 15;
	if (iTimes[8] == 2)CheckSum += 25;
	CheckSum += iTimes[9]  * 15;
	CheckSum += iTimes[10] * 15;
	CheckSum += iTimes[11] * 25;
	CheckSum += iTimes[12] * 20;
	CheckSum += iTimes[13] * 5;
	CheckSum += iTimes[14] * 10;
	CheckSum += iTimes[15] * 10;
	CheckSum += iTimes[16] * 10;

	//if (CheckSum != iTimes[1])return "Point missmatch, Calk:" + std::to_string(CheckSum) + " Ingame: " + std::to_string(iTimes[1]);


	MISE;
	return "";
}

void WEB_Analyser::AddPlayers101()
{
	MISS;
	bool skip;
	SMJCard *cTemp;
	for (auto P : Players)
	{
		if (P->Type != 1)continue;

		skip = false;
		for (auto A : R->ActionMatrix)if (A->Type == 4002 && A->PlayerID == P->PlayerID)skip = true;
		if (skip)continue;

		unsigned long iTimes[RankRowStamps] = { 0 };
		bool bUVCheck = true;
		bool bIJCheck = true;
		for (auto C : P->Deck)
		{
			if (C->count > 0)
			{

				cTemp = Bro->J_GetSMJCard(C->CardID);
				if(cTemp->color == 0 //FIre
					//|| cTemp->color == 1 // Shadow
					|| cTemp->color == 2 //Nature
					|| cTemp->color == 3 //Frost
					|| cTemp->color == 4 //Bandid
					|| cTemp->color == 5 //SK
					|| cTemp->color == 6 //TW
					|| cTemp->color == 7 //LS
					//|| cTemp->color == 8 //Amii
					|| cTemp->color == 9 //FF
					|| cTemp->color == -1 //Neutal
					)bUVCheck = false;

				if (cTemp->color == 0 //FIre
					|| cTemp->color == 1 // Shadow
					//|| cTemp->color == 2 //Nature
					|| cTemp->color == 3 //Frost
					|| cTemp->color == 4 //Bandid
					|| cTemp->color == 5 //SK
					|| cTemp->color == 6 //TW
					|| cTemp->color == 7 //LS
					//|| cTemp->color == 8 //Amii
					|| cTemp->color == 9 //FF
					|| cTemp->color == -1 //Neutal
					)bIJCheck = false;
			}
		}

		if (R->MapName == "20001_pve_02p_unexpected_visitors.map" && R->DifficultyID >= 2)iTimes[0] = 1;		
		if (R->MapName == "20001_pve_02p_unexpected_visitors.map" && R->DifficultyID >= 3)iTimes[1] = 1;
		if (R->MapName == "20001_pve_02p_unexpected_visitors.map" && bUVCheck)iTimes[2] = 1;

		if (R->MapName == "20002_pve_02p_into_the_jungle.map" && R->DifficultyID >= 2)iTimes[3] = 1;
		if (R->MapName == "20002_pve_02p_into_the_jungle.map" && R->DifficultyID >= 3)iTimes[4] = 1;
		if (R->MapName == "20002_pve_02p_into_the_jungle.map" && bIJCheck)iTimes[5] = 1;

		Bro->AddPlayer(101, P->Name, P->PlayerID, iTimes);		
	}
	MISE;
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