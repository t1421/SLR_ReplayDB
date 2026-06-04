#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\DataTypes.h"
//#include "..\..\incl\Replay.h" 
//#include "..\..\incl\CardBaseSMJ.h" 
#include "..\..\incl\LOAD.h" 

#include "..\..\incl\WEB_King\WEB_King_Game.h"
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


broker *(WEB_King_Game::Bro) = NULL;


WEB_King_Game::WEB_King_Game(WEB_Container_King*Con_, WEB_Analyser* WA_)
	: Con(Con_), WA(WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	
	MISD("#0");

	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtGames = new Wt::WTable();
	
	MISD("#2");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGames)));	
	
	MISD("#3");

	WRefresh();

	MISE;
}

void WEB_King_Game::WRefresh()
{
	MISS;

	Wt::WAnchor* waLink;

	wtGames->clear();	
	wtGames->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID </h4>"))));
	wtGames->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player 1 </h4>"))));
	wtGames->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player 2 </h4>"))));

	for (unsigned int i = 0; i < Bro->vKingGames.size(); i++)
	{
		wtGames->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->vKingGames[i].ReplayID))));
		wtGames->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->vKingGames[i].PlayerName1))));
		wtGames->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->vKingGames[i].PlayerName2))));
		if (Bro->vKingGames[i].PlayerName1 == Bro->vKingGames[i].PlayerWinner)
		{
			wtGames->elementAt(i + 1, 1)->setStyleClass("green");
			wtGames->elementAt(i + 1, 2)->setStyleClass("red");
		}
		else 
		{
			wtGames->elementAt(i + 1, 2)->setStyleClass("green");
			wtGames->elementAt(i + 1, 1)->setStyleClass("red");
		}

		if (Con->WA_Admin)
		{
			waLink = new Wt::WAnchor();
			waLink->setText("#");
			waLink->setLink(Wt::WLink(Bro->L->sPMV_KING_PATH + Bro->vKingGames[i].ReplayID + ".pmv"));			
			wtGames->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
		}
	}

	wtGames->columnAt(0)->setWidth(100);
	wtGames->columnAt(1)->setWidth(150);
	wtGames->columnAt(2)->setWidth(150);

	MISE;

}

