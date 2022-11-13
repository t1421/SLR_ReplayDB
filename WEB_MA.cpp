#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_MA.h"
#include "WEB_Replay.h"

broker *(WEB_MA::Bro) = NULL;

WEB_MA::WEB_MA(WEB_Replay *WR_):WR(WR_)
{
	MISS;

	cMain = new WContainerWidget();	
	wtStatus = new WText();
	
	MISD("#1");

	cMain->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)));

	MISE;
}



void WEB_MA::WRefresh()
{
	MISS;
	string sReturn = WR->BOT1();
	
	if(sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>"); 
	else wtStatus->setText("<h3> The restult is: " + to_string(WR->CountActions()) + "</h3>");
	
	MISE;
}