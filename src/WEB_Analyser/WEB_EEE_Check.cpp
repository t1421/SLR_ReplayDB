#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB_Analyser\WEB_EEE_Check.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WHBoxLayout.h>

broker *(WEB_EEE_Check::Bro) = NULL;

WEB_EEE_Check::WEB_EEE_Check(WEB_Analyser *WR_, unsigned int iEEE_NR_) : WR(WR_), EEENR(iEEE_NR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
		
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTime = new Wt::WText(" ");
	wtPower = new Wt::WText(" ");
	wtAddInfo = new Wt::WText(" ");
	
	MISD("#1");
	
	Rank = new WEB_Rank(WR,EEENR);
	
	MISD("#2");
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtAddInfo)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTime)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPower)));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Rank->cMain)));
	
	MISD("#3");
	Rank->WRefresh();

	MISE;
}

void WEB_EEE_Check::WRefresh()
{
	MISS;
	
	wtTime->setText(" ");
	wtAddInfo->setText(" ");
	wtPower->setText(" ");

	unsigned long iTimes[RankRowStamps] = {0};

	std::string sReturn;

	switch (EEENR)
	{
	case 0: Rank->WRefresh(); return;
	case 1: sReturn = WR->Kalk_EEE_Def(iTimes, "sss1.map"); break;
	case 2: sReturn = WR->Kalk_EEE_Def(iTimes, "sss2.map"); break;
	case 3: sReturn = WR->Kalk_EEE3(iTimes); break;
	case 4: sReturn = WR->Kalk_EEE_Def(iTimes, "sss4.map"); break;
	case 5: sReturn = WR->Kalk_EEE5(iTimes); break;
	case 6: sReturn = WR->Kalk_EEE_Def(iTimes, "sss6.map"); break;	
	case 7: sReturn = WR->Kalk_EEE7(iTimes); break;	
	}
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{	
		std::string sPlayer = WR->GetPlayerName(WR->getPMVPlayerID());
		if (Bro->AddPlayer(EEENR, sPlayer, WR->getReplayHash(), iTimes) == 1)
		{
			WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(EEENR) + "_" + sPlayer + ".pmv");
			Bro->ReCalTotalEEE();
		}
		
		wtStatus->setText("<h3>Hello there " + sPlayer + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");

		switch (EEENR)
		{
		case 2:
			wtAddInfo->setText("Score: " + std::to_string(iTimes[0] + iTimes[2]));
			break;
		case 3:
			wtAddInfo->setText("Buildings: " + std::to_string(iTimes[0]));
			break;
		case 5:
			wtAddInfo->setText("Units: " + std::to_string(iTimes[0]));
			break;
		case 7:
			wtAddInfo->setText("Score: " + std::to_string(iTimes[0]) + "/" + std::to_string(iTimes[1]));
			break;
		//default:
		//	wtTime->setText("Time: " + sTimeFull(iTimes[0]));
		}

		wtTime->setText("Time: " + sTimeFull(iTimes[0]));
		wtPower->setText("Power: " + std::to_string(iTimes[2]));

		
		

		//MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
	
	Rank->WRefresh();
	MISE;
}
