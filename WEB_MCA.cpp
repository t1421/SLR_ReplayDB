#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MCA.h"
#include "Load.h" 

broker *(WEB_MCA::Bro) = NULL;

WEB_MCA::WEB_MCA(WEB_Replay *WR_) : WR(WR_)
{
	MISS;

	cMain = new WContainerWidget();	
	cReplay = new WContainerWidget();
	cReplayResult = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();	
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	MISD("#0");

	wtStatus	= new WText(" ");
	wtTabelle   = new WTable();
	
	MISD("#1");

	cMap = new WContainerWidget();
	wiMap = new WImage("./resources/TheTreasureFleet.webp");
	cMap->setStyleClass("crop");
	
	MISD("#2");
	
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 1, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cMap)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cReplayResult)), 2, 1);
	
	TempGrid->setColumnStretch(0, 5);
	TempGrid->setColumnStretch(1, 95);

	cReplayResult->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)));
	cReplayResult->setContentAlignment(AlignmentFlag::Left);
	
	cMap->addWidget(std::unique_ptr<WWidget>(std::move(wiMap)));
	cMap->setMaximumSize(400, 400);
	
	MISE;
}

void WEB_MCA::WRefresh()
{
	MISS;

	wtTabelle->clear();
	string sReturn = WR->BOT3(wtTabelle, cMap);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else wtStatus->setText("<h3>All looks good :-)</h3> ");

	MISE;
}
