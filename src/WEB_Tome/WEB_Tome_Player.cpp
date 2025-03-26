//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WTable.h>
#include <Wt/WLineEdit.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WBreak.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>


broker *(WEB_Tome_Player::Bro) = NULL;

WEB_Tome_Player::WEB_Tome_Player(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	wtGameID = new Wt::WText("");
	wtPlayerID = new Wt::WText("");
	cMain = new Wt::WContainerWidget();
	wtBooster = new Wt::WTable();
	wtHistory = new Wt::WTable();
	wlFilter = new Wt::WLineEdit();
	waLink = new Wt::WAnchor();
	waLink->setText("<h5> Your Player Link </h5>");

	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	MISD("#0");

	wlFilter->setWidth(Card_Size_X * 9);
	
	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPlayerID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
	

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtBooster)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtHistory)));
	
	MISD("#2");
	
	wfuDropZone->setFilters(".pmv");

	wfuDropZone->changed().connect([=]
	{
		MISD("#changed");
		wfuDropZone->upload();
		wtStatus->setText("New File \n");
	});
	wfuDropZone->fileTooLarge().connect([=]
	{
		MISD("#fileTooLarge");
		wtStatus->setText("File is too large. \n");
	});

	wfuDropZone->uploaded().connect([=]
	{
		if (Con->BroGameID == -1)
		{
			MISEA("WTF !!!");
			return;
		}

		MISD("#uploaded");
		wtStatus->setText("Upload done \n");
		
		if (WA->NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			switch (WA->TomeAnalyser(new Wt::WTable(), Con->BroGameID))
			{
			case 0: wtStatus->setText("<h3 style='color:Green;'>All OK</h3>");
				break;
			case 1: wtStatus->setText("<h3 style='color:Tomato;'>Error: Could not match Players</h3>");
				break;
			case 2: wtStatus->setText("<h3 style='color:Tomato;'>Error: A not allowed Card was player</h3>");
				break;
			}
		}

	});

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

	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	wtPlayerID->setText("<h4> Player ID: " + playerID + "</h4>");
	std::stringstream sLink;
	sLink << Bro->L_getWebTome() << "?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID + "&playerID=" + playerID;
	waLink->setLink(Wt::WLink(sLink.str()));

	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	for (unsigned int i = 0; i < EnumBoosters.size(); i++)if (EnumBoosters[i].first == "-3")FreeBoosterIndex = i;

	wtHistory->clear();
	wtBooster->clear();
	MISD("#0");
	Con->DrawBooster(wtHistory, Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters, false);
	MISD("#1");
	wtBooster->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Opened"))));
	wtBooster->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Total"))));
	
	
	for (unsigned int i = 0; i < EnumBoosters.size(); i++)
	{
		wtBooster->elementAt(0, i + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg(Bro->L_getBOOSTER_PATH() + EnumBoosters[i].first + ".png", Booster_Size_X, Booster_Size_Y)
		)));
		wtBooster->elementAt(1, i + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first))))));
		wtBooster->elementAt(2, i + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i])))));
		wtBooster->elementAt(3, i + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("Open"))));
		//wtBooster->elementAt(3, i + 1)->widget(0)->setWidth(Card_Size_X * 9 / EnumBoosters.size() + 1);

		if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first)
			+ Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[FreeBoosterIndex].first)
			>= Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i]
			+ Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[FreeBoosterIndex]
			//|| i == FreeBoosterIndex
			|| Bro->vTomeGames[Con->BroGameID]->bAllowOpening == false
			)wtBooster->elementAt(3, i + 1)->widget(0)->disable();

		dynamic_cast<Wt::WPushButton *>(wtBooster->elementAt(3, i + 1)->widget(0))->clicked().connect(std::bind([=]() {
			//Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.push_back(Bro->J_OpenBooster(EnumBoosters[i].first));
			Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.push_back(Bro->J_OpenBooster(EnumBoosters[i].first,
				Bro->vTomeGames[Con->BroGameID]->bNoDouble, Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters));

			if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iMaxBoosters[i] < Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->iOpenBoosterOfType(EnumBoosters[i].first))
				Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters[Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.size() - 1]->sType = "-3";
			Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters[Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters.size() - 1]->iLfdnr = Bro->vTomeGames[Con->BroGameID]->AllBoosters();
						
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			WRefresh();
			Bro->postChatEventMIS(std::to_string(Con->BroGameID), "booster");
		}));		

		wtBooster->elementAt(0, i + 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(1, i + 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(2, i + 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
		wtBooster->elementAt(3, i + 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

		if (i == FreeBoosterIndex)
		{			
			wtBooster->elementAt(3, i + 1)->removeWidget(wtBooster->elementAt(3, i + 1)->widget(0)); 
			wtBooster->moveColumn(i + 1, 1);	
		}
		
	}
	MISD("#2");


	for(unsigned int i = 0 ; i < wtBooster->columnCount() ; i++)
	wtBooster->columnAt(i)->setWidth(Card_Size_X * 9 / wtBooster->columnCount());

	wlFilter->setText(Con->BoosterToFilter(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters, "MyTome"));
	// Check Replay

	MISE;
}
