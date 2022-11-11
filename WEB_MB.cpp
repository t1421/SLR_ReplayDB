#define DF_Debug

#include "prototypes.h"
#include "WEB_Main.h"
#include "WEB_MB.h"
#include "WEB_MBA.h"
#include "WEB_MBB.h"


broker *(WEB_MB::Bro) = NULL;

WEB_MB::WEB_MB()
{
	MISS;

	WColor wTemp;

	cMain = new WContainerWidget();
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h1><b>BOT 2 Replay Checker</b></h1>"))));
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(sToolbar)));
			
	MISD("#1");	

	A = new WEB_MBA();
	B = new WEB_MBB();

	MISD("#3");

	WEB_Toolbar::ToolBarButton(0, "Cards Played", *A->cMain);
	WEB_Toolbar::ToolBarButton(1, "Cards in Deck", *B->cMain);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();
	
	
	MISE;
}
