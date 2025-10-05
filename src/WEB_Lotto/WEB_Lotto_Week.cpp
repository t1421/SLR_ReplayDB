//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\Replay.h" 
#include "..\..\incl\CardBaseSMJ.h" 
#include "..\..\incl\LOAD.h" 

#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\WEB_Lotto\WEB_Lotto_Week.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WGridLayout.h>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WLength.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>

#define Card_Size_X 185 / 5
#define Card_Size_Y 255 / 5

broker *(WEB_Lotto_Week::Bro) = NULL;


WEB_Lotto_Week::WEB_Lotto_Week(WEB_Container_Lotto *Con_, LottoWeek *BroWeek_) 
	: Con(Con_), BroWeek(BroWeek_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	
	MISD("#0");

	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();
	wtPulls = new Wt::WTable();
	
	MISD("#11");
	wfuDropZone = new Wt::WFileUpload();
	wtReplayResultCard = new Wt::WTable();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();
	wtJoin = new Wt::WPushButton("Join with replay");

	unsigned int iCol = 0;
	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J->EnumBoosters;

	MISD("#2");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReplayResultCard)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtJoin)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPulls)));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISD("#3");
	
	MISD("#4");

	MISD("#4");
	wtJoin->clicked().connect(std::bind([=]() {
		MISD("Click wtJoin");
		BroWeek->JoinWeek(myPlayer);
		wtReplayResultCard->clear();
		wtStatus->setText("<h3 style='color:Green;'>Happy to have you :-)</h3>");
		wtJoin->disable();
		WRefresh();
	}));
	wtJoin->disable();

	MISD("#5");
	
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
		wtJoin->disable();
		MISD("#uploaded1");
		wtStatus->setText("Upload done \n");
		MISD("#uploaded2");
		wtReplayResultCard->clear();
		MISD("#uploaded3");
		
		if (WA->NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			/*
			if ((WA->R->DifficultyID != 2 && WA->R->DifficultyID != 3)
				|| WA->R->PlayModeID != 1
				|| WA->R->MapID > 100
				|| WA->R->MapID == 67) //tutorial
			{
				wtStatus->setText("<h3 style='color:Tomato;'>Error: You need to play Adv or Exp on a campain map</h3>");
				return;
			}
			*/
			if (!BroWeek->CheckPlayer(std::to_string(WA->getPMVPlayerID())))
			{
				wtStatus->setText("<h3 style='color:Tomato;'>Error: You already joind this week</h3>");
				return;
			}

			myPlayer = WA->getLottoPlayer();
			if(myPlayer->vSimpleDeck.size()!= 20)wtStatus->setText("<h3 style='color:Orange;'>Error: You dont have 20 unice Cards in your deck</h3>");
			else wtStatus->setText("<h3 style='color:Green;'>All OK -> Press Join</h3>");	
			
			//wtReplayResultCard
			DrawDeck(wtReplayResultCard, myPlayer, false);
			wtJoin->enable();

		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");	
	});
	
	WRefresh();

	MISE;
}

void WEB_Lotto_Week::WRefresh()
{
	MISS;

	unsigned int iPlayer = 0;
	unsigned int iStageRow = 0;
	unsigned int iSplit = 0;


	switch (BroWeek->iStatus)
	{
	case 0: break; //Hidden
	case 1:        //Active
		wtTabelle->clear();
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Player</h3>"))));
		wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Map</h3>"))));
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Deck</h3>"))));
		wtTabelle->elementAt(iStageRow, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Total BFP Pool: " + std::to_string(int(BroWeek->iBFP)) + "</h3>"))));
		wtTabelle->elementAt(0, 2)->setColumnSpan(5);
		wtTabelle->elementAt(0, 7)->setColumnSpan(5);
		for each(Lotto_Player *P in BroWeek->vPlayer)
			DrawDeck(wtTabelle, P, false);
		for (unsigned int iStage = 0; iStage < Bro->LottoStages.size(); iStage++)
		{
			iStageRow = wtTabelle->rowCount();
			wtTabelle->elementAt(iStageRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>Points " + std::to_string(Bro->LottoStages[iStage].second) + "</h4>"))));
			wtTabelle->elementAt(iStageRow, 0)->setColumnSpan(3);
			wtTabelle->elementAt(iStageRow, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>BFP: " + std::to_string(int(Bro->LottoStages[iStage].first * BroWeek->iBFP)) + "</h4>"))));
			wtTabelle->elementAt(iStageRow, 4)->setColumnSpan(5);
		}

		wfuDropZone->enable();
		break;
	case 2:        //Inactiv
	case 3:        //Pull
		//BroWeek->CalcPulls();
		///Calc Pulls + sort
		wtTabelle->clear();
		for (unsigned int iStage = 0; iStage < Bro->LottoStages.size(); iStage++)
		{
			//MISD("#####");
			//MISD(iStage);
			//MISD(Bro->LottoStages[iStage].second);
			
			iStageRow = wtTabelle->rowCount();
			wtTabelle->elementAt(iStageRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Points " + std::to_string(Bro->LottoStages[iStage].second) + "</h3>"))));
			wtTabelle->elementAt(iStageRow, 0)->setColumnSpan(3);

			for(; iPlayer < BroWeek->vPlayer.size() && BroWeek->vPlayer[iPlayer]->iPoints() >= Bro->LottoStages[iStage].second; iPlayer++)
				DrawDeck(wtTabelle, BroWeek->vPlayer[iPlayer], true);

			wtTabelle->elementAt(iStageRow, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>BFP Total: " + std::to_string(int(Bro->LottoStages[iStage].first * BroWeek->iBFP )) + "</h3>"))));
			wtTabelle->elementAt(iStageRow, 4)->setColumnSpan(5);

			//Berechnung des splits
			if (wtTabelle->rowCount() - iStageRow - 1 <= 0)iSplit = 1;
			else iSplit = wtTabelle->rowCount() - iStageRow - 1;
			wtTabelle->elementAt(iStageRow, 10)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Per Player: " + std::to_string(int(Bro->LottoStages[iStage].first * BroWeek->iBFP / iSplit)) + "</h3>"))));
			wtTabelle->elementAt(iStageRow, 10)->setColumnSpan(5);
		}
		//MISD("xxxxxxxxx");
		//NO prizes
		iStageRow = wtTabelle->rowCount();
		wtTabelle->elementAt(iStageRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>NO Prizes</h3>"))));
		for (; iPlayer < BroWeek->vPlayer.size(); iPlayer++)
			DrawDeck(wtTabelle, BroWeek->vPlayer[iPlayer], true);
		///for each Stage  (Draw Line)
		/// Each Plyer matching Stage (Draw Player)
		
		wfuDropZone->disable();
				
		break;

	default:
		break;
	}

	wtPulls->clear();
	if (BroWeek->vCardsPulled.size() > 0)
	{
		iStageRow = 0;
		wtPulls->elementAt(iStageRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>The Pulls</h3>"))));
		wtPulls->elementAt(iStageRow, 0)->setColumnSpan(2);

		if (BroWeek->iMapPull != 0)
		{
			wtPulls->elementAt(iStageRow, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>" + Con->getMapName(BroWeek->iMapPull) + "</h3>"))));
			wtPulls->elementAt(iStageRow, 5)->setColumnSpan(2);
			wtPulls->elementAt(iStageRow, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->L->sMAPPIC_PATH + "1" + std::to_string(BroWeek->iMapPull) + ".jpg", Card_Size_Y * 2, Card_Size_Y * 2))));
		}
		wtPulls->elementAt(iStageRow, 7)->setColumnSpan(6);
		for(unsigned int i = 0; i < BroWeek->vCardsPulled.size();i++)
		{
			if (i == 0 || i == 8)
			{
				iStageRow++;
			}
			wtPulls->elementAt(iStageRow, i % 8)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J->GetLottoImg(BroWeek->vCardsPulled[i], 1), Card_Size_X * 2.5, Card_Size_Y * 2.5))));
		}
	}



	MISE;
}

void WEB_Lotto_Week::DrawDeck(Wt::WTable *wtTabelle, Lotto_Player *Player, bool bColore)
{
	MISS;
	
	//MISD(Player->iPoints());
	unsigned int iRow = wtTabelle->rowCount();
	wtTabelle->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h5>" + Player->sPlayerName + "</h5>"))));
	if(bColore)wtTabelle->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h5>Points: " + std::to_string(Player->iPoints()) + "</h5>"))));
	if (bColore)wtTabelle->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->L->sMAPPIC_PATH + std::to_string(Player->iMapPoint) + std::to_string(Player->iMapID) + ".jpg", Card_Size_Y, Card_Size_Y))));
	else wtTabelle->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->L->sMAPPIC_PATH + "1" + std::to_string(Player->iMapID) + ".jpg", Card_Size_Y, Card_Size_Y))));
	for(unsigned int i = 0; i < Player->vSimpleDeck.size(); i++)
	{		
		if(bColore)wtTabelle->elementAt(iRow, i + 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J->GetLottoImg(Player->vSimpleDeck[i], Player->vPoints[i]), Card_Size_X, Card_Size_Y))));
		else wtTabelle->elementAt(iRow, i + 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J->GetLottoImg(Player->vSimpleDeck[i], 1), Card_Size_X, Card_Size_Y))));
	}	
	MISE;
}


