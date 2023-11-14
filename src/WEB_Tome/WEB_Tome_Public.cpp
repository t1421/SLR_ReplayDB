//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Public.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"

#include <Wt/WLink.h>
#include <Wt/WAnchor.h>

broker *(WEB_Tome_Public::Bro) = NULL;

WEB_Tome_Public::WEB_Tome_Public(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;
	
	wtGameID = new Wt::WText("");	
	waLink = new Wt::WAnchor();
	waLink->setText("<h5> PublicLink </h5>");

	MISD("#A");

	cMain = new Wt::WContainerWidget();	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
	


	MISD("#0");
	
	PB = new WEB_Tome_PublicBoosters(Con);
	PP = new WEB_Tome_PublicPlayers(Con);
	PPB = new WEB_Tome_PublicPlayersBooster(Con);
	
	MISD("#1");
	
	WEB_Toolbar::ToolBarButton(0, "Players", *PP->cMain, PP);
	WEB_Toolbar::ToolBarButton(1, "Boosters", *PB->cMain, PB);
	WEB_Toolbar::ToolBarButton(2, "Player Boosters", *PPB->cMain, PPB);

	Wt::WContainerWidget *XXX = new Wt::WContainerWidget();
	sToolbar->insertWidget(3, std::unique_ptr<Wt::WContainerWidget>(std::move(XXX)));
	

	MISD("#2");

	WEB_Toolbar::bDisable[0] = true;
	WEB_Toolbar::bDisable[1] = true;
	WEB_Toolbar::bDisable[2] = true;

	MISD("#3");
	
	WEB_Toolbar::updateToolbar();
	
	MISD("#2");

	//WRefresh();

	MISE;
}

void WEB_Tome_Public::WRefresh()
{
	MISS;

	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	waLink->setLink(Wt::WLink("https://t1421.tk/tome?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID));

	WEB_Toolbar::bDisable[0] = !Bro->vTomeGames[Con->BroGameID]->bShowPlayers;
	WEB_Toolbar::bDisable[1] = !Bro->vTomeGames[Con->BroGameID]->bShowBoosters;
	WEB_Toolbar::bDisable[2] = !Bro->vTomeGames[Con->BroGameID]->bShowBoostersOfPlayer;
	
	if (!WEB_Toolbar::bDisable[0])WEB_Toolbar::sToolbar->setCurrentIndex(0);
	else if (!WEB_Toolbar::bDisable[1])WEB_Toolbar::sToolbar->setCurrentIndex(1);
	else if (!WEB_Toolbar::bDisable[2])WEB_Toolbar::sToolbar->setCurrentIndex(2);
	WEB_Toolbar::updateToolbar();
	updateFrame();

	MISE;
}

