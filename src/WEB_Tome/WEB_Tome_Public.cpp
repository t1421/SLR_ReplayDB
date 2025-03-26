//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Public.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicCards.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"

#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include <Wt/WSlider.h>


broker *(WEB_Tome_Public::Bro) = NULL;

WEB_Tome_Public::WEB_Tome_Public(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;
	
	wtGameID = new Wt::WText("");	
	waLink = new Wt::WAnchor();
	waLink->setText("<h5> PublicLink </h5>");

	MISD("#X");
	slider = new Wt::WSlider();
	slider->resize(390, 5);
	slider->disable();	
	sliderText = new Wt::WText("");

	MISD("#A");

	cMain = new Wt::WContainerWidget();	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderText)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(slider)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
	


	MISD("#0");
	
	PB = new WEB_Tome_PublicBoosters(Con);
	PP = new WEB_Tome_PublicPlayers(Con);
	PC = new WEB_Tome_PublicCards(Con);
	PPB = new WEB_Tome_PublicPlayersBooster(Con);
	
	MISD("#1");
	
	WEB_Toolbar::ToolBarButton(0, "Players", *PP->cMain, PP);
	WEB_Toolbar::ToolBarButton(1, "Boosters", *PB->cMain, PB);
	WEB_Toolbar::ToolBarButton(2, "Cards", *PC->cMain, PC);
	WEB_Toolbar::ToolBarButton(3, "Player Boosters", *PPB->cMain, PPB);

	Wt::WContainerWidget *XXX = new Wt::WContainerWidget();
	sToolbar->insertWidget(4, std::unique_ptr<Wt::WContainerWidget>(std::move(XXX)));
	

	MISD("#2");

	WEB_Toolbar::bDisable[0] = true;
	WEB_Toolbar::bDisable[1] = true;
	WEB_Toolbar::bDisable[2] = true;
	WEB_Toolbar::bDisable[3] = true;

	MISD("#3");
	
	WEB_Toolbar::updateToolbar();
	
	MISD("#2");

	//WRefresh();

	MISE;
}

void WEB_Tome_Public::WRefresh()
{
	MISS;
	unsigned int isBooster = 0;
	unsigned int maxBooster = 0;

	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	std::stringstream sLink;
	sLink << Bro->L_getWebTome() << "?gameID=" << Bro->vTomeGames[Con->BroGameID]->sGameID;
	waLink->setLink(Wt::WLink(sLink.str()));

	WEB_Toolbar::bDisable[0] = !Bro->vTomeGames[Con->BroGameID]->bTapShowPlayer;
	WEB_Toolbar::bDisable[1] = !Bro->vTomeGames[Con->BroGameID]->bTapShowBooster;
	WEB_Toolbar::bDisable[2] = !Bro->vTomeGames[Con->BroGameID]->bTapShowCards;
	WEB_Toolbar::bDisable[3] = !Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayer;
	
	if (!WEB_Toolbar::bDisable[0])WEB_Toolbar::sToolbar->setCurrentIndex(0);
	else if (!WEB_Toolbar::bDisable[1])WEB_Toolbar::sToolbar->setCurrentIndex(1);
	else if (!WEB_Toolbar::bDisable[2])WEB_Toolbar::sToolbar->setCurrentIndex(2);
	else if (!WEB_Toolbar::bDisable[3])WEB_Toolbar::sToolbar->setCurrentIndex(3);


	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
	{
		isBooster += Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters.size();
		maxBooster += Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->iMaxBoostersSum();
	}
	

	slider->setRange(0, maxBooster);
	slider->setValue(isBooster);
	sliderText->setText(std::to_string(isBooster) + " / " + std::to_string(maxBooster));

	WEB_Toolbar::updateToolbar();
	updateFrame();

	MISE;
}

