#define DF_Debug

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


broker *(WEB_Tome_Admin::Bro) = NULL;

struct WEB_Tome_Player
{
	Wt::WText *wtPlayerID;
	Wt::WLineEdit *wlPlayerName;
	Wt::WLineEdit *iMaxBoosters[NumBoostersTypes];
	Wt::WPushButton *wbSave;
	Wt::WPushButton *wbDel;
	Wt::WPushButton *wbMes;

	WEB_Tome_Player(Tome_Player *Player)
	{
		wtPlayerID = new Wt::WText(Player->sPlayerID);
		wlPlayerName = new Wt::WLineEdit(Player->sPlayerName);
		for (unsigned int i = 0; i < NumBoostersTypes; i++)
			iMaxBoosters[i] = new Wt::WLineEdit(std::to_string(Player->iMaxBoosters[i]));
		wbSave = new Wt::WPushButton("Save");
		wbDel = new Wt::WPushButton("Del");
		wbMes = new Wt::WPushButton("Mes");
	};
};

WEB_Tome_Admin::WEB_Tome_Admin(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	MISD("#0");

	cMain = new Wt::WContainerWidget();
	//Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	//cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	MISD("#1");

	wtTabelle = new Wt::WTable();

	wcShowPlayers = new Wt::WCheckBox("Show Players");
	wcShowBoosters = new Wt::WCheckBox("Show Boosters");
	wcShowBoostersOfPlayer = new Wt::WCheckBox("Show Boosters per Player");
	wcAllowOpening = new Wt::WCheckBox("Allow Opening Booster");

	wtGameID = new Wt::WText("");
	wtAdminID = new Wt::WText("");

	wbAddPlayer = new Wt::WPushButton("Add Player");

	MISD("#11");
	wfuDropZone = new Wt::WFileUpload();
	wtReplayResultCard = new Wt::WTable();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	MISD("#2");

	//TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))), 0, 0);
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	//TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Admin ID: </h4>"))), 1, 0);
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtAdminID)));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcAllowOpening)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowPlayers)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowBoosters)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowBoostersOfPlayer)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbAddPlayer)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReplayResultCard)));
	

	MISD("#3");
	wcShowPlayers->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowPlayers = wcShowPlayers->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
	}));
	wcShowBoosters->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowBoosters = wcShowBoosters->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
	}));
	wcShowBoostersOfPlayer->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowBoostersOfPlayer = wcShowBoostersOfPlayer->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
	}));
	wcAllowOpening->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bAllowOpening = wcAllowOpening->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
	}));
	wbAddPlayer->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->AddPlayer();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
	}));

	

	MISD("#4");

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
			if (WA->TomeAnalyser(wtReplayResultCard, Con->BroGameID ))wtStatus->setText("<h3 style='color:Tomato;'>Error: A not allowed Card was player</h3>");
			else wtStatus->setText("<h3 style='color:Green;'>All OK</h3>");			
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

	unsigned int iCol = 0;
	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	std::vector<WEB_Tome_Player *> Tabel_Player;

	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	wtAdminID->setText("<h4> Admin ID: " + Bro->vTomeGames[Con->BroGameID]->sAdminID + "</h4>");

	wcShowPlayers->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowPlayers);
	wcShowBoosters->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowBoosters);
	wcShowBoostersOfPlayer->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowBoostersOfPlayer);
	wcAllowOpening->setChecked(Bro->vTomeGames[Con->BroGameID]->bAllowOpening);

	wtTabelle->clear();

	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayerID"))));
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player Name"))));

	for (unsigned int i = 0; i < EnumBoosters.size(); i++)
	{
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg(Bro->L_getBOOSTER_PATH() + EnumBoosters[i].first + ".png", Booster_Size_X, Booster_Size_Y)
		)));
		
	}
	

	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Save"))));
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Delete"))));
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Mesage"))));

	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
	{
		iCol = 0;
		Tabel_Player.push_back(new WEB_Tome_Player(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]));
		wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->wtPlayerID)));
		wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->wlPlayerName)));

		for (unsigned int j = 0; j < NumBoostersTypes; j++)
			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->iMaxBoosters[j])));

		wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->wbSave)));
		wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->wbDel)));
		wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Tabel_Player[i]->wbMes)));
		
		Tabel_Player[i]->wbSave->clicked().connect(std::bind([=]() {
			Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerName = WSTRINGtoSTRING(Tabel_Player[i]->wlPlayerName->text());
			for (unsigned int j = 0; j < NumBoostersTypes; j++)
				Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->iMaxBoosters[j] = std::atoi(WSTRINGtoSTRING(Tabel_Player[i]->iMaxBoosters[j]->text()).c_str());			
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			WRefresh();
		}));

		Tabel_Player[i]->wbDel->clicked().connect(std::bind([=]() {
			Bro->vTomeGames[Con->BroGameID]->vPlayer.erase(Bro->vTomeGames[Con->BroGameID]->vPlayer.begin() + i);
			Bro->vTomeGames[Con->BroGameID]->bSaveGame();
			WRefresh();
		}));

		Tabel_Player[i]->wbMes->clicked().connect(std::bind([=]() {
			Wt::WApplication::instance()->doJavaScript(Wt::WApplication::instance()->javaScriptClass() + ".CopyToClip('" + 
				"Hello " + Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerName + ", " + 
				"welcome to the Tome Fight! The GameID is: " + Bro->vTomeGames[Con->BroGameID]->sGameID + " " +
				"and you PlayerID is: " + Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerID + " " +
				"But you can just use this link: " +
				"https://localhost:8443/?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID  + "&playerID=" + Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerID +
				"');");
			
		}));
	}

	iCol = 0;
	wtTabelle->columnAt(iCol++)->setWidth(75);
	wtTabelle->columnAt(iCol++)->setWidth(200);
	for (unsigned int j = 0; j < NumBoostersTypes; j++)
	wtTabelle->columnAt(iCol++)->setWidth(50);
	wtTabelle->columnAt(iCol++)->setWidth(75);
	wtTabelle->columnAt(iCol++)->setWidth(75);
	wtTabelle->columnAt(iCol++)->setWidth(75);

	wbAddPlayer->setWidth(75 + 200 + NumBoostersTypes * 50 + 75 + 75 + 75);
	
	MISE;
}

