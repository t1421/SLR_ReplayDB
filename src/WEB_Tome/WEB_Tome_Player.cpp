#define DF_Debug

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
	wtReforge = new Wt::WTable();
	wtHistory = new Wt::WTable();
	wbReforge = new Wt::WPushButton("Reforge");
	wlFilter = new Wt::WLineEdit();
	waLink = new Wt::WAnchor();
	waLink->setText("<h5> Your Player Link </h5>");

	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	MISD("#0");

	wlFilter->setWidth(Card_Size_X * 9);
	wbReforge->setWidth(Card_Size_X);
	wbReforge->setHeight(Card_Size_Y);
	
	wtReforge->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
		DrawImg("./resources/Boosters/-91.png",Card_Size_X, Card_Size_Y))));	
	wtReforge->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetImage(0, 3, 3, 1, false), Card_Size_X, Card_Size_Y))));
	wtReforge->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetImage(0, 3, 3, 1, false), Card_Size_X, Card_Size_Y))));
	wtReforge->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetImage(0, 3, 3, 1, false), Card_Size_X, Card_Size_Y))));
	wtReforge->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetImage(0, 3, 3, 1, false), Card_Size_X, Card_Size_Y))));
	wtReforge->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbReforge)));
	wtReforge->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetImage(0, 3, 3, 1, false), Card_Size_X, Card_Size_Y))));
	
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
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReforge)));
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
	unsigned int RefrogeIndex;
	bool ReforgeOK;
	unsigned int iCol = 0;
	unsigned int iRow = 0;

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
	for (unsigned int i = 0; i < EnumBoosters.size(); i++)if (EnumBoosters[i].first == "-91")RefrogeIndex = i;

	wtBooster->clear();
	wtHistory->clear();
	MISD("#0");
	Con->DrawBooster(wtHistory, Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters, 1);
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
		wtBooster->elementAt(3, i + 1)->widget(0)->setWidth(Booster_Size_X);

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
				Bro->vTomeGames[Con->BroGameID]->bNoDoubleBooster, Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters));

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

		if (i == FreeBoosterIndex || i == RefrogeIndex)
		{			
			wtBooster->elementAt(3, i + 1)->removeWidget(wtBooster->elementAt(3, i + 1)->widget(0)); 
			wtBooster->moveColumn(i + 1, 1);	
		}
		
	}
	MISD("#2");


	for(unsigned int i = 0 ; i < wtBooster->columnCount() ; i++)
	wtBooster->columnAt(i)->setWidth(Card_Size_X * 9 / wtBooster->columnCount());

	wlFilter->setText(Con->BoosterToFilter(Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters, 1));
	
	//wtReforge->clear();
	if (Bro->vTomeGames[Con->BroGameID]->bAllowRefroging)
	{
		wtReforge->setHidden(false);
		MISD("#3 START");

		ReforgeOK = true;
		for (unsigned int i = 0; i < 4; i++)
			if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i]->cardId == 0)ReforgeOK = false;
		// Update Images
		wbReforge->setDisabled(!ReforgeOK);

		MISD("#3 Boosters");
		//set Click Actions		
		iRow = 0;
		for (auto B : Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->vBoosters)
		{
			iCol = 1;
			for (auto C : B->vCards)
			{
				if (C->reforged == 0 || C->reforged == 2)
				{
					MISD("STA" + std::to_string(iRow) + "#" + std::to_string(iCol) + "#" + std::to_string(wtHistory->elementAt(iRow, iCol)->count()));
					//wtHistory->elementAt(iRow, iCol)->clicked().connect(std::bind([=]() {
					dynamic_cast<Wt::WImage*>(wtHistory->elementAt(iRow, iCol)->widget(0))->clicked().connect(std::bind([=]() {
						//dynamic_cast<Wt::WPushButton *>(wtHistory->elementAt(iRow, iCol)->widget(0))->clicked().connect(std::bind([=]() {
						MISD("dynamic_cast");
						//Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i]->cardId
						switch (C->reforged)
						{
						case 0:
							for (unsigned int i = 0; i < 4; i++)
								if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i]->cardId == 0)
								{
									MISD("case 0:")
									Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i] = C;
									C->reforged = 2;
									break;
								}
							break;
						case 2:
							for (unsigned int i = 0; i < 4; i++)
								if (Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i]->cardId == C->cardId && C->reforged == 2)
								{
									MISD("case 2:");
									Bro->vTomeGames[Con->BroGameID]->vPlayer[PlayerIndex]->ReforgeBooster->vCards[i] = new SMJCard(0);
									C->reforged = 0;
									break;
								}
							break;
						}
						
						Bro->vTomeGames[Con->BroGameID]->bSaveGame();
						WRefresh();
						}));


					if (C->reforged == 2)
						wtHistory->elementAt(iRow, iCol)->setStyleClass("yReforge");

					

				}
				iCol++;
			}

			iRow++;
		}

	}
	else wtReforge->setHidden(true);

	//Bro->postChatEventMIS(std::to_string(Con->BroGameID), "booster");

	MISE;
}
