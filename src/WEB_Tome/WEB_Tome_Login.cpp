//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WRadioButton.h>


broker *(WEB_Tome_Login::Bro) = NULL;

WEB_Tome_Login::WEB_Tome_Login(WEB_Container_Tome *Con_): Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	Wt::WTable *wtTabelle = new Wt::WTable();

	MISD("#0");

	wtStatus = new Wt::WText;
	wlGameID = new Wt::WLineEdit();
	wlUserID = new Wt::WLineEdit();	
	wbJoin = new Wt::WPushButton("Join");
	wbNewGame = new Wt::WPushButton("Make new game");

	//wrType[0] = new Wt::WRadioButton();
	//wrType[1] = new Wt::WRadioButton();
	//wrType[2] = new Wt::WRadioButton();
	gbJoinMode = std::make_shared<Wt::WButtonGroup>();
	
	/*
	wbJoinPublic->setWidth(150);
	wbJoinPlayer->setWidth(150);
	wbJoinPlayer->setWidth(150);
	wbJoinAdmin->setWidth(150);
	wbNewGame->setWidth(150);
	*/
	//wbLeave->setDisabled(true);

	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WTable>(std::move(wtTabelle)));

	MISD("#2");
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))));
	wtTabelle->elementAt(0, 0)->setColumnSpan(3);
	wtTabelle->elementAt(0, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	
	wtTabelle->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlGameID)));
	wtTabelle->elementAt(1, 0)->setColumnSpan(3);
	wtTabelle->elementAt(1, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	wtTabelle->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Public </h4>"))));
	wtTabelle->elementAt(2, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h4>"))));
	wtTabelle->elementAt(2, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Admin </h4>"))));
	wtTabelle->elementAt(2, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(2, 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(2, 2)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	gbJoinMode->addButton(wtTabelle->elementAt(3, 0)->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>()), 0);
	gbJoinMode->addButton(wtTabelle->elementAt(3, 1)->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>()), 1);
	gbJoinMode->addButton(wtTabelle->elementAt(3, 2)->addWidget(Wt::cpp14::make_unique<Wt::WRadioButton>()), 2);
	gbJoinMode->setCheckedButton(gbJoinMode->button(0));
	wtTabelle->elementAt(3, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(3, 1)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	wtTabelle->elementAt(3, 2)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	wtTabelle->elementAt(4, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlUserID)));
	wtTabelle->elementAt(4, 0)->setColumnSpan(3);
	wtTabelle->elementAt(4, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	wtTabelle->elementAt(5, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoin)));
	wtTabelle->elementAt(5, 0)->setColumnSpan(3);
	wtTabelle->elementAt(5, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	wtTabelle->elementAt(6, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbNewGame)));
	wtTabelle->elementAt(6, 0)->setColumnSpan(3);
	wtTabelle->elementAt(6, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);

	wtTabelle->elementAt(7, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	wtTabelle->elementAt(7, 0)->setColumnSpan(3);
	wtTabelle->elementAt(7, 0)->setContentAlignment(Wt::AlignmentFlag::Center | Wt::AlignmentFlag::Middle);
	
	wtTabelle->columnAt(0)->setWidth(100);
	wtTabelle->columnAt(1)->setWidth(100);
	wtTabelle->columnAt(2)->setWidth(100);

	wbNewGame->setWidth(300);
	wbJoin->setWidth(300);


	MISD("#3");
	wbJoin->clicked().connect(std::bind([=]() {
			//if toggel / switch toggel
		switch (gbJoinMode->selectedButtonIndex())
		{
		case 0:
			JoinPublic();
			break;
		case 1:
			JoinPlayer();
			break;
		case 2:
			JoinAdmin();
			break;
		}
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
		//WRefresh();
	}));

	gbJoinMode->checkedChanged().connect(std::bind([=](Wt::WRadioButton *selection) {
		wlUserID->setDisabled(gbJoinMode->selectedButtonIndex() == 0);
	}, std::placeholders::_1));
		
	//WRefresh();

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
		gbJoinMode->setCheckedButton(gbJoinMode->button(0));
		wlGameID->setText(sGameID);
		JoinPublic();
	}
	else if (sGameID != "" && sPlayerID != "" && sAdminID == "")
	{
		gbJoinMode->setCheckedButton(gbJoinMode->button(1));
		wlGameID->setText(sGameID);
		wlUserID->setText(sPlayerID);
		JoinPlayer();
	}
	else if (sGameID != "" && sPlayerID == "" && sAdminID != "")
	{
		gbJoinMode->setCheckedButton(gbJoinMode->button(2));
		wlGameID->setText(sGameID);
		wlUserID->setText(sAdminID);
		JoinAdmin();
	}
	MISE;
}

void WEB_Tome_Login::JoinPublic()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameID->text()));
	if (Con->BroGameID == -1 || wlGameID->text() == "")
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
	Con->PublicReset();

	Con->WRefresh();	
	Con->updateFrame();
	WRefresh();
	MISE;
}

void WEB_Tome_Login::JoinPlayer()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameID->text()));
	if (Con->BroGameID == -1 || wlGameID->text() == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		MISEA("Player Game ID");
		return;
	}

	if (Bro->vTomeGames[Con->BroGameID]->bCheckPlayer(WSTRINGtoSTRING(wlUserID->text())) == false
		|| wlUserID->text() == "")
	{
		wtStatus->setText("Wrong Player ID");
		Con->WRefresh();
		MISEA("Player Player ID");
		return;
	}

	wtStatus->setText("OK");
	Con->WEB_Toolbar::bDisable[2] = false;
	Con->WEB_Toolbar::bDisable[1] = false;
	Con->WEB_Toolbar::bDisable[4] = false;
	Con->WEB_Toolbar::bDisable[0] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(2);
	Con->PublicReset();

	Con->WRefresh();
	Con->updateFrame();
	WRefresh();
	MISE;
}

void WEB_Tome_Login::JoinAdmin()
{
	MISS;
	Con->BroGameID = Bro->getTomeGame(WSTRINGtoSTRING(wlGameID->text()));
	if (Con->BroGameID == -1 || wlGameID->text() == "")
	{
		wtStatus->setText("Wrong Game ID");
		Con->WRefresh();
		MISEA("Admin Game ID");
		return;
	}

	if (Bro->vTomeGames[Con->BroGameID]->sAdminID != WSTRINGtoSTRING(wlUserID->text())
		|| wlUserID->text() == "")
	{
		wtStatus->setText("Wrong Admin ID");
		Con->WRefresh();
		MISEA("Admin Admin ID");
		return;
	}

	wtStatus->setText("OK");
	Con->WEB_Toolbar::bDisable[3] = false;
	Con->WEB_Toolbar::bDisable[4] = false;
	Con->WEB_Toolbar::bDisable[0] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(3);

	Con->WRefresh();
	Con->updateFrame();
	WRefresh();
	MISE;
}