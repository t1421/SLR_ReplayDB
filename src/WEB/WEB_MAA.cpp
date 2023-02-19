//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_MAA.h"
#include "..\..\incl\WEB\WEB_Replay.h"

#include <Wt/WContainerWidget.h>

broker *(WEB_MAA::Bro) = NULL;

WEB_MAA::WEB_MAA(WEB_Replay *WR_): WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtStatus	= new Wt::WText(" ");
			
	MISD("#1");	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
		
	MISE;
}

void WEB_MAA::WRefresh()
{
	MISS;
#ifdef BOT1
	std::string sReturn = WR->BOT1();

	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		//wtStatus->setText("<h3> The restult is: " + std::to_string(WR->CountActions()) + "</h3>");
		std::string sRankName;
		switch (Bro->AddRankPlayer(BOT1LIST, WR->Player(), WR->CountActions(), sRankName))
		{
		case 5: //Slower

			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(WR->CountActions()) + " -> but more actions :-)</h3> ");
			break;
		case 9: //Same
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(WR->CountActions()) + " -> same action count :-)</h3> ");
			break;
		case 10: //Faster
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + std::to_string(WR->CountActions()) + " -> less actions then your last :-)</h3> ");
			break;
		case 15: //New Player
			wtStatus->setText("<h3>Welcome to the Leaderboard " + sRankName + ": " + std::to_string(WR->CountActions()) + " actions :-)</h3> ");
			break;
		default: //Should not happen
			wtStatus->setText("<h3>WHAT HAPPEND?</h3> ");
		}
		MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
#endif
	MISE;
}

