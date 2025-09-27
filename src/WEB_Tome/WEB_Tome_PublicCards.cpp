//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicCards.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>

broker *(WEB_Tome_PublicCards::Bro) = NULL;

WEB_Tome_PublicCards::WEB_Tome_PublicCards(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtTabelle = new Wt::WTable();
	wlFilter = new Wt::WLineEdit();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
		
	MISD("#0");
	wlFilter->setWidth(Card_Size_X * 9);

	//WRefresh();

	MISE;
}

void WEB_Tome_PublicCards::WRefresh()
{
	MISS;

	wtTabelle->clear();

	std::vector<std::unique_ptr<SMJCard>> vAllCards;
	std::vector <Tome_Booster*> vAllBoosters;

	for (auto P : Bro->vTomeGames[Con->BroGameID]->vPlayer)
		for (auto B : P->vBoosters)
		{
			vAllBoosters.push_back(B);
			//for (auto C : B->vCards)
			for (unsigned int i = 0; i < B->vCards.size(); i++)
			{
				if (B->sType == "-91")i = 4;
				vAllCards.push_back(std::make_unique<SMJCard>(*B->vCards[i]));
			}
		}

	Con->DrawCard(wtTabelle, vAllCards);
	wlFilter->setText(Con->BoosterToFilter(vAllBoosters, 3));

	MISE;
}
