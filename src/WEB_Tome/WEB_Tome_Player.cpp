#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

broker *(WEB_Tome_Player::Bro) = NULL;

WEB_Tome_Player::WEB_Tome_Player(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();

	MISD("#0");

	
	MISD("#1");

	
	MISD("#2");

	WRefresh();

	MISE;
}

void WEB_Tome_Player::WRefresh()
{
	MISS;
	//Code für Filter
	// Check Replay

	MISE;
}
