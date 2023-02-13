#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_Analyser_Head.h"
#include "..\..\incl\WEB\WEB_Analyser_Deck.h"
#include "..\..\incl\WEB\WEB_Analyser_Acti.h"



broker *(WEB_Analyser::Bro) = NULL;

WEB_Analyser::WEB_Analyser(WEB_Replay *WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
	
	MISD("#1");

	Head = new WEB_Analyser_Head(WR_);
	Deck = new WEB_Analyser_Deck(WR_);
	Acti = new WEB_Analyser_Acti(WR_);
	

	MISD("#11");

	WEB_Toolbar::ToolBarButton(bToolbar.size(), "Head", *Head->cMain, Head);
	WEB_Toolbar::ToolBarButton(bToolbar.size(), "Deck", *Deck->cMain, Deck);
	WEB_Toolbar::ToolBarButton(bToolbar.size(), "Acti", *Acti->cMain, Acti);
	WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();

	MISE;
}



void WEB_Analyser::WRefresh()
{
	MISS;
	updateFrame();		
	MISE;
}