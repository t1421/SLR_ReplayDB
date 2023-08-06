//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_ME.h"
#include "..\..\incl\WEB_Analyser\WEB_MEA.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"

broker *(WEB_ME::Bro) = NULL;

WEB_ME::WEB_ME(WEB_Analyser *WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));

	MISD("#10");

	A = new WEB_MEA(WA_);
	MISD("#100");
	B = new WEB_Rank(BOT4LIST); 
	
	MISD("#11");	

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain, A);	
	WEB_Toolbar::ToolBarButton(1, "Rank", *B->cMain, B);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	
	MISE;
}

void WEB_ME::WRefresh()
{
	MISS;
	updateFrame();
	MISE;
}