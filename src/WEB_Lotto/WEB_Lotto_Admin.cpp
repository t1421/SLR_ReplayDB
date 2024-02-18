#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"

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


broker *(WEB_Lotto_Admin::Bro) = NULL;


WEB_Lotto_Admin::WEB_Lotto_Admin(WEB_Container_Lotto *Con_) : Con(Con_)
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
	wcShowBoostersOfPlayer = new Wt::WCheckBox("Show Boosters per Player");
	wcAllowOpening = new Wt::WCheckBox("Allow Opening Booster");
	wcNoDouble = new Wt::WCheckBox("No Duplicate Cards");

	wtGameID = new Wt::WText("");
	wtAdminID = new Wt::WText("");

	wbSave = new Wt::WPushButton("Save");
	wbAddPlayer = new Wt::WPushButton("Add Player");
	
	MISD("#11");
	

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
	
	

	MISD("#3");
	

	MISD("#4");


	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayerID"))));	

	wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player Name"))));
	wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Add"))));
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Rem"))));

	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Delete"))));
	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Mesage"))));

	MISD("#4");

	wtTabelle->columnAt(1)->setWidth(160);

	MISD("#5");
	
	
	MISE;
}

void WEB_Lotto_Admin::WRefresh()
{
	MISS;
	/*
	if (Con->BroGameID == -1)
	{
		MISEA("WTF !!!");
		return;
	}
	*/
	//unsigned int iCol = 0;
	//std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	//std::vector<WEB_Tome_Player *> Tabel_Player;

	MISE;
}

