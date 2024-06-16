#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB_Analyser\WEB_EEE_Check.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>

broker *(WEB_EEE_Check::Bro) = NULL;

WEB_EEE_Check::WEB_EEE_Check(WEB_Analyser *WR_, unsigned int iEEE_NR_) : WR(WR_), EEENR(iEEE_NR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
		
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTime = new Wt::WText(" ");
	
	MISD("#1");
	
	Rank = new WEB_Rank(EEENR);
	
	MISD("#2");
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTime)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Rank->cMain)));
	
	MISD("#3");
	Rank->WRefresh();

	MISE;
}

void WEB_EEE_Check::WRefresh()
{
	MISS;
	
	wtTime->setText(" ");

	unsigned long iTimes[RankRowStamps] = {0};

	std::string sReturn;

	switch (EEENR)
	{
	case 0: sReturn = WR->Kalk_EEE0(iTimes); break;
	case 1: sReturn = WR->Kalk_EEE1(iTimes); break;
	case 2: sReturn = WR->Kalk_EEE2(iTimes); break;
	case 3: sReturn = WR->Kalk_EEE3(iTimes); break;
	case 4: sReturn = WR->Kalk_EEE4(iTimes); break;
	case 5: sReturn = WR->Kalk_EEE5(iTimes); break;
	case 6: sReturn = WR->Kalk_EEE6(iTimes); break;
	case 7: sReturn = WR->Kalk_EEE7(iTimes); break;	
	}
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		
		//iTimes[0] = WR->getPlaytime();		
		std::string sPlayer = WR->GetPlayerName(WR->getPMVPlayerID());
		if (Bro->AddPlayer(EEENR, sPlayer, WR->getReplayHash(), iTimes) == 1)
		{
			
			WR->SaveReplay(Bro->L_getPMV_WEB_PATH() + std::to_string(EEENR) + sPlayer + ".pmv");
		}

		wtStatus->setText("<h3>Hello there " + sPlayer + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
		wtTime->setText(sTime(iTimes[0]));

		//MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
	
	Rank->WRefresh();
	MISE;
}
