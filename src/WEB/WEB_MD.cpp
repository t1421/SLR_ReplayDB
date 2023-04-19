//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_MD.h"
#include "..\..\incl\WEB\WEB_MDA.h"
#include "..\..\incl\WEB\WEB_Rank.h"

broker *(WEB_MD::Bro) = NULL;

WEB_MD::WEB_MD(WEB_Analyser *WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));

	MISD("#10");

	A = new WEB_MDA(WA_);
	MISD("#100");
	B = new WEB_Rank(VornskrLIST);
	
	MISD("#11");	

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain, A);	
	WEB_Toolbar::ToolBarButton(1, "Rank", *B->cMain, B);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	
	MISE;
}

void WEB_MD::WRefresh()
{
	MISS;
	updateFrame();
	MISE;
}