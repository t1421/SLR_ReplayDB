#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Leave.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"

#include <Wt/WContainerWidget.h>
//#include <Wt/WText.h>
//#include <Wt/WGridLayout.h>
//#include <Wt/WPushButton.h>


broker *(WEB_Tome_Leave::Bro) = NULL;

WEB_Tome_Leave::WEB_Tome_Leave(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	MISD("#0");
	
	//WRefresh();



	MISE;
}

void WEB_Tome_Leave::WRefresh()
{
	MISS;
	
	Con->BroGameID = -1;
	Con->WEB_Toolbar::bDisable[0] = false;
	Con->WEB_Toolbar::bDisable[1] = true;
	Con->WEB_Toolbar::bDisable[2] = true;
	Con->WEB_Toolbar::bDisable[3] = true;
	Con->WEB_Toolbar::bDisable[4] = true;
	Con->WEB_Toolbar::sToolbar->setCurrentIndex(0);
	Con->WRefresh();

	MISE;
}
