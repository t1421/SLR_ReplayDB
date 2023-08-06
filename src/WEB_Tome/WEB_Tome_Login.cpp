#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\DataTypes.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>

broker *(WEB_Tome_Login::Bro) = NULL;

WEB_Tome_Login::WEB_Tome_Login(WEB_Container_Tome *Con_): Con(Con_) //(TomeStruct *_TS): TS(_TS)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	Wt::WTable *wtTabelle = new Wt::WTable();

	MISD("#0");

	wtStatus = new Wt::WText;
	wlGameID = new Wt::WLineEdit();
	wlPlayerID = new Wt::WLineEdit();
	wlAdminID = new Wt::WLineEdit();
	wbJoin = new Wt::WPushButton("JOIN");
	wbJoin->setWidth(300);

	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WTable>(std::move(wtTabelle)));

	MISD("#2");
	wtTabelle->elementAt(0,0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Game ID: </h4>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlGameID)));
	wtTabelle->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player ID: </h4>"))));
	wtTabelle->elementAt(1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlPlayerID)));
	wtTabelle->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Admin ID: </h4>"))));
	wtTabelle->elementAt(2, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlAdminID)));

	wtTabelle->elementAt(3, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbJoin)));
	wtTabelle->elementAt(3, 0)->setColumnSpan(2);

	wtTabelle->elementAt(4, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	wtTabelle->elementAt(4, 0)->setColumnSpan(2);
	
	wtTabelle->columnAt(0)->setWidth(100);
	wtTabelle->columnAt(1)->setWidth(200);

	MISD("#3");

	wbJoin->clicked().connect(std::bind([=]() {
		Check_Input(WSTRINGtoSTRING(wlGameID->text()), WSTRINGtoSTRING(wlPlayerID->text()), WSTRINGtoSTRING(wlAdminID->text()));
	}));

	WRefresh();

	MISE;
}

void WEB_Tome_Login::Check_Input(std::string sGameID, std::string sPlayerID, std::string sAdminID)
{
	MISS;
	MISD(sGameID);
	MISD(sPlayerID);
	MISD(sAdminID);

	*Con->GlobalTS = Bro->L_Load_TomeGameHead(sGameID);

	if (Con->GlobalTS->GameID == sGameID)
		Con->WEB_Toolbar::bDisable[1] = false;

	if (Con->GlobalTS->AdminID == sAdminID)
		Con->WEB_Toolbar::bDisable[3] = false;

	for(int i = 0; i < Con->GlobalTS->PlayerID.size();i++)
		if(Con->GlobalTS->PlayerID[i] == sPlayerID)
			Con->WEB_Toolbar::bDisable[2] = false;

	Con->WRefresh();

	MISE;
}

void WEB_Tome_Login::WRefresh()
{
	MISS;
	
	wtStatus->setText("<h3>WEB_Tome_Login</h3>");

	MISE;
}
