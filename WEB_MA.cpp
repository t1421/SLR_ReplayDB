//#define DF_Debug

#include "Broker.h"

#include "WEB_MA.h"
#include "WEB_MAA.h"
#include "WEB_Rank.h"


broker *(WEB_MA::Bro) = NULL;

WEB_MA::WEB_MA(WEB_Replay *WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
	
	MISD("#1");

	A = new WEB_MAA(WR_);
	B = new WEB_Rank(BOT1LIST);

	MISD("#11");

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain, A);
	WEB_Toolbar::ToolBarButton(1, "Rank", *B->cMain, B);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();

	MISE;
}



void WEB_MA::WRefresh()
{
	MISS;
	updateFrame();		
	MISE;
}