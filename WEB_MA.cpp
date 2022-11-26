#define DF_Debug

#include "Broker.h"

#include "WEB_MA.h"
#include "WEB_Replay.h"

broker *(WEB_MA::Bro) = NULL;

WEB_MA::WEB_MA(WEB_Replay *WR_):WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	wtStatus = new Wt::WText();
	
	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));

	MISE;
}



void WEB_MA::WRefresh()
{
	MISS;
	std::string sReturn = WR->BOT1();
	
	if(sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>"); 
	else wtStatus->setText("<h3> The restult is: " + std::to_string(WR->CountActions()) + "</h3>");
	
	MISE;
}