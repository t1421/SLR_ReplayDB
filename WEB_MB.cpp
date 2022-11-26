#define DF_Debug

#include "Broker.h"

#include "WEB_MB.h"
#include "WEB_MBA.h"

class WEB_Replay;


broker *(WEB_MB::Bro) = NULL;

WEB_MB::WEB_MB(WEB_Replay *WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
			
	MISD("#1");	

	A = new WEB_MBA(WR_,true);
	B = new WEB_MBA(WR_, false);

	MISD("#3");

	WEB_Toolbar::ToolBarButton(0, "Cards Played", *A->cMain,A);
	WEB_Toolbar::ToolBarButton(1, "Cards in Deck", *B->cMain,B);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();
	
	
	MISE;
}


void WEB_MB::WRefresh()
{
	MISS;
	updateFrame();
	MISE;
}

