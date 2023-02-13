#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser_Head.h"
#include "..\..\incl\WEB\WEB_Replay.h"

#include <Wt/WContainerWidget.h>

broker *(WEB_Analyser_Head::Bro) = NULL;

WEB_Analyser_Head::WEB_Analyser_Head(WEB_Replay *WR_): WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	//wtStatus	= new Wt::WText(" ");
			
	MISD("#1");	
	//cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
		
	MISE;
}

void WEB_Analyser_Head::WRefresh()
{
	MISS;
	

	MISE;
}

