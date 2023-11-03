#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WLineEdit.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>


broker *(WEB_Tome_Player::Bro) = NULL;

WEB_Tome_Player::WEB_Tome_Player(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	wtBooster = new Wt::WTable();
	wtHistory = new Wt::WTable();
	wlFilter = new Wt::WLineEdit();

	//Wt::WVBoxLayout *wlLayou = new Wt::WVBoxLayout();

	MISD("#0");

	//cMain->setLayout(std::unique_ptr<Wt::WVBoxLayout>(std::move(wlLayou)));
	wlFilter->setWidth(Card_Size_X * 9);
	
	MISD("#1");

	//wlLayou->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtBooster)));
	//wlLayou->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	//wlLayou->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtHistory)));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtBooster)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtHistory)));
	
	
	MISD("#2");

	MISD("#3");

	//WRefresh();

	MISE;
}

void WEB_Tome_Player::WRefresh()
{
	MISS;

	unsigned int PlayerIndex;
	unsigned int FreeBoosterIndex;
	std::string playerID = Con->getPlayerID();
		
	for (PlayerIndex = 0; PlayerIndex < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); PlayerIndex++)
		if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->sPlayerID == playerID)break;
	if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->sPlayerID != playerID)
	{
		MISEA("V2 !!!")
			return;
	}

	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	for (unsigned int i = 0; i < EnumBoosters.size(); i++)if (EnumBoosters[i].first == "-3")FreeBoosterIndex = i;

	wtHistory->clear();
	wtBooster->clear();

	Con->DrawBooster(wtHistory, Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters);

	for (unsigned int i = 0; i < EnumBoosters.size(); i++)
	{
		wtBooster->elementAt(0, i)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg(Bro->L_getBOOSTER_PATH() + EnumBoosters[i].first + ".png", Booster_Size_X, Booster_Size_Y)
		)));
		wtBooster->elementAt(1, i)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first))))));
		wtBooster->elementAt(2, i)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i])))));
		wtBooster->elementAt(3, i)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("Open"))));
		wtBooster->elementAt(3, i)->widget(0)->setWidth(Card_Size_X * 9 / EnumBoosters.size());

		if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first)
			+ Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[FreeBoosterIndex].first)
			>= Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i]
			+ Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[FreeBoosterIndex]
			|| i == FreeBoosterIndex
			|| Bro->vTomeGames[Con->BroGameID]->bAllowOpening == false
			)wtBooster->elementAt(3, i)->widget(0)->disable();

		dynamic_cast<Wt::WPushButton *>(wtBooster->elementAt(3, i)->widget(0))->clicked().connect(std::bind([=]() {
			Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.push_back(Bro->J_OpenBooster(EnumBoosters[i].first));

			if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i] < Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first))
				Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters[Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.size() - 1]->sType = "-3";
			Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters[Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.size() - 1]->iLfdnr = Bro->vTomeGames[Con->BroGameID]->AllBoosters();
						
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			WRefresh();
		}));

		wtBooster->elementAt(0, i)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(1, i)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(2, i)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(3, i)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	}

	wlFilter->setText(Con->BoosterToFilter(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters, "MyTome"));
	// Check Replay

	MISE;
}
