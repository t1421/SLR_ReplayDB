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
#include <Wt/WBreak.h>
#include <Wt/WLength.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>
#include <Wt/WRadioButton.h>
#include <Wt/WComboBox.h>



broker *(WEB_Tome_Admin::Bro) = NULL;

struct WEB_Tome_Player
{
	Wt::WText *wtPlayerID;
	Wt::WLineEdit *wlPlayerName;
	Wt::WLineEdit *iMaxBoosters[NumBoostersTypes];
	Wt::WPushButton *wbDel;
	Wt::WPushButton *wbMes;
	Wt::WAnchor*waLink;
	Wt::WTableRow* wrRow;
	

	WEB_Tome_Player(Tome_Player *Player)
	{
		wrRow = new Wt::WTableRow();
		wtPlayerID = new Wt::WText(Player->sPlayerID);
		wlPlayerName = new Wt::WLineEdit(Player->sPlayerName);
		wbDel = new Wt::WPushButton("Del");
		wbMes = new Wt::WPushButton("Mes");
		waLink = new Wt::WAnchor();
		waLink->setText("Link");
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
		wrRow->elementAt(NumBoostersTypes + 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
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

	wcShowGlobalBoosterProgress = new Wt::WCheckBox("Global Progress");

	wcTapShowPlayer = new Wt::WCheckBox("Show Players");
	wcTapShowPlayerBoosterOpen = new Wt::WCheckBox("Opend");
	wcTapShowPlayerBoosterMax = new Wt::WCheckBox("Max");

	wcTapShowBooster = new Wt::WCheckBox("Show Boosters");
	wcTapShowBoosterUR = new Wt::WCheckBox("UR");
	wcTapShowBoosterR = new Wt::WCheckBox("R");
	wcTapShowBoosterUC = new Wt::WCheckBox("UC");
	wcTapShowBoosterC = new Wt::WCheckBox("C");	
	wcTapShowBoosterOrder = new Wt::WComboBox;

	wcTapShowCards = new Wt::WCheckBox("Show Cards");
	wcTapShowCardsUR = new Wt::WCheckBox("UR");
	wcTapShowCardsR = new Wt::WCheckBox("R");
	wcTapShowCardsUC = new Wt::WCheckBox("UC");
	wcTapShowCardsC = new Wt::WCheckBox("C");
	wcTapShowCardsOrder = new Wt::WComboBox;


	wcTapShowBoosterPerPlayer = new Wt::WCheckBox("Show Boosters Per Player");
	wcTapShowBoosterPerPlayerUR = new Wt::WCheckBox("UR");
	wcTapShowBoosterPerPlayerR = new Wt::WCheckBox("R");
	wcTapShowBoosterPerPlayerUC = new Wt::WCheckBox("UC");
	wcTapShowBoosterPerPlayerC = new Wt::WCheckBox("C");
	wcTapShowBoosterPerPlayerOrder = new Wt::WComboBox;

	wcAllowOpening = new Wt::WCheckBox("Allow Opening Booster");
	wcAllowRefroging = new Wt::WCheckBox("Allow Refroging");

	wcNoDouble = new Wt::WCheckBox("No Duplicate Cards");
	wcNoAffinities = new Wt::WCheckBox("No Affinities");
	wcNoPromos = new Wt::WCheckBox("No Promo Cards");

	wtGameID = new Wt::WText("");
	wtAdminID = new Wt::WText("");

	wbSave = new Wt::WPushButton("Save");
	wbAddPlayer = new Wt::WPushButton("Add Player");
	
	MISD("#11");
	wfuDropZone = new Wt::WFileUpload();
	wtReplayResultCard = new Wt::WTable();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	
	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");

	wcTapShowBoosterOrder->addItem("Time");
	wcTapShowBoosterOrder->addItem("Typ");

	wcTapShowCardsOrder->addItem("Colour");
	wcTapShowCardsOrder->addItem("Rarety");
	wcTapShowCardsOrder->addItem("ID");

	wcTapShowBoosterPerPlayerOrder->addItem("Time");
	wcTapShowBoosterPerPlayerOrder->addItem("Typ");

	MISD("#2");

	//Wt::WGridLayout* TempGrid = new Wt::WGridLayout();

	Wt::WTable *wtTempTable = new Wt::WTable();

	unsigned int iRow = 0;
	//cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtGameID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtAdminID)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTempTable)));

	//TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Public Tap Settings </h4>"))), iRow, 0);
	//iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Public Tap Settings </h4>"))));
	wtTempTable->elementAt(iRow, 0)->setColumnSpan(2);
	iRow++;

	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcShowGlobalBoosterProgress)));
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowPlayer)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowPlayerBoosterOpen)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowPlayerBoosterMax)));
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBooster)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterUR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterUC)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterC)));
	wtTempTable->elementAt(iRow, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterOrder)));
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCards)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCardsUR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCardsR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCardsUC)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCardsC)));
	wtTempTable->elementAt(iRow, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowCardsOrder)));
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayer)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayerUR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayerR)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayerUC)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayerC)));
	wtTempTable->elementAt(iRow, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTapShowBoosterPerPlayerOrder)));
	iRow++;

	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Others Settings </h4>"))));
	wtTempTable->elementAt(iRow, 0)->setColumnSpan(2);
	
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcAllowOpening)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcAllowRefroging)));
	iRow++;
	wtTempTable->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcNoDouble)));
	wtTempTable->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcNoAffinities)));
	wtTempTable->elementAt(iRow, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcNoPromos)));
	
	wtTempTable->columnAt(0)->setWidth(250);
	wtTempTable->columnAt(1)->setWidth(250);
	wtTempTable->columnAt(2)->setWidth(150);

	wcAllowRefroging->disable();
	wcNoAffinities->disable();
	wcNoPromos->disable();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player Table </h4>"))));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbSave)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbAddPlayer)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReplayResultCard)));
	
	MISD("#3");
	wcShowGlobalBoosterProgress->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bShowGlobalBoosterProgress = wcShowGlobalBoosterProgress->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));

	wcTapShowPlayer->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowPlayer = wcTapShowPlayer->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcTapShowPlayerBoosterOpen->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterOpen = wcTapShowPlayerBoosterOpen->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	wcTapShowPlayerBoosterMax->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterMax = wcTapShowPlayerBoosterMax->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));

	MISD("#31");
	wcTapShowBooster->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBooster = wcTapShowBooster->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#311");
	wcTapShowBoosterUR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterUR = wcTapShowBoosterUR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#312");
	wcTapShowBoosterR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterR = wcTapShowBoosterR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#313");
	wcTapShowBoosterUC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterUC = wcTapShowBoosterUC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#314");
	wcTapShowBoosterC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterC = wcTapShowBoosterC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#315");
	wcTapShowBoosterOrder->changed().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterOrder = wcTapShowBoosterOrder->currentIndex();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#32");
	wcTapShowCards->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowCards = wcTapShowCards->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowCardsUR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowCardsUR = wcTapShowCardsUR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowCardsR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowCardsR = wcTapShowCardsR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowCardsUC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowCardsUC = wcTapShowCardsUC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowCardsC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowCardsC = wcTapShowCardsC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowCardsOrder->changed().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->iTapShowCardsOrder = wcTapShowCardsOrder->currentIndex();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	MISD("#33");
	wcTapShowBoosterPerPlayer->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayer = wcTapShowBoosterPerPlayer->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcTapShowBoosterPerPlayerUR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerUR = wcTapShowBoosterPerPlayerUR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowBoosterPerPlayerR->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerR = wcTapShowBoosterPerPlayerR->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowBoosterPerPlayerUC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerUC = wcTapShowBoosterPerPlayerUC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowBoosterPerPlayerC->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerC = wcTapShowBoosterPerPlayerC->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));
	wcTapShowBoosterPerPlayerOrder->changed().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterPerPlayerOrder = wcTapShowBoosterPerPlayerOrder->currentIndex();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		WRefresh();
		}));

	MISD("#333");

	wcAllowOpening->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bAllowOpening = wcAllowOpening->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcAllowRefroging->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bAllowRefroging = wcAllowRefroging->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	MISD("#34");
	wcNoDouble->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bNoDouble = wcNoDouble->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
	}));
	wcNoAffinities->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bNoAffinities = wcNoAffinities->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));
	wcNoPromos->clicked().connect(std::bind([=]() {
		Bro->vTomeGames[Con->BroGameID]->bNoPromos = wcNoPromos->isChecked();
		Bro->vTomeGames[Con->BroGameID]->bSaveGame();
		WRefresh();
		Bro->postChatEventMIS(std::to_string(Con->BroGameID), "global");
		}));

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

	unsigned int iCol = 0;
	wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Add"))));
	wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Rem"))));
	wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
	wtTabelle->elementAt(1, iCol)->setColumnSpan(2);

	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayerID"))));	
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player Name"))));
	
	MISD("#5");
	for (unsigned int i = 0; i < EnumBoosters.size(); i++)
	{
		wtTabelle->elementAt(2, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg(Bro->L_getBOOSTER_PATH() + EnumBoosters[i].first + ".png", Booster_Size_X, Booster_Size_Y)
		)));
		
		wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("+"))));
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(0, iCol)->widget(0))->setWidth(Booster_Size_X * 1.5);
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(0, iCol)->widget(0))->clicked().connect(std::bind([=]() {
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
		
		wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("-"))));
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(1, iCol)->widget(0))->setWidth(Booster_Size_X * 1.5);
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(1, iCol)->widget(0))->clicked().connect(std::bind([=]() {
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
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Delete"))));
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Mesage"))));
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Link"))));

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
	MISD("#1");
	wtGameID->setText("<h4> Game ID: " + Bro->vTomeGames[Con->BroGameID]->sGameID + "</h4>");
	wtAdminID->setText("<h4> Admin ID: " + Bro->vTomeGames[Con->BroGameID]->sAdminID + "</h4>");
	std::stringstream sLink; 
	sLink<< Bro->L_getWebTome()<<"?gameID="<<Bro->vTomeGames[Con->BroGameID]->sGameID<<"&adminID="<<Bro->vTomeGames[Con->BroGameID]->sAdminID;
	waLink->setLink(Wt::WLink(sLink.str()));

	MISD("#2");
	wcShowGlobalBoosterProgress->setChecked(Bro->vTomeGames[Con->BroGameID]->bShowGlobalBoosterProgress);

	wcTapShowPlayer->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowPlayer);
	wcTapShowPlayerBoosterOpen->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterOpen);
	wcTapShowPlayerBoosterMax->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowPlayerBoosterMax);
	MISD("#3");

	wcTapShowBooster->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBooster);
	wcTapShowBoosterUR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterUR);
	wcTapShowBoosterR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterR);
	wcTapShowBoosterUC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterUC);
	wcTapShowBoosterC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterC);
	wcTapShowBoosterOrder->setCurrentIndex(Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterOrder);
	
	MISD("#4");

	wcTapShowCards->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowCards);
	wcTapShowCardsUR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowCardsUR);
	wcTapShowCardsR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowCardsR);
	wcTapShowCardsUC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowCardsUC);
	wcTapShowCardsC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowCardsC);
	wcTapShowCardsOrder->setCurrentIndex(Bro->vTomeGames[Con->BroGameID]->iTapShowCardsOrder);
	
	MISD("#5");

	wcTapShowBoosterPerPlayer->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayer);
	wcTapShowBoosterPerPlayerUR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerUR);
	wcTapShowBoosterPerPlayerR->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerR);
	wcTapShowBoosterPerPlayerUC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerUC);
	wcTapShowBoosterPerPlayerC->setChecked(Bro->vTomeGames[Con->BroGameID]->bTapShowBoosterPerPlayerC);
	wcTapShowBoosterPerPlayerOrder->setCurrentIndex(Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterPerPlayerOrder);

	MISD("#55");
	
	wcAllowOpening->setChecked(Bro->vTomeGames[Con->BroGameID]->bAllowOpening);
	wcAllowRefroging->setChecked(Bro->vTomeGames[Con->BroGameID]->bAllowRefroging);

	MISD("#6");

	wcNoDouble->setChecked(Bro->vTomeGames[Con->BroGameID]->bNoDouble);
	wcNoAffinities->setChecked(Bro->vTomeGames[Con->BroGameID]->bNoAffinities);
	wcNoPromos->setChecked(Bro->vTomeGames[Con->BroGameID]->bNoPromos);

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
					Bro->L_getWebTome() + "?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID + "&playerID=" + iTP->sPlayerID +
					"');");
			}));

			Tabel_Player[Tabel_Player.size() - 1]->waLink->setLink(Wt::WLink(Bro->L_getWebTome() + "?gameID=" + Bro->vTomeGames[Con->BroGameID]->sGameID + "&playerID=" + iTP->sPlayerID));
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