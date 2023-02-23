#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser_Deck.h"
#include "..\..\incl\WEB\WEB_Replay.h"
#include "..\..\incl\Replay.h" 

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

#define Card_Size_X 185
#define Card_Size_Y 255

broker *(WEB_Analyser_Deck::Bro) = NULL;

WEB_Analyser_Deck::WEB_Analyser_Deck(WEB_Replay *WR_): WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtTabelle = new Wt::WTable();
				
	MISD("#1");	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
		
	MISE;
}

void WEB_Analyser_Deck::WRefresh()
{
	MISS;

	wtTabelle->clear();


	if (WR->R->OK != true)
	{
		MISEA("no Replay");
		return;
	}

	if (!GetDecks())
	{
		MISEA("ERROR in Deck");
		return;
	}

	unsigned iRow = 0;
	for (unsigned int i= 0; i < Players.size(); i++)
	{
		if (Players[i]->Type != 1)continue; //only "real" players
		drawPlayer(i, iRow);
		iRow += 2;
	}

	MISE;
}

bool WEB_Analyser_Deck::GetDecks()
{
	MISS;

	Players.clear();
	Player *Player_Temp;
	Card *Card_Temp;

	unsigned int CardLoop;
	bool Found;

	for (unsigned int i = 0; i < WR->R->PlayerMatrix.size(); i++)
	{
		MISD(std::to_string(WR->R->PlayerMatrix[i]->Deck.size()));
		Player_Temp = new Player;
		//Player_Temp = WR->R->PlayerMatrix[i];
		Player_Temp->Name = WR->R->PlayerMatrix[i]->Name;
		Player_Temp->PlayerID = WR->R->PlayerMatrix[i]->PlayerID;
		Player_Temp->ActionPlayer = WR->R->PlayerMatrix[i]->ActionPlayer;
		Player_Temp->GroupID = WR->R->PlayerMatrix[i]->GroupID;
		Player_Temp->IDinGroup = WR->R->PlayerMatrix[i]->IDinGroup;
		Player_Temp->Type = WR->R->PlayerMatrix[i]->Type;
		Player_Temp->Deck.clear();
		for (unsigned int j = 0; j < WR->R->ActionMatrix.size(); j++)
		{
			if (WR->R->ActionMatrix[j]->PlayerID != WR->R->PlayerMatrix[i]->PlayerID)continue;
			if (WR->R->ActionMatrix[j]->Type != 4012 //Building
			&&  WR->R->ActionMatrix[j]->Type != 4011 //Spell 2
			&&  WR->R->ActionMatrix[j]->Type != 4010 //Spell 1
			&&  WR->R->ActionMatrix[j]->Type != 4009 //Unit
				)continue;

			Found = false;
			for (CardLoop = 0; CardLoop < Player_Temp->Deck.size(); CardLoop++)
				if (Player_Temp->Deck[CardLoop]->CardID == WR->R->ActionMatrix[j]->Card)
				{
					Found = true;
					break;
				}
			
			if (Found == false)
			{
				//MISD("ADD   :" + std::to_string(WR->R->ActionMatrix[j]->Card));
				Card_Temp = new Card;
				Card_Temp->CardID = WR->R->ActionMatrix[j]->Card;
				Card_Temp->Charges = WR->R->ActionMatrix[j]->Charges;
				Card_Temp->Upgrade = WR->R->ActionMatrix[j]->Upgrade;
				Card_Temp->count = 0;
				Player_Temp->Deck.push_back(Card_Temp);
			}
			Player_Temp->Deck[CardLoop]->count++;
		}

		//Get Deck of Hosting Player
		if (WR->R->PlayerMatrix[i]->PlayerID == WR->R->PMVPlayerID)
		{
			MISD(std::to_string(WR->R->PlayerMatrix[i]->Deck.size()));
			for (int j = 0; j < WR->R->PlayerMatrix[i]->Deck.size(); j++)
			{
				Found = false;
				for (CardLoop = 0; CardLoop < Player_Temp->Deck.size(); CardLoop++)
					if (Player_Temp->Deck[CardLoop]->CardID == WR->R->PlayerMatrix[i]->Deck[j]->CardID)
					{
						Found = true;
						break;
					}

				if (Found == false)
				{
					//MISD("ADD   :" + std::to_string(WR->R->ActionMatrix[j]->Card));
					Card_Temp = new Card;
					Card_Temp->CardID = WR->R->PlayerMatrix[i]->Deck[j]->CardID;
					Card_Temp->Charges = WR->R->PlayerMatrix[i]->Deck[j]->Charges;
					Card_Temp->Upgrade = WR->R->PlayerMatrix[i]->Deck[j]->Upgrade;
					Card_Temp->count = 0;
					Player_Temp->Deck.push_back(Card_Temp);
				}

			}

		}
		
		Players.push_back(Player_Temp);
	}

	MISE;
	return true;
}



unsigned int WEB_Analyser_Deck::drawPlayer(unsigned int iPlayer, unsigned int &iRow)
{
	MISS;
	unsigned short iCol = 0;
	unsigned char tempCharge;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>"+Players[iPlayer]->Name+"</h3>"))));
	wtTabelle->elementAt(iRow, iCol)->setColumnSpan(5);
	iRow++;

	for (unsigned int i = 0; i < Players[iPlayer]->Deck.size(); i++)
	{
		if (Players[iPlayer]->Deck[i]->CardID == 0)continue;
		tempCharge = Bro->J_SwitchCharges(Players[iPlayer]->Deck[i]->CardID, Players[iPlayer]->Deck[i]->Charges);
		if (tempCharge > Players[iPlayer]->Deck[i]->Upgrade)tempCharge = Players[iPlayer]->Deck[i]->Upgrade;

		wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage(Bro->J_GetImage(
			Players[iPlayer]->Deck[i]->CardID,
			Players[iPlayer]->Deck[i]->Upgrade,
			tempCharge,
			Players[iPlayer]->Deck[i]->count
		)))));
		
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setHeight(Card_Size_Y);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setWidth(Card_Size_X);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->resize(Card_Size_X, Card_Size_Y);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setMaximumSize(Card_Size_X, Card_Size_Y);

		wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Players[iPlayer]->Deck[i]->count)))));
		//wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Players[iPlayer]->Deck[i]->CardID)))));

		iCol++;
		if (i % 5 == 4)
		{
			iRow++;
			iCol = 0;
		}
	}
	

	MISE;
	return 1;
}