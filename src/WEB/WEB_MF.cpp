#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_MF.h"
#include "..\..\incl\WEB\WEB_MFA.h"
#include "..\..\incl\WEB\WEB_Rank.h"

broker *(WEB_MF::Bro) = NULL;

WEB_MF::WEB_MF(WEB_Analyser *WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));

	MISD("#10");

	A = new WEB_MFA(WR_);
	B[0] = new WEB_Rank(KOTGLIST1);
	B[1] = new WEB_Rank(KOTGLIST2);
	B[2] = new WEB_Rank(KOTGLIST3);
	B[3] = new WEB_Rank(KOTGLIST4);
	
	
	MISD("#11");	

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain, A);	
	WEB_Toolbar::ToolBarButton(1, "Rank Orbs", *B[0]->cMain, B[0]);
	WEB_Toolbar::ToolBarButton(2, "Rank Walls", *B[1]->cMain, B[1]);
	WEB_Toolbar::ToolBarButton(3, "Rank Amii", *B[2]->cMain, B[2]);
	WEB_Toolbar::ToolBarButton(4, "Rank Total", *B[3]->cMain, B[3]);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	
	MISE;
}

void WEB_MF::WRefresh()
{
	MISS;
	updateFrame();
	MISE;
}