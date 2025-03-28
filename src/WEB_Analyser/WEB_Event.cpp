//#define DF_Debug

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

	Bro->A_UpdateRankMode(_iEventNr);

	cMain = new Wt::WContainerWidget();	

	wtStatus = new Wt::WText(" ");
	wtTime = new Wt::WText(" ");
	wtPower = new Wt::WText(" ");
		
	MISD("#0");

	std::time_t timestampS = Bro->L_getEventStart(_iEventNr);
	std::time_t timestampE = Bro->L_getEventEnd(_iEventNr);

	slider = new Wt::WSlider();
	slider->resize(390, 5);
	slider->disable();
	slider->setRange(timestampS, timestampE);
	sliderText = new Wt::WText("Timeframe: " + TimeToText(timestampS) + " - " + TimeToText(timestampE));
	sliderNow = new Wt::WText("Now: " + TimeToText(Bro->L_getEEE_Now()));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderText)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderNow)));
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

	Bro->A_UpdateRankMode(iEventNr);
	
	wtTime->setText(" ");
	std::string sTeamID;

	unsigned long iTimes[RankRowStamps] = {0};

	std::string sReturn;

	switch (iEventNr)
	{
		case 0: Rank->WRefresh(); return;
		case 1: sReturn = WR->Kalk_Event0(iTimes, "sss1.map"); break;
		case 2: sReturn = WR->Kalk_Event2(iTimes); break;
		case 3: sReturn = WR->Kalk_Event3(iTimes); break;
		case 4: sReturn = WR->Kalk_Event0(iTimes, "sss4.map"); break;
		//case 5: sReturn = WR->Kalk_Event5(iTimes, Chart); break;
		case 6: sReturn = WR->Kalk_Event0(iTimes, "sss6.map"); break;
		case 7: sReturn = WR->Kalk_Event7(iTimes); break;
		case 8: sReturn = WR->Kalk_Event8(iTimes); break;
		case 9: sReturn = WR->Kalk_Event9(); break;
		case 10: sReturn = WR->Kalk_Event10(iTimes); break;
		case 11: sReturn = WR->Kalk_Event11(iTimes); break;
		case 12: sReturn = WR->Kalk_Event12(iTimes); break;
	}
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{	
		switch (iEventNr)
		{
		case 8:
			sTeamID = WR->GetTeamID();
			if (Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			wtPower->setText("Power: " + std::to_string(iTimes[1]));
			break;
		case 9:
			WR->AddPlayers9();
			WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + "_" + WR->getMapName() + "_" + std::to_string(WR->getReplayHash()) + ".pmv");
			wtStatus->setText("<h3>Nice run :-)</h3> ");
			break;

		case 10:
			sTeamID = WR->GetTeamID();
			if (Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetTeamID() + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			wtPower->setText("Points: " + std::to_string(iTimes[1]));
			break;

		case 11:
			sTeamID = WR->GetTeamID();
			if (Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtTime->setText("Time: " + sTime(iTimes[0]));
			break;
		case 12:
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			if (Bro->A_AddPlayer(iEventNr, sTeamID, 0, iTimes) == 1)
				WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + sTeamID + ", nice run : -) </h3> ");
			break;
		}

	}
	
	Rank->WRefresh();
	MISE;
}


