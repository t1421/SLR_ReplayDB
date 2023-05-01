//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB\WEB_MDA.h"
#include "..\..\incl\WEB\WEB_Analyser.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>


broker *(WEB_MDA::Bro) = NULL;

WEB_MDA::WEB_MDA(WEB_Analyser *WA_) : WA(WA_)
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

void WEB_MDA::WRefresh()
{
	MISS;
	
	double iPoints;

	wtTabelle->clear();
	std::string sReturn = WA->Check_BOT3();
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		iPoints = WA->Kalk_BOT3(wtTabelle);
		MISD("#2#" + std::to_string(iPoints));
		std::string sRankName;
		switch (Bro->AddRankPlayer(VornskrLIST, WA->getPMVPlayerID(), iPoints, sRankName))
		{
		case 5: //Slower
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(iPoints) + " -> but slower :-)</h3> ");
			break;
		case 9: //Same
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(iPoints) + " -> same time as before :-)</h3> ");
			break;
		case 10: //Faster
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(iPoints) + " -> faster then your last :-)</h3> ");
			break;
		case 15: //New Player
			wtStatus->setText("<h3>Welcome to the Leaderboard " + sRankName + ": " + std::to_string(iPoints)  + " :-)</h3> ");
			break;
		default: //Should not happen
			wtStatus->setText("<h3>WHAT HAPPEND?</h3> ");
		}		
		//MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
	
	MISE;
}
