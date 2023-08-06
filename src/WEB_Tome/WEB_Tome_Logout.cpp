#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Logout.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

broker *(WEB_Tome_Logout::Bro) = NULL;

WEB_Tome_Logout::WEB_Tome_Logout()
{
	MISS;

	cMain = new Wt::WContainerWidget();

	MISD("#0");

	wtStatus = new Wt::WText;

	MISD("#1");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));

	MISD("#2");

	WRefresh();

	MISE;
}

void WEB_Tome_Logout::WRefresh()
{
	MISS;
	
	wtStatus->setText("<h3>WEB_Tome_Logout</h3>");

	MISE;
}
