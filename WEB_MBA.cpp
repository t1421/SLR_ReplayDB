#define DF_Debug

#include "prototypes.h"
#include "WEB_Main.h"
#include "WEB_MBA.h"
#include "Load.h" 

broker *(WEB_MBA::Bro) = NULL;

WEB_MBA::WEB_MBA(WEB_Replay *WR_, bool bMode_): WR(WR_), bMode(bMode_)
{
	MISS;

	cMain = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	wtStatus	= new WText(" ");
	wtMap       = new WText(" ");
	wtTime      = new WText(" ");
	wtTabelle   = new WTable();
			
	MISD("#1");	

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 0, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 1, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 2, 0);	
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)), 3, 0);
		
	MISE;
}




void WEB_MBA::WRefresh()
{
	MISS;
	bool result = false;
	wtMap->setText(" ");
	wtTime->setText(" ");
	wtStatus->setText(" ");
	
	if (WR->BOT2())
	{
		wtMap->setText("Map: " + WR->MapName());
		wtTime->setText("Time: " + WR->Time());

		wtTabelle->clear();
		if (bMode)
		{
			WR->FillWebDeckAction();
			result = WR->FillTableBOT2(WR->WebDeckActions, wtTabelle);
		}
		else
		{
			WR->FillWebDeckDeck();
			result = WR->FillTableBOT2(WR->WebDeckDeck, wtTabelle);
		}

		if (result == true)wtStatus->setText("<h4>All looks good :-)</h4> ");		
		else wtStatus->setText("<h4>Something is wrong in your deck</h4> ");

	}
	else wtStatus->setText("<h3> somthing went wrong </h3>");

	MISE;
}

