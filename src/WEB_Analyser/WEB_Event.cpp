//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\LOAD.h" 
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
	wtLine1 = new Wt::WText(" ");
	wtLine2 = new Wt::WText(" ");
	wtLine3 = new Wt::WText(" ");
	wtLine4 = new Wt::WText(" ");
		
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
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtLine1)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtLine2)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtLine3)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtLine4)));
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
	
	wtStatus->setText(" ");
	wtLine1->setText(" ");
	wtLine2->setText(" ");
	wtLine3->setText(" ");
	wtLine4->setText(" ");
	std::string sTeamID;

	unsigned int iSaveReturn = 0;
	

	unsigned long iTimes[RankRowStamps] = {0};
	unsigned long iTimesBestRun[RankRowStamps] = { 0 };

	std::string sReturn;

	if (Bro->A_getRankMode(iEventNr) > 10 && !WR->WA_Admin)
	{
		Rank->WRefresh();
		MISEA("Event Over");		
		return;
	}

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
		case 13: sReturn = WR->Kalk_Event13(iTimes); break;
		case 14: sReturn = WR->Kalk_Event14(iTimes); break;
		case 15: sReturn = WR->Kalk_Event15(iTimes); break;
		case 16: sReturn = WR->Kalk_Event16(iTimes); break;
		case 17: sReturn = WR->Kalk_Event17(iTimes); break;
		case 18: sReturn = WR->Kalk_Event18(iTimes); break;
		case 19: sReturn = WR->Kalk_Event19(iTimes); break;
	}
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{	
		switch (iEventNr)
		{
		case 8:
			sTeamID = WR->GetTeamID();
			if (Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtLine1->setText("Time: " + sTime(iTimes[0]));
			wtLine2->setText("Power: " + std::to_string(iTimes[1]));
			break;
		case 9:
			WR->AddPlayers9();
			WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + "_" + WR->getMapName() + "_" + std::to_string(WR->getReplayHash()) + ".pmv");
			wtStatus->setText("<h3>Nice run :-)</h3> ");
			break;

		case 10:
			sTeamID = WR->GetTeamID();
			if (Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes) == 1)
				WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + WR->GetTeamID() + ".pmv");

			wtStatus->setText("<h3>Hello there " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
			wtLine1->setText("Time: " + sTime(iTimes[0]));
			wtLine2->setText("Points: " + std::to_string(iTimes[1]));
			break;

		case 11:
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1) WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + WR->GetPlayerName(WR->getPMVPlayerID()) + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run " + sTeamID + ": -) </h3> ");
			else wtStatus->setText("<h3>Nice run " + sTeamID + ", but not better </h3> ");

			wtLine1->setText("This run Time: " + sTime(iTimes[0]));
			if (iSaveReturn != 1)wtLine2->setText("Best run Time: " + sTime(iTimesBestRun[0]));
			wtLine3->setText("This run Deck Level: " + std::to_string(iTimes[2]));
			if (iSaveReturn != 1)wtLine4->setText("Best run Deck Level: " + std::to_string(iTimesBestRun[2]));
			break;
		case 12:
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			if (Bro->A_AddPlayer(iEventNr, sTeamID, 0, iTimes) == 1)
				WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");

			wtStatus->setText("<h3>Hello there " + sTeamID + ", nice run : -) </h3> ");
			break;
		case 13: //BOT9
			sTeamID = WR->GetTeamID();
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run : -) (Ranking shows +/- one rank compared to yours) </h3> ");
			else wtStatus->setText("<h3>Nice run, but not faster then your currend one (Ranking shows +/- one rank compared to yours) </h3> ");
			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			wtLine2->setText("Spells: " + std::to_string(iTimes[1]));
			wtLine3->setText("Units: " + std::to_string(iTimes[2]));

			wtLine4->setText("Your best run (" + sTimeFull(iTimesBestRun[0]) + ") is in the top " + getRankBracket(iTimesBestRun[RankRowStamps - 1], Bro->A_GetTotalPlayers(iEventNr)));
			break;
		case 14: //BOT10
		case 16: //BOT10
			sTeamID = Bro->GetTeamName(WR->GetTeamID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run : -) </h3> ");
			else wtStatus->setText("<h3>Nice run, but not faster then your currend one </h3> ");
			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			wtLine2->setText("Your best run " + sTimeFull(iTimesBestRun[0]));			
			break;
		case 15: //Canyon
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run : -) (Ranking shows +/- one rank compared to yours) </h3> ");
			else wtStatus->setText("<h3>Nice run, but not faster then your currend one (Ranking shows +/- one rank compared to yours) </h3> ");

			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			wtLine2->setText("Crystals: " + std::to_string(iTimes[2]));
			wtLine3->setText("Crystals Time: " + sTimeFull(iTimes[15]));
			wtLine4->setText("Your best run (" + sTimeFull(iTimesBestRun[0]) + ") is in the top " + getRankBracket(iTimesBestRun[RankRowStamps - 1], Bro->A_GetTotalPlayers(iEventNr)));

			//wtStatus->setText("<h3>Hello there " + sTeamID + ", nice run : -) </h3> ");
			break;

		case 17: //heart_of_trouble
			sTeamID = WR->GetPlayerName(WR->getPMVPlayerID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			//if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run : -)</h3> ");
			wtStatus->setText("<h3>Nice run :-) </h3> ");

			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			wtLine2->setText("Tickets: " + std::to_string(iTimes[1]));

			break;
		case 18: //4Player
			sTeamID = Bro->GetTeamName(WR->GetTeamID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run " + sTeamID + ": -) </h3> ");
			else wtStatus->setText("<h3>Nice run " + sTeamID + ", but not faster then your currend one </h3> ");

			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			wtLine2->setText("Power Dif: " + std::to_string(iTimes[2]));

			break;
		case 19: //BOT11
			sTeamID = Bro->GetTeamName(WR->GetTeamID());
			iSaveReturn = Bro->A_AddPlayer(iEventNr, sTeamID, WR->getReplayHash(), iTimes, iTimesBestRun);
			if (iSaveReturn == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNr) + "_" + sTeamID + ".pmv");
			if (iSaveReturn == 1)wtStatus->setText("<h3>Nice run : -) </h3> ");
			else wtStatus->setText("<h3>Nice run, but not faster then your currend one </h3> ");

			wtLine1->setText("Time: " + sTimeFull(iTimes[0]));
			//wtLine2->setText("Tickets: " + std::to_string(iTimes[1]));

			break;
		}	

	}

	//BOT 10 Doubble ranking in two Taps
	if (iEventNr == 14 || iEventNr == 16)
	{
		int iEventNrTemp;
		if (iEventNr == 14)
		{
			iEventNrTemp = 16;
			sReturn = WR->Kalk_Event16(iTimes);
		}
		else
		{
			iEventNrTemp = 14;
			sReturn = WR->Kalk_Event14(iTimes);
		}
		
		if (sReturn == "")if (Bro->A_AddPlayer(iEventNrTemp, Bro->GetTeamName(WR->GetTeamID()), WR->getReplayHash(), iTimes, iTimesBestRun) == 1)WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(iEventNrTemp) + "_" + Bro->GetTeamName(WR->GetTeamID()) + ".pmv");
		
	}
	Rank->WRefresh();
	MISE;
}


std::string WEB_Event::getRankBracket(int rank, int totalPlayers) 
{
	if (rank <= totalPlayers * 0.25)
		return "25%";
	else if (rank <= totalPlayers * 0.50)
		return "50%";
	else if (rank <= totalPlayers * 0.75)
		return "75%";
	else
		return "100%";
}