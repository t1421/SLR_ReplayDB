#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Admin.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Tome_Admin::Bro) = NULL;

WEB_Tome_Admin::WEB_Tome_Admin(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	MISD("#0");

	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));

	MISD("#1");

	//WRefresh();

	MISE;
}

void WEB_Tome_Admin::WRefresh()
{
	MISS;
	

	MISE;
}
