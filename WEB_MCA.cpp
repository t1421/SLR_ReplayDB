//#define DF_Debug

#include "Broker.h"

#include "Utility.h" 
#include "WEB_MCA.h"
#include "WEB_Replay.h"

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

	unsigned long iTime;

	wtTabelle->clear();
	std::string sReturn = WR->BOT3(wtTabelle, cMap, iTime);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		//wtStatus->setText("<h3>All looks good :-)</h3> ");
		std::string sRankName;
		switch (Bro->AddRankPlayer(BOT3LIST, WR->Player(), iTime, sRankName))
		{
		case 5: //Slower
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> but slower :-)</h3> ");
			break;
		case 9: //Same
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> same time as before :-)</h3> ");
			break;
		case 10: //Faster
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> faster then your last :-)</h3> ");
			break;
		case 15: //New Player
			wtStatus->setText("<h3>Welcome to the Leaderboard " + sRankName + ": " + sTime(iTime) + ":-)</h3> ");
			break;
		default: //Should not happen
			wtStatus->setText("<h3>WHAT HAPPEND?</h3> ");
		}		
		MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}

	MISE;
}
