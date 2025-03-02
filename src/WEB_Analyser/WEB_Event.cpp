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
#include <Wt/WSlider.h>

broker *(WEB_Event::Bro) = NULL;

WEB_Event::WEB_Event(WEB_Analyser *WR_, unsigned int _iEventNr) : WR(WR_), iEventNr(_iEventNr)
{
	MISS;

	Bro->UpdateEventRankModes(_iEventNr);

	cMain = new Wt::WContainerWidget();	

	wtStatus = new Wt::WText(" ");
	wtTime = new Wt::WText(" ");
	wtPower = new Wt::WText(" ");
		
	MISD("#0");

	std::time_t timestampS = Bro->L_get_Start(_iEventNr);
	std::time_t timestampE = Bro->L_get_End(_iEventNr);

	slider = new Wt::WSlider();
	slider->resize(390, 5);
	slider->disable();
	slider->setRange(timestampS, timestampE);
	sliderText = new Wt::WText("Timeframe: " + TimeToText(timestampS) + " - " + TimeToText(timestampE));


	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderText)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(slider)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));


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

	slider->setValue(Bro->L_getEEE_Now());	

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
		case 102: sReturn = WR->Kalk_Event102(iTimes); break;
		case 103: sReturn = WR->Kalk_Event103(iTimes); break;
		case 104: sReturn = WR->Kalk_Event104(iTimes); break;
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
			WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + "_" + WR->getMapName() + "_" + std::to_string(WR->getReplayHash()) + ".pmv");
			wtStatus->setText("<h3>Nice run :-)</h3> ");
			break;

		case 102:
			sTeamID = WR->GetTeamID();
			if (Bro->AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			wtPower->setText("Points: " + std::to_string(iTimes[1]));
			break;

		case 103:
			sTeamID = WR->GetTeamID();
			if (Bro->AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			break;
		case 104:
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			if (Bro->AddPlayer(iEventNr, sTeamID, 0, iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + sTeamID + ", nice run : -) </h3> ");
			break;
		}

	}
	
	Rank->WRefresh();
	MISE;
}


