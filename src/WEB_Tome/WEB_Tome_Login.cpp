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
		WRefresh(); //???
	}));

	wbJoinPlayer->clicked().connect(std::bind([=]() {
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
		WRefresh(); //???
	}));

	wbJoinAdmin->clicked().connect(std::bind([=]() {
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
		WRefresh(); //???
	}));


	wbNewGame->clicked().connect(std::bind([=]() {
		/*
		wtStatus->setText("OK");
		Con->WEB_Toolbar::bDisable[3] = false;
		Con->WEB_Toolbar::bDisable[0] = true;
		Con->WEB_Toolbar::sToolbar->setCurrentIndex(3);
		*/
		Con->WRefresh();
		WRefresh(); //???
	}));
	/*
	wbJoin->clicked().connect(std::bind([=]() {
		Check_Input(WSTRINGtoSTRING(wlGameID->text()), WSTRINGtoSTRING(wlPlayerID->text()), WSTRINGtoSTRING(wlAdminID->text()));
	}));

	wbLeave->clicked().connect(std::bind([=]() {
		wlGameID->setText("");
		wlPlayerID->setText("");
		wlAdminID->setText("");
		Check_Input("", "", "");
	}));
	*/
	WRefresh();

	MISE;
}
/*
void WEB_Tome_Login::Check_Input(std::string sGameID, std::string sPlayerID, std::string sAdminID)
{
	MISS;
	MISD(sGameID);
	MISD(sPlayerID);
	MISD(sAdminID);
	wlGameID->setText(sGameID);
	wlPlayerID->setText(sPlayerID);
	wlAdminID->setText(sAdminID);
	
	Con->WEB_Toolbar::bDisable[1] = true;
	Con->WEB_Toolbar::bDisable[2] = true;
	Con->WEB_Toolbar::bDisable[3] = true;
	wtStatus->setText(" ");

	Con->BroGameID = Bro->getTomeGame(sGameID);
	if (Con->BroGameID == -1 || sGameID == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		WRefresh();
		MISEA("No Game ID")
		return;
	}
	else Con->WEB_Toolbar::bDisable[1] = false;

	if (Bro->vTomeGames[Con->BroGameID]->sAdminID == sAdminID && sAdminID!="" )Con->WEB_Toolbar::bDisable[3] = false;
	else if(sAdminID != "")wtStatus->setText(wtStatus->text() + "Wrong Admin ID ");

	for(int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size();i++)
		if (Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerID == sPlayerID)
		{
			Con->WEB_Toolbar::bDisable[2] = false;
			break;
		}
	if(Con->WEB_Toolbar::bDisable[2] == true && sPlayerID != "")
		wtStatus->setText(wtStatus->text() +  "Wrong Player ID ");

	Con->WRefresh();
	WRefresh();
	
	MISE;
}
*/
void WEB_Tome_Login::WRefresh()
{
	MISS;
	if (Con->BroGameID != -1)Con->connect();
	else Con->disconnect();
	
	//wtStatus->setText("<h3>WEB_Tome_Login</h3>");
	//MISD(std::to_string(Con->BroGameID));
	/*
	wbLeave->setEnabled(Con->BroGameID != -1);
	wbJoin->setEnabled(Con->BroGameID == -1);
	wlGameID->setEnabled(Con->BroGameID == -1);
	wlPlayerID->setEnabled(Con->BroGameID == -1);
	wlAdminID->setEnabled(Con->BroGameID == -1);*/
	

	MISE;
}
