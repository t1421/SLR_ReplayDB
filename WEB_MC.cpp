#define DF_Debug

#include "prototypes.h"
#include "WEB_Main.h"
#include "WEB_MC.h"
#include "WEB_MCA.h"
#include "WEB_MCB.h"

broker *(WEB_MC::Bro) = NULL;

WEB_MC::WEB_MC(WEB_Replay *WR_)
{
	MISS;

	cMain = new WContainerWidget();
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(sToolbar)));

	MISD("#10");

	A = new WEB_MCA(WR_);
	B = new WEB_MCB();
	
	MISD("#11");	

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain, A);	
	WEB_Toolbar::ToolBarButton(1, "Rank", *B->cMain, B);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	
	MISE;
}

void WEB_MC::WRefresh()
{
	MISS;
	updateFrame();
	MISE;
}