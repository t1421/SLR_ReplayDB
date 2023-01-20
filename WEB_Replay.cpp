//#define DF_Debug

#include "Broker.h"

#include "WEB_Utility.h"
#include "Replay.h" 
#include "LOAD.h" 
#include "Utility.h"

#include "WEB_Replay.h"

#include <Wt/WTable.h>

broker *(WEB_Replay::Bro) = NULL;

WEB_Replay::WEB_Replay() :R(new Replay()), BOT3Stuff(false){};

bool WEB_Replay::NewReplay(std::string sFile)
{
	R = new Replay();
	BOT3Stuff = false;
	return R->LoadPMV(sFile);
}

int WEB_Replay::CountActions() 
{ 
	return R->CountActions(); 
};

int WEB_Replay::CountActions(std::string sFilter)
{
	return R->CountActions(sFilter);
};

std::string WEB_Replay::BOT1()
{
	//MAP Check
	if (R->OK != true)return "Error in replay";
	if (R->MapName != "11105_PvE_01p_EncountersWithTwilight.map")return "Wrong Map";
	if (R->DifficultyID != 3)return "Wrong Difficulty";
	
	return "";
};

std::string WEB_Replay::BOT2(bool bMode,Wt:: WTable *wtTabelle)
{
	bool result = false;

	if (R->OK != true)return "Error in replay";

	if (bMode)
	{
		FillWebDeckAction();
		result = FillTableBOT2(WebDeckActions, wtTabelle);
	}
	else
	{
		FillWebDeckDeck();
		result = FillTableBOT2(WebDeckDeck, wtTabelle);
	}

	if (R->MapName != "11104_PvE_01p_BehindEnemyLines.map")return "Wrong Map";
	if (R->DifficultyID != 2)return "Wrong Difficulty";

	if (result == true)return "";
	else return "Something is wrong in your deck";
	
	return "";
}

std::string WEB_Replay::BOT3(Wt::WTable *wtTabelle, Wt::WContainerWidget *cMap, unsigned long &Time)
{
	if (R->OK != true)return "Error in replay";
	if (R->MapName != "11101_PvE_01p_TugOfWar.map")return "Wrong Map";
	BOT3WellsAndOrbUnit();
	Time = FillTableBOT3(wtTabelle);

	for (unsigned int i = 0; i < vMarker.size(); i++)
		cMap->addWidget(std::unique_ptr<Wt::WWidget>(std::move(vMarker[i]->IMG)));

	if (R->DifficultyID != 1)return "Wrong Difficulty";
	if (R->CountActions("4007") != 2)return "You have to save the first 2 Wagons";
	if (R->Playtime > 10000)return "You have to save the first 2 Wagons";
	if (R->GameVersion != 400039)return "Wrong Game Version";
	
	for (unsigned j = 0; j < vMarker.size(); j++) if (WSTRINGtoSTRING(vMarker[j]->Time->text()) == "XX:XX")return "You did not build all Orbs and/or Wells";
		
	return "";
}

std::string WEB_Replay::MapName()
{
	return R->MapName;
}

std::string WEB_Replay::Time()
{
	return sTime(R->Playtime);
}

unsigned long WEB_Replay::Playtime()
{
	return R->Playtime;
}

unsigned long long WEB_Replay::Player()
{
	return R->PMVPlayerID;
}

unsigned int WEB_Replay::Difficulty()
{
	return R->DifficultyID;
}

bool WEB_Replay::FillWebDeckAction()
{
	MISS;

	WebDeckActions.clear();

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		switch (R->ActionMatrix[i]->Type)
		{
		case 4009: //summon unit
			addCard(R->ActionMatrix[i]->Card, true, false, false, WebDeckActions);
			break;
		case 4010: //cast spell
		case 4011: //cast line spell
			addCard(R->ActionMatrix[i]->Card, false, true, false, WebDeckActions);
			break;
		case 4012: //cast building
			addCard(R->ActionMatrix[i]->Card, false, false, true, WebDeckActions);
			break;
		}
	}

	addColors(WebDeckActions);

	MISE;
	return true;
}

void WEB_Replay::addColors(std::vector <WebCard*>& WebDeck)
{
	MISS;
	for (unsigned int i = 0; i < WebDeck.size(); i++)
	{
		//MISD(to_string(WebDeck[i]->CardID));
		for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		{
			if (Bro->L->CsvAllCards[j]->CardID == WebDeck[i]->CardID)
			{
				WebDeck[i]->iFire = Bro->L->CsvAllCards[j]->iFire;
				WebDeck[i]->iFrost = Bro->L->CsvAllCards[j]->iFrost;
				WebDeck[i]->iShadow = Bro->L->CsvAllCards[j]->iShadow;
				WebDeck[i]->iNature = Bro->L->CsvAllCards[j]->iNature;
				WebDeck[i]->iNeutral = Bro->L->CsvAllCards[j]->iNeutral;
				break;
			}
		}

	}
	MISE;
}

void WEB_Replay::addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building, std::vector <WebCard*>& WebDeck)
{
	MISS;
	unsigned int uiFound = -1;

	

	for (unsigned int i = 0; i < WebDeck.size(); i++)if (uiCardID == WebDeck[i]->CardID)uiFound = i;

	if (uiFound != -1)WebDeck[uiFound]->playCount++;
	else
	{
		MISD(std::to_string(uiCardID));
		WebCard *Card_TEMP = new WebCard;
		Card_TEMP->CardID = uiCardID;
		Card_TEMP->bUnit = Unit;
		Card_TEMP->bSpell = Spell;
		Card_TEMP->bBuilding = Building;

		for (int i = 0; i < 3; i++)
		{
			Card_TEMP->IMG[i] = new Wt::WImage("./resources/Cards/" + std::to_string(uiCardID) + ".png");
			Card_TEMP->IMG[i]->setHeight(BOT2_IMG_SIZE);
			Card_TEMP->IMG[i]->setWidth(BOT2_IMG_SIZE);
			Card_TEMP->IMG[i]->resize(BOT2_IMG_SIZE, BOT2_IMG_SIZE);
			Card_TEMP->IMG[i]->setMaximumSize(BOT2_IMG_SIZE, BOT2_IMG_SIZE);
		}



		WebDeck.push_back(Card_TEMP);
	}
	MISE;
}

bool WEB_Replay::FillWebDeckDeck()
{
	MISS;

	WebDeckDeck.clear();

	for (unsigned int i = 0; i < R->PlayerMatrix.size(); i++)
	{
		//MISD("i:" + to_string(i))
		if (R->PlayerMatrix[i]->Deck.size() == 0) continue;
		for (unsigned int j = 0; j < R->PlayerMatrix[i]->Deck.size(); j++)
		{
			if (R->PlayerMatrix[i]->Deck[j]->CardID == 0)continue;
			//MISD("j:" + to_string(j))
			addCard(R->PlayerMatrix[i]->Deck[j]->CardID,
				getFromCSVUnit(R->PlayerMatrix[i]->Deck[j]->CardID),
				getFromCSVSpell(R->PlayerMatrix[i]->Deck[j]->CardID),
				getFromCSVBuilding(R->PlayerMatrix[i]->Deck[j]->CardID),
				WebDeckDeck);
		}

		if (WebDeckDeck.size() != 0)break;
	}

	if (WebDeckDeck.size() == 0)
	{
		MISEA("No Deck?");
		return false;
	}

	addColors(WebDeckDeck);

	MISE;
	return true;
}


bool WEB_Replay::getFromCSVBuilding(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bBuilding;

	return false;
}

bool WEB_Replay::getFromCSVSpell(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bSpell;

	return false;
}

bool WEB_Replay::getFromCSVUnit(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bUnit;

	return false;
}


bool WEB_Replay::FillTableBOT2(std::vector <WebCard*>& WebDeck, Wt::WTable *wtTabelle)
{
	MISS;
	unsigned short iRow = 0;
	unsigned short iCol = 0;

	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Tier Check</h3>"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Tier 1"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Tier 2"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Tier 3"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Tier 4"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));

	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Type Check</h3>"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Unit"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Building"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Spell"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));

	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Color Check</h3>"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Fire"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Nature"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Frost"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Shadow"))));

	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Twilight"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Stonekin"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Lost Souls"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Bandits"))));

	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Others"))));
	wtTabelle->elementAt(iRow++, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" "))));
	iRow--;

	MISD("#1");
	for (int i = 0; i < iRow; i++)
	{
		wtTabelle->elementAt(i, iCol)->setHeight(BOT2_IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage(""))));
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setHeight(BOT2_IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setWidth(BOT2_IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->resize(BOT2_IMG_SIZE, BOT2_IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setMaximumSize(BOT2_IMG_SIZE, BOT2_IMG_SIZE);
	}
	iCol++;
	iCol++;
	MISD("#2");

	for (unsigned int i = 0; i < WebDeck.size(); i++)
	{
		wtTabelle->elementAt(WebDeck[i]->iFire + WebDeck[i]->iNature + WebDeck[i]->iFrost + WebDeck[i]->iShadow + WebDeck[i]->iNeutral, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[0])));


		if (WebDeck[i]->bUnit)wtTabelle->elementAt(7, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[1])));
		if (WebDeck[i]->bBuilding)wtTabelle->elementAt(8, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[1])));
		if (WebDeck[i]->bSpell)wtTabelle->elementAt(9, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[1])));

		if (WebDeck[i]->iFire != 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(12, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(13, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(14, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(15, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));

		else if (WebDeck[i]->iFire != 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(16, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(17, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(18, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire != 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(19, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
		else wtTabelle->elementAt(20, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WebDeck[i]->IMG[2])));
	}

	iCol--;
	MISD("#Z1");
	//Tier check
	for (int i = 1; i < 5; i++)
	{
		//static_cast
		if (wtTabelle->elementAt(i, iCol + 1)->count() == 4)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	//Type check
	for (int i = 7; i < 10; i++)
	{
		//static_cast
		if (wtTabelle->elementAt(i, iCol + 1)->count() <= 6 && wtTabelle->elementAt(i, iCol + 1)->count() >= 5)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	//Color check1
	if (wtTabelle->elementAt(12, iCol + 1)->count() +
		wtTabelle->elementAt(13, iCol + 1)->count() +
		wtTabelle->elementAt(14, iCol + 1)->count() +
		wtTabelle->elementAt(15, iCol + 1)->count() == 16)
	{
		for (int i = 12; i < 16; i++)
		{
			if (wtTabelle->elementAt(i, iCol + 1)->count() == 4)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
			else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
		}
		for (int i = 16; i < 20; i++)
		{
			if (wtTabelle->elementAt(i, iCol + 1)->count() == 0)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
			else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
		}
	}
	else for (int i = 12; i < 20; i++)
	{
		if (wtTabelle->elementAt(i, iCol + 1)->count() == 2)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	if (wtTabelle->elementAt(20, iCol + 1)->count() == 0)dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(20, iCol)->widget(0))->setImageLink("./resources/1.png");
	else dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(20, iCol)->widget(0))->setImageLink("./resources/0.png");

	//wtTabelle->elementAt(i, iCol + 1)->widget(0)->setHeight(IMG_SIZE);
	MISD("##5");
	for (int i = 0; i < iRow; i++)
	{
		//MISD(to_string(i));
		if (dynamic_cast<Wt::WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->imageLink() == Wt::WLink("./resources/0.png"))
		{
			MISEA("X1");
			return false;
		}
	}

	MISE;
	return true;
}


void WEB_Replay::BOT3WellsAndOrbUnit()
{
	MISS;

	//Nur einmal!
	if (BOT3Stuff == true)return;

	//Nur infos f�r eine Map
	if (R->MapName != "11101_PvE_01p_TugOfWar.map") return;

	Action * Action_TEMP;
	unsigned int Player;

	for (Player = 0; Player < R->PlayerMatrix.size(); Player++)
	{
		if (R->PlayerMatrix[Player]->Type != 1)continue;
		else break;
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		Action_TEMP = new Action;
		Action_TEMP->Time = 0;
		Action_TEMP->Type = 4030;
		Action_TEMP->ActionPlayer = R->PlayerMatrix[Player]->ActionPlayer;
		Action_TEMP->AdditionalInfo = std::to_string(4550 + i);
		R->ActionMatrix.insert(R->ActionMatrix.begin(), Action_TEMP);
	}

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type != 4031)continue;
		R->ActionMatrix[i]->AdditionalInfo = R->ActionMatrix[i]->AdditionalInfo + ";4555";
		MISE;
		return;
	}

	MISE;
}


unsigned long WEB_Replay::FillTableBOT3(Wt::WTable *wtTabelle)
{
	MISS;

	unsigned int iMaxAction = 0;
	unsigned long iUnit;

	InitVector();
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Wells </h3>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Orbs </h3>"))));
	//wtTabelle->elementAt(0,2)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3> Walls </h3>"))));
	wtTabelle->columnAt(0)->setWidth(100);
	wtTabelle->columnAt(1)->setWidth(100);
	//wtTabelle->columnAt(2)->setWidth(100);

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if ( //R->ActionMatrix[i]->Type != 4029
			R->ActionMatrix[i]->Type != 4030
			&& R->ActionMatrix[i]->Type != 4031)continue;

		iUnit = atoi(R->ActionMatrix[i]->AdditionalInfo.erase(0, R->ActionMatrix[i]->AdditionalInfo.find(";") + 1).c_str());

		for (unsigned int j = 0; j < vMarker.size(); j++)
		{
			if (vMarker[j]->Unit == iUnit && WSTRINGtoSTRING(vMarker[j]->Time->text()) == "XX:XX")
			{
				vMarker[j]->Time->setText(sTime(R->ActionMatrix[i]->Time));
				iMaxAction = i;
			}
		}
	}


	iUnit = atoi(R->ActionMatrix[iMaxAction]->AdditionalInfo.erase(0, R->ActionMatrix[iMaxAction]->AdditionalInfo.find(";") + 1).c_str());

	for (unsigned int i = 0; i < 3; i++)
	{

		for (unsigned int j = 0, iRow = 1; j < vMarker.size(); j++)
		{
			if (vMarker[j]->Type != i) continue;

			wtTabelle->elementAt(++iRow, vMarker[j]->Type)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(vMarker[j]->Time)));
			if (WSTRINGtoSTRING(vMarker[j]->Time->text()) == "XX:XX")wtTabelle->elementAt(iRow, vMarker[j]->Type)->setStyleClass("red");
			if (vMarker[j]->Unit == iUnit)wtTabelle->elementAt(iRow, vMarker[j]->Type)->setStyleClass("green");

			wtTabelle->elementAt(iRow, vMarker[j]->Type)->mouseWentOver().connect([=] {
				vMarker[j]->IMG->setHidden(false);
			});

			wtTabelle->elementAt(iRow, vMarker[j]->Type)->mouseWentOut().connect([=] {
				vMarker[j]->IMG->setHidden(true);
			});

		}
	}

	MISE;
	return R->ActionMatrix[iMaxAction]->Time;
}


void WEB_Replay::InitVector()
{
	MISS;


	vMarker.clear();
	MISD(std::to_string(90 + Xoffset) + "#" + std::to_string(267 + Yoffset));
	vMarker.push_back(new Marker(1, 4555, 90, 267));
	vMarker.push_back(new Marker(1, 4556, 157, 318));
	vMarker.push_back(new Marker(1, 4558, 332, 103));
	vMarker.push_back(new Marker(1, 4557, 60, 142));

	vMarker.push_back(new Marker(0, 4550, 85, 263));
	vMarker.push_back(new Marker(0, 4551, 79, 262));
	vMarker.push_back(new Marker(0, 4552, 83, 258));
	vMarker.push_back(new Marker(0, 4553, 46, 286));
	vMarker.push_back(new Marker(0, 4554, 45, 293));
	vMarker.push_back(new Marker(0, 4536, 145, 368));
	vMarker.push_back(new Marker(0, 4535, 155, 368));
	vMarker.push_back(new Marker(0, 4539, 339, 330));
	vMarker.push_back(new Marker(0, 4540, 342, 257));
	vMarker.push_back(new Marker(0, 4537, 157, 244));
	vMarker.push_back(new Marker(0, 4538, 158, 249));
	vMarker.push_back(new Marker(0, 4541, 247, 148));
	vMarker.push_back(new Marker(0, 4543, 247, 154));
	vMarker.push_back(new Marker(0, 4542, 188, 36));
	vMarker.push_back(new Marker(0, 4544, 328, 96));
	vMarker.push_back(new Marker(0, 4545, 325, 103));
	vMarker.push_back(new Marker(0, 4546, 328, 110));
	vMarker.push_back(new Marker(0, 4547, 65, 136));
	vMarker.push_back(new Marker(0, 4548, 59, 148));
	vMarker.push_back(new Marker(0, 4549, 67, 144));

	//vMarker.push_back(new Marker(2, 4452,  75, 316));
	//vMarker.push_back(new Marker(2, 4453, 151, 347));
	//vMarker.push_back(new Marker(2, 4455, 291, 76));

	

	MISE;
}