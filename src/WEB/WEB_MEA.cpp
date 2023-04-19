//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB\WEB_MEA.h"
#include "..\..\incl\WEB\WEB_Analyser.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>


broker *(WEB_MEA::Bro) = NULL;

WEB_MEA::WEB_MEA(WEB_Analyser *WA_) : WA(WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	
		
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTabelle   = new Wt::WTable();
	
	MISD("#1");
	
	
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	MISD("#2");
	cMain->setContentAlignment(Wt::AlignmentFlag::Left);
	
	MISE;
}

void WEB_MEA::WRefresh()
{
	MISS;
	
	double iPoints;

	wtTabelle->clear();
	std::string sReturn = WA->Kalk_BOT4(wtTabelle);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		//iPoints = WA->Kalk_BOT4(wtTabelle);
		iPoints = WA->getPlaytime();
		MISD("#2#" + std::to_string(iPoints));
		std::string sRankName;
		switch (Bro->AddRankPlayer(BOT4LIST, WA->getPMVPlayerID(), iPoints, sRankName))
		{
		case 5: //Slower
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iPoints) + " -> but slower :-)</h3> ");
			break;
		case 9: //Same
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iPoints) + " -> same time as before :-)</h3> ");
			break;
		case 10: //Faster
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iPoints) + " -> faster then your last :-)</h3> ");
			break;
		case 15: //New Player
			wtStatus->setText("<h3>Welcome to the Leaderboard " + sRankName + ": " + sTime(iPoints)  + ":-)</h3> ");
			break;
		default: //Should not happen
			wtStatus->setText("<h3>WHAT HAPPEND?</h3> ");
		}		
		//MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
	
	MISE;
}
