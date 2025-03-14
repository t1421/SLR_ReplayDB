//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\Replay.h" 

#include "..\..\incl\WEB_Tome\WEB_Tome_Admin.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

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
#include <Wt/WRadioButton.h>


broker *(WEB_Tome_Admin::Bro) = NULL;

struct WEB_Tome_Player
{
	Wt::WText *wtPlayerID;
	Wt::WLineEdit *wlPlayerName;
	Wt::WLineEdit *iMaxBoosters[NumBoostersTypes];
	Wt::WPushButton *wbDel;
	Wt::WPushButton *wbMes;
	Wt::WTableRow *wrRow;

	WEB_Tome_Player(Tome_Player *Player)
	{
		wrRow = new Wt::WTableRow();
		wtPlayerID = new Wt::WText(Player->sPlayerID);
		wlPlayerName = new Wt::WLineEdit(Player->sPlayerName);
		wbDel = new Wt::WPushButton("Del");
		wbMes = new Wt::WPushButton("Mes");
		for (unsigned int i = 0; i < NumBoostersTypes; i++)
			iMaxBoosters[i] = new Wt::WLineEdit(std::to_string(Player->iMaxBoosters[i]));
	};
	void FILL()
	{
		wrRow->elementAt(0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPlayerID)));
		wrRow->elementAt(1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlPlayerName)));
		for (unsigned int i = 0; i < NumBoostersTypes; i++)
		{
			wrRow->elementAt(2 + i)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(iMaxBoosters[i])));
		}
		wrRow->elementAt(NumBoostersTypes + 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbDel)));
		wrRow->elementAt(NumBoostersTypes + 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbMes)));
	};
};

WEB_Tome_Admin::WEB_Tome_Admin(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	waLink = new Wt::WAnchor();
	waLink->setText("<h5> Your Admin Link </h5>");

	MISD("#0");

	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();

	wcShowPlayers = new Wt::WCheckBox("Show Players");
	wcShowBoosters = new Wt::WCheckBox("Show Boosters");
	wcShowCards = new Wt::WCheckBox("Show Cards");
	wcShowBoostersOfPlayer = new Wt::WCheckBox("Show Boosters per Player");
	wcAllowOpening = new Wt::WCheckBox("Allow Opening Booster");
	wcNoDouble = new Wt::WCheckBox("No Duplicate Cards");

	wtGameID = new Wt::WText("");
	wtAdminID = new Wt::WText("");

	wbSave = new Wt::WPushButton("Save");
	wbAddPlayer = new Wt::WPushButton("Add Player");

	wcShowCardsUR = new Wt::WCheckBox("UR");
	wcShowCardsR = new Wt::WCheckBox("R");
	wcShowCardsUC = new Wt::WCheckBox("UC");
	wcShowCardsC = new Wt::WCheckBox("C");

	gbCardOrder = std::make_shared<Wt::WButtonGroup>();
	
	MISD("#11");
	wfuDropZone = new Wt::WFileUpload();
	wtReplayResultCard = new Wt::WTable();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	unsigned int iCol = 0;
	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");

	MISD("#2");

	//TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))), 0, 0);
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	//TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Admin ID: </h4>"))), 1, 0);
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtAdminID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcAllowOpening)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowPlayers)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowBoosters)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowCards)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowCardsUR)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowCardsR)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowCardsUC)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowCardsC)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	gbCardOrder->addButton(cMain->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>("Colour")), 0);
	gbCardOrder->addButton(cMain->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>("Rarity")), 1);
	gbCardOrder->addButton(cMain->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>("ID")), 2);
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowBoostersOfPlayer)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcNoDouble)));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbAddPlayer)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbSave)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReplayResultCard)));
	
	MISD("#3");
	wcShowPlayers->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowPlayers = wcShowPlayers->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcShowBoosters->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowBoosters = wcShowBoosters->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcShowCards->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowCards = wcShowCards->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcShowBoostersOfPlayer->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowBoostersOfPlayer = wcShowBoostersOfPlayer->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcAllowOpening->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bAllowOpening = wcAllowOpening->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcNoDouble->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bNoDouble = wcNoDouble->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));

	wcShowCardsUR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowCardsUR = wcShowCardsUR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	wcShowCardsR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowCardsR = wcShowCardsR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	wcShowCardsUC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowCardsUC = wcShowCardsUC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	wcShowCardsC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowCardsC = wcShowCardsC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));

	
	gbCardOrder->checkedChanged().connect(std::bind([=](Wt::WRadioButton* selection) {
		Bro->vTomeGames[Con->BroGameID]->iCardOrder = gbCardOrder->selectedButtonIndex();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}, std::placeholders::_1));

	wbSave->clicked().connect(std::bind([=]() {
		
		TabelToBro();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		//WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "player");
		FixTable();		
	}));

	wbAddPlayer->clicked().connect(std::bind([=]() {
		TabelToBro();
		Bro->vTomeGames[Con->BroGameID]->AddPlayer();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		FixTable();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "player",
			Bro->vTomeGames[Con->BroGameID]->vPlayer[Bro->vTomeGames[Con->BroGameID]->vPlayer.size() - 1]->sPlayerID);
	}));

	MISD("#4");


	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayerID"))));	

	wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player Name"))));
	wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Add"))));
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Rem"))));

	for (unsigned int i = 0; i < EnumBoosters.size(); i++)
	{
		wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg(Bro->L_getBOOSTER_PATH() + EnumBoosters[i].first + ".png", Booster_Size_X, Booster_Size_Y)
		)));

		wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("+"))));
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(1, iCol)->widget(0))->setWidth(Booster_Size_X * 1.5);
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(1, iCol)->widget(0))->clicked().connect(std::bind([=]() {
			for each(WEB_Tome_Player* iWTP in Tabel_Player)
			{
				iWTP->iMaxBoosters[i]->setText(
					std::to_string(atoi(WSTRINGtoSTRING(iWTP->iMaxBoosters[i]->text()).c_str()) + 1));
			}
			TabelToBro();
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			Bro->postChatEventMIS(std::to_string(Con->BroGameID), "player");
			FixTable();
		}));

		wtTabelle->elementAt(2, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("-"))));
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(2, iCol)->widget(0))->setWidth(Booster_Size_X * 1.5);
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(2, iCol)->widget(0))->clicked().connect(std::bind([=]() {
			for each(WEB_Tome_Player* iWTP in Tabel_Player)
			{
				if(atoi(WSTRINGtoSTRING(iWTP->iMaxBoosters[i]->text()).c_str()) - 1 >= 0)
					iWTP->iMaxBoosters[i]->setText(
						std::to_string(atoi(WSTRINGtoSTRING(iWTP->iMaxBoosters[i]->text()).c_str()) - 1));
			}
			TabelToBro();
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			Bro->postChatEventMIS(std::to_string(Con->BroGameID), "player");
			FixTable();
		}));

		iCol++;

	}
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Delete"))));
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Mesage"))));

	MISD("#4");

	wtTabelle->columnAt(1)->setWidth(160);

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
		if (Con->BroGameID == -1)
		{
			MISEA("WTF !!!");
			return;
		}
		
		MISD("#uploaded");
		wtStatus->setText("Upload done \n");
		wtReplayResultCard->clear();

		if (WA->NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			switch (WA->TomeAnalyser(wtReplayResultCard, Con->BroGameID))
			{
			case 0: wtStatus->setText("<h3 style='color:Green;'>All OK</h3>");	
				break;
			case 1: wtStatus->setText("<h3 style='color:Tomato;'>Error: Could not match Players</h3>");
				break;
			case 2: wtStatus->setText("<h3 style='color:Tomato;'>Error: A not allowed Card was player</h3>");
				break;
			}	
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");	
	});
	

	MISE;
}

void WEB_Tome_Admin::WRefresh()
{
	MISS;

	if (Con->BroGameID == -1)
	{
		MISEA("WTF !!!");
		return;
	}

	//unsigned int iCol = 0;
	//std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	//std::vector<WEB_Tome_Player *> Tabel_Player;

	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	wtAdminID->setText("<h4> Admin ID: " + Bro->vTomeGames[Con->BroGameID]->sAdminID + "</h4>");
	std::stringstream sLink; 
	sLink<<WebTome<<"?gameID="<<Bro->vTomeGames[Con->BroGameID]->sGameID<<"&adminID="<<Bro->vTomeGames[Con->BroGameID]->sAdminID;
	waLink->setLink(Wt::WLink(sLink.str()));

	wcShowPlayers->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowPlayers);
	wcShowBoosters->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowBoosters);
	wcShowCards->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowCards);
	wcShowBoostersOfPlayer->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowBoostersOfPlayer);
	wcAllowOpening->setChecked(Bro->vTomeGames[Con->BroGameID]->bAllowOpening);
	wcNoDouble->setChecked(Bro->vTomeGames[Con->BroGameID]->bNoDouble);

	wcShowCardsUR->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowCardsUR);
	wcShowCardsR->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowCardsR);
	wcShowCardsUC->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowCardsUC);
	wcShowCardsC->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowCardsC);
	
	gbCardOrder->setCheckedButton(gbCardOrder->button(Bro->vTomeGames[Con->BroGameID]->iCardOrder));

	FixTable();

	MISE;
}

void WEB_Tome_Admin::FixTable()
{	
	MISS;
	bool bFound;

	//Add New 
	for each(Tome_Player* iTP in Bro->vTomeGames[Con->BroGameID]->vPlayer)
	{
		bFound = false;
		for each(WEB_Tome_Player* iWTP in Tabel_Player)
			if (iTP->sPlayerID == iWTP->wtPlayerID->text())
			{
				bFound = true;
				break;
			}
		if (bFound == true)continue;
		else
		{
			Tabel_Player.push_back(new WEB_Tome_Player(iTP));	
			wtTabelle->insertRow(wtTabelle->rowCount(), std::unique_ptr<Wt::WTableRow>(std::move(Tabel_Player[Tabel_Player.size() - 1]->wrRow)));
			Tabel_Player[Tabel_Player.size() - 1]->FILL();
			Tabel_Player[Tabel_Player.size() - 1]->wbDel->clicked().connect(std::bind([=]() {
				for (std::vector<Tome_Player*>::iterator it = Bro->vTomeGames[Con->BroGameID]->vPlayer.begin(); it != Bro->vTomeGames[Con->BroGameID]->vPlayer.end();)
					if (iTP->sPlayerID == (*it)->sPlayerID)
					{
						Bro->vTomeGames[Con->BroGameID]->vPlayer.erase(it);						
					}
					else  ++it;

				Bro->vTomeGames[Con->BroGameID]->bSaveGame();
				FixTable();
				Bro->postChatEventMIS(std::to_string(Con->BroGameID), "player");
			}));

			Tabel_Player[Tabel_Player.size() - 1]->wbMes->clicked().connect(std::bind([=]() {
				Wt::WApplication::instance()->doJavaScript(Wt::WApplication::instance()->javaScriptClass() + ".CopyToClip('" +
					"Hello " + iTP->sPlayerName + ", " +
					"welcome to the Tome Fight! The GameID is: " + Bro->vTomeGames[Con->BroGameID]->sGameID + " " +
					"and you PlayerID is: " + iTP->sPlayerID + " " +
					"But you can just use this link: " +
					WebTome + "?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID + "&playerID=" + iTP->sPlayerID +
					"');");
			}));
		}		
	}
	MISD("###");
	//remove Dell
	for (std::vector<WEB_Tome_Player*>::iterator it= Tabel_Player.begin(); it!= Tabel_Player.end();)
	{
		MISD(WSTRINGtoSTRING( (*it)->wtPlayerID->text()));
		bFound = false;
		for each(Tome_Player* iTP in Bro->vTomeGames[Con->BroGameID]->vPlayer)
			if (iTP->sPlayerID == (*it)->wtPlayerID->text())
			{
				bFound = true;
				break;
			}
		if (bFound == false)
		{
			wtTabelle->removeRow((*it)->wrRow->rowNum());
			it = Tabel_Player.erase(it);			
		}
		else  ++it;
	}
	MISE;
}

void WEB_Tome_Admin::TabelToBro()
{
	MISS;
	int iTemp;
	for each(WEB_Tome_Player* iWTP in Tabel_Player)
	{
		//MISD(WSTRINGtoSTRING(iWTP->wlPlayerName->text()));
		for each (Tome_Player* iTP in Bro->vTomeGames[Con->BroGameID]->vPlayer)
		{
			//MISD(iTP->sPlayerName);
			if (iTP->sPlayerID == iWTP->wtPlayerID->text())
			{
				//MISD("XX")
				iTP->sPlayerName = WSTRINGtoSTRING(iWTP->wlPlayerName->text());
				for (unsigned int j = 0; j < NumBoostersTypes; j++)
				{
					iTemp = std::atoi(WSTRINGtoSTRING(iWTP->iMaxBoosters[j]->text()).c_str());
					if (iTemp < 0)iTemp = 0;
					iTP->iMaxBoosters[j] = iTemp;
				}
					
				
			}
		}
	}
	MISE;
}