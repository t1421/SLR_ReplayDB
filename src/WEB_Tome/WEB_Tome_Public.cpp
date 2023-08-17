#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Public.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"

#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"

//#include <Wt/WContainerWidget.h>
//#include <Wt/WText.h>

broker *(WEB_Tome_Public::Bro) = NULL;

WEB_Tome_Public::WEB_Tome_Public(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
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
	WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();
	
	MISD("#2");

	//WRefresh();

	MISE;
}

void WEB_Tome_Public::WRefresh()
{
	MISS;
	
	updateFrame();

	MISE;
}

