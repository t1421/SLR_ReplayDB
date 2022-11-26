#define DF_Debug

#include "Broker.h"

//#include "Replay.h" 
#include "WEB_Replay.h"

#include "WEB_MCA.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>

broker *(WEB_MCA::Bro) = NULL;

WEB_MCA::WEB_MCA(WEB_Replay *WR_) : WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	cReplay = new Wt::WContainerWidget();
	cReplayResult = new Wt::WContainerWidget();
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTabelle   = new Wt::WTable();
	
	MISD("#1");

	cMap = new Wt::WContainerWidget();
	wiMap = new Wt::WImage("./resources/TheTreasureFleet.webp");
	cMap->setStyleClass("crop");
	
	MISD("#2");
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)), 1, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(cMap)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(cReplayResult)), 2, 1);
	
	TempGrid->setColumnStretch(0, 5);
	TempGrid->setColumnStretch(1, 95);

	cReplayResult->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	cReplayResult->setContentAlignment(Wt::AlignmentFlag::Left);
	
	cMap->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wiMap)));
	cMap->setMaximumSize(400, 400);
	
	MISE;
}

void WEB_MCA::WRefresh()
{
	MISS;

	wtTabelle->clear();
	std::string sReturn = WR->BOT3(wtTabelle, cMap);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else wtStatus->setText("<h3>All looks good :-)</h3> ");

	MISE;
}
