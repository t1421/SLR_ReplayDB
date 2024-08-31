#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\..\incl\WEB_Analyser\WEB_Event.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WHBoxLayout.h>

broker *(WEB_Event::Bro) = NULL;

WEB_Event::WEB_Event(WEB_Analyser *WR_, unsigned int _iEventNr) : WR(WR_), iEventNr(_iEventNr)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
		
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTime		= new Wt::WText(" ");
	wtPower		= new Wt::WText(" ");
	
	MISD("#1");
	
	Rank = new WEB_Rank(WR, iEventNr);
	
	MISD("#2");
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTime)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPower)));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Rank->cMain)));
	
	MISD("#3");
	Rank->WRefresh();

	MISE;
}

void WEB_Event::WRefresh()
{
	MISS;
	
	wtTime->setText(" ");
	std::string sTeamID;

	unsigned long iTimes[RankRowStamps] = {0};

	std::string sReturn;

	switch (iEventNr)
	{
		case 100: sReturn = WR->Kalk_Event100(iTimes); break;
		case 101: sReturn = WR->Kalk_Event101(); break;
	}
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{	
		switch (iEventNr)
		{
		case 100:
			sTeamID = WR->GetTeamID();
			if (Bro->AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			wtPower->setText("Power: " + std::to_string(iTimes[1]));
			break;
		case 101:
			WR->AddPlayers101();
			//if (Bro->AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
			//	WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Nice run :-)</h3> ");
			//wtTime->setText("Time: " + sTime(iTimes[0]));
			//wtPower->setText("Power: " + std::to_string(iTimes[1]));
			break;
		}

	}
	
	Rank->WRefresh();
	MISE;
}

