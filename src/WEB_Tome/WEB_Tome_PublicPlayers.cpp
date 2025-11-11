//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Tome_PublicPlayers::Bro) = NULL;

WEB_Tome_PublicPlayers::WEB_Tome_PublicPlayers(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtTabelle = new Wt::WTable();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
		
	MISD("#0");

	//WRefresh();

	MISE;
}

void WEB_Tome_PublicPlayers::WRefresh()
{
	MISS;

	wtTabelle->clear();

	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Player </h3>"))));
	if(Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterOpen)wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Boosters Opend </h3>"))));
	if (Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterMax)wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Max Boosters </h3>"))));

	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
	{
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerName))));
		if (Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterOpen)wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->iOpendBoostersSum())))));
		if (Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterMax)wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->iMaxBoostersSum())))));
	}

	wtTabelle->columnAt(0)->setWidth(150);
	wtTabelle->columnAt(1)->setWidth(75);
	wtTabelle->columnAt(2)->setWidth(75);

	MISE;
}
