//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicCards.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Tome_PublicCards::Bro) = NULL;

WEB_Tome_PublicCards::WEB_Tome_PublicCards(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtTabelle = new Wt::WTable();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
		
	MISD("#0");

	//WRefresh();

	MISE;
}

void WEB_Tome_PublicCards::WRefresh()
{
	MISS;

	wtTabelle->clear();

	std::vector<SMJCard*> vAllCards;

	for (auto P : Bro->vTomeGames[Con->BroGameID]->vPlayer)
		for (auto B : P->vBoosters)
			for (auto C : B->vCards)
				vAllCards.push_back(C);

	Con->DrawCard(wtTabelle, vAllCards);

	MISE;
}
