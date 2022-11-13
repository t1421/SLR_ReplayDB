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
	wtTabelle   = new WTable();
			
	MISD("#1");	

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 0, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)), 1, 0);
		
	MISE;
}

void WEB_MBA::WRefresh()
{
	MISS;
	
	wtTabelle->clear();
	string sReturn = WR->BOT2(bMode, wtTabelle);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else wtStatus->setText("<h3>All looks good :-)</h3> ");

	MISE;
}

