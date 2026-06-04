#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\DataTypes.h"
//#include "..\..\incl\Replay.h" 
//#include "..\..\incl\CardBaseSMJ.h" 
//#include "..\..\incl\LOAD.h" 

#include "..\..\incl\WEB_King\WEB_King_Player.h"
#include "..\..\incl\WEB_King\WEB_Container_King.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WGridLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WLength.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>



broker *(WEB_King_Player::Bro) = NULL;


WEB_King_Player::WEB_King_Player(WEB_Container_King*Con_, WEB_Analyser* WA_)
	: Con(Con_), WA(WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	
	MISD("#0");

	cMain = new Wt::WContainerWidget();
	//cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtPlayer = new Wt::WTable();

	MISD("#2");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPlayer)));
		
	MISD("#3");
	
	MISD("#4");

	
	WRefresh();

	MISE;
}

void WEB_King_Player::WRefresh()
{
	MISS;

	wtPlayer->clear();
	wtPlayer->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h4>"))));
	wtPlayer->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> W </h4>"))));
	wtPlayer->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> L </h4>"))));

	for (unsigned int i = 0; i < Bro->vKingPlayers.size(); i++)
	{
		wtPlayer->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->vKingPlayers[i].Name))));
		wtPlayer->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vKingPlayers[i].iWins)))));
		wtPlayer->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vKingPlayers[i].iLosses)))));
		wtPlayer->elementAt(i + 1, 1)->setStyleClass("green");
		wtPlayer->elementAt(i + 1, 2)->setStyleClass("red");		
	}

	wtPlayer->columnAt(0)->setWidth(150);
	wtPlayer->columnAt(1)->setWidth(50);
	wtPlayer->columnAt(2)->setWidth(50);


	MISE;
}

