#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_Analyser_Deck.h"
#include "..\..\incl\Replay.h" 

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

#define Card_Size_X 185
#define Card_Size_Y 255

broker *(WEB_Analyser_Deck::Bro) = NULL;

WEB_Analyser_Deck::WEB_Analyser_Deck(WEB_Analyser *WA_) : WA(WA_)
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


	if (WA->isOK() != true)
	{
		MISEA("no Replay");
		return;
	}

	
	unsigned iRow = 0;
	for (unsigned int i= 0; i < WA->Players.size(); i++)
	{
		if (WA->Players[i]->Type != 1)continue; //only "real" players
		drawPlayer(i, iRow);
		iRow += 2;
	}

	MISE;
}


unsigned int WEB_Analyser_Deck::drawPlayer(unsigned int iPlayer, unsigned int &iRow)
{
	MISS;
	unsigned short iCol = 0;
	unsigned char tempCharge;
	wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>" + WA->Players[iPlayer]->Name + "</h3>"))));
	wtTabelle->elementAt(iRow, iCol)->setColumnSpan(5);
	iRow++;

	for (unsigned int i = 0; i < WA->Players[iPlayer]->Deck.size(); i++)
	{
		if (WA->Players[iPlayer]->Deck[i]->CardID == 0)continue;
		tempCharge = Bro->J_SwitchCharges(WA->Players[iPlayer]->Deck[i]->CardID, WA->Players[iPlayer]->Deck[i]->Charges);
		if (tempCharge > WA->Players[iPlayer]->Deck[i]->Upgrade)tempCharge = WA->Players[iPlayer]->Deck[i]->Upgrade;

		wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage(Bro->J_GetImage(
			WA->Players[iPlayer]->Deck[i]->CardID,
			WA->Players[iPlayer]->Deck[i]->Upgrade,
			tempCharge,
			WA->Players[iPlayer]->Deck[i]->count,
			false
		)))));
		
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setHeight(Card_Size_Y);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setWidth(Card_Size_X);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->resize(Card_Size_X, Card_Size_Y);
		wtTabelle->elementAt(iRow, iCol)->widget(0)->setMaximumSize(Card_Size_X, Card_Size_Y);
		wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h></h>"))));
		wtTabelle->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(WA->Players[iPlayer]->Deck[i]->count)))));
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