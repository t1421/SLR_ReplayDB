#define DF_Debug

#include "prototypes.h"
#include "WEB_Main.h"
#include "WEB_MC.h"
#include "WEB_MCA.h"
#include "WEB_MCB.h"

broker *(WEB_MC::Bro) = NULL;

WEB_MC::WEB_MC()
{
	MISS;

	cMain = new WContainerWidget();
	
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h1><b>BOT 3 Replay Checker</b></h1>"))));
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<WWidget>(std::move(sToolbar)));

	MISD("#10");

	A = new WEB_MCA();
	B = new WEB_MCB();
	
	MISD("#11");	

	WEB_Toolbar::ToolBarButton(0, "Replay", *A->cMain);	
	WEB_Toolbar::ToolBarButton(1, "Rank", *B->cMain);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	
	MISE;
}
