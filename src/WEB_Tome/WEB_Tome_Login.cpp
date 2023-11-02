#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>

broker *(WEB_Tome_Login::Bro) = NULL;

WEB_Tome_Login::WEB_Tome_Login(WEB_Container_Tome *Con_): Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	Wt::WTable *wtTabelle = new Wt::WTable();

	MISD("#0");

	wtStatus = new Wt::WText;
	wlGameIDPublic = new Wt::WLineEdit();
	wlGameIDPlayer = new Wt::WLineEdit();
	wlGameIDAdmin = new Wt::WLineEdit();
	wlPlayerID = new Wt::WLineEdit();
	wlAdminID = new Wt::WLineEdit();
	wbJoinPublic = new Wt::WPushButton("Join as Public");
	wbJoinPlayer = new Wt::WPushButton("Join as Player");
	wbJoinAdmin = new Wt::WPushButton("Join as Admin");
	wbNewGame = new Wt::WPushButton("Make new game");
	//wbLeave = new Wt::WPushButton("Leave");

	wbJoinPublic->setWidth(150);
	wbJoinPlayer->setWidth(150);
	wbJoinPlayer->setWidth(150);
	wbJoinAdmin->setWidth(150);
	wbNewGame->setWidth(150);

	//wbLeave->setDisabled(true);

	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WTable>(std::move(wtTabelle)));

	MISD("#2");
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlGameIDPublic)));
	wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoinPublic)));

	wtTabelle->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))));
	wtTabelle->elementAt(1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlGameIDPlayer)));
	wtTabelle->elementAt(1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player ID: </h4>"))));
	wtTabelle->elementAt(1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlPlayerID)));
	wtTabelle->elementAt(1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoinPlayer)));

	wtTabelle->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))));
	wtTabelle->elementAt(2, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlGameIDAdmin)));
	wtTabelle->elementAt(2, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Admin ID: </h4>"))));
	wtTabelle->elementAt(2, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlAdminID)));
	wtTabelle->elementAt(2, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoinAdmin)));

	wtTabelle->elementAt(3, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbNewGame)));
	/*
	wtTabelle->elementAt(3, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoin)));
	wtTabelle->elementAt(3, 0)->setColumnSpan(2);
	
	wtTabelle->elementAt(4, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbLeave)));
	wtTabelle->elementAt(4, 0)->setColumnSpan(2);
	*/
	wtTabelle->elementAt(5, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	wtTabelle->elementAt(5, 0)->setColumnSpan(5);
	
	wtTabelle->columnAt(0)->setWidth(100);
	wtTabelle->columnAt(1)->setWidth(100);
	wtTabelle->columnAt(2)->setWidth(100);
	wtTabelle->columnAt(3)->setWidth(100);
	wtTabelle->columnAt(4)->setWidth(150);


	MISD("#3");
	wbJoinPublic->clicked().connect(std::bind([=]() {
		JoinPublic();		
	}));

	wbJoinPlayer->clicked().connect(std::bind([=]() {
		JoinPlayer();		
	}));

	wbJoinAdmin->clicked().connect(std::bind([=]() {
		JoinAdmin();		
	}));


	wbNewGame->clicked().connect(std::bind([=]() {
		Con->BroGameID = Bro->getTomeGame("NEW");
		MISD("Con->BroGameID:" )
		wtStatus->setText("OK");
		Con->WEB_Toolbar::bDisable[3] = false;
		Con->WEB_Toolbar::bDisable[4] = false;
		Con->WEB_Toolbar::bDisable[0] = true;
		Con->WEB_Toolbar::sToolbar->setCurrentIndex(3);

		Con->WRefresh();
		Con->updateFrame();
		WRefresh(); //???
	}));
	
	WRefresh();

	MISE;
}

void WEB_Tome_Login::WRefresh()
{
	MISS;
	if (Con->BroGameID != -1)Con->connect();
	else Con->disconnect();
	

	MISE;
}

void WEB_Tome_Login::Parameter(std::string sGameID, std::string sPlayerID, std::string sAdminID)
{
	MISS;
	if (sGameID != "" && sPlayerID == "" && sAdminID == "")
	{
		wlGameIDPublic->setText(sGameID);
		JoinPublic();
	}
	else if (sGameID != "" && sPlayerID != "" && sAdminID == "")
	{
		wlGameIDPlayer->setText(sGameID);
		wlPlayerID->setText(sPlayerID);
		JoinPlayer();
	}
	else if (sGameID != "" && sPlayerID == "" && sAdminID != "")
	{
		wlGameIDAdmin->setText(sGameID);
		wlAdminID->setText(sAdminID);
		JoinAdmin();
	}
	MISE;
}

void WEB_Tome_Login::JoinPublic()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameIDPublic->text()));
	if (Con->BroGameID == -1 || wlGameIDPublic->text() == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		WRefresh();
		MISEA("Public Game ID");
		return;
	}

	wtStatus->setText("OK");
	Con->WEB_Toolbar::bDisable[1] = false;
	Con->WEB_Toolbar::bDisable[4] = false;
	Con->WEB_Toolbar::bDisable[0] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(1);

	Con->WRefresh();
	WRefresh();
	Con->updateFrame();
	MISE;
}

void WEB_Tome_Login::JoinPlayer()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameIDPlayer->text()));
	if (Con->BroGameID == -1 || wlGameIDPlayer->text() == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		WRefresh();
		MISEA("Player Game ID");
		return;
	}

	if (Bro->vTomeGames[Con->BroGameID]->bCheckPlayer(WSTRINGtoSTRING(wlPlayerID->text())) == false
		|| wlPlayerID->text() == "")
	{
		wtStatus->setText("Wrong Player ID");
		Con->WRefresh();
		WRefresh();
		MISEA("Player Player ID");
		return;
	}

	wtStatus->setText("OK");
	Con->WEB_Toolbar::bDisable[2] = false;
	Con->WEB_Toolbar::bDisable[1] = false;
	Con->WEB_Toolbar::bDisable[4] = false;
	Con->WEB_Toolbar::bDisable[0] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(2);

	Con->WRefresh();
	WRefresh();
	Con->updateFrame();
	MISE;
}

void WEB_Tome_Login::JoinAdmin()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameIDAdmin->text()));
	if (Con->BroGameID == -1 || wlGameIDAdmin->text() == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		WRefresh();
		MISEA("Admin Game ID");
		return;
	}

	if (Bro->vTomeGames[Con->BroGameID]->sAdminID != WSTRINGtoSTRING(wlAdminID->text())
		|| wlAdminID->text() == "")
	{
		wtStatus->setText("Wrong Admin ID");
		Con->WRefresh();
		WRefresh();
		MISEA("Admin Admin ID");
		return;
	}

	wtStatus->setText("OK");
	Con->WEB_Toolbar::bDisable[3] = false;
	Con->WEB_Toolbar::bDisable[4] = false;
	Con->WEB_Toolbar::bDisable[0] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(3);

	Con->WRefresh();
	WRefresh();
	Con->updateFrame();
	MISE;
}