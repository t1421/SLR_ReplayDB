#define DF_Debug

#include "Broker.h"

#include "WEB_MBA.h"
#include "WEB_Replay.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>

broker *(WEB_MBA::Bro) = NULL;

WEB_MBA::WEB_MBA(WEB_Replay *WR_, bool bMode_): WR(WR_), bMode(bMode_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	wtStatus	= new Wt::WText(" ");
	wtTabelle   = new Wt::WTable();
			
	MISD("#1");	

	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)), 0, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)), 1, 0);
		
	MISE;
}

void WEB_MBA::WRefresh()
{
	MISS;
	
	wtTabelle->clear();
	std::string sReturn = WR->BOT2(bMode, wtTabelle);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else wtStatus->setText("<h3>All looks good :-)</h3> ");

	MISE;
}

