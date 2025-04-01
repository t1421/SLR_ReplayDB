//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\DataTypes.h"

#include <algorithm>

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>

#define Card_Size_X 93
#define Card_Size_Y 128

broker *(WEB_Tome_PublicBoosters::Bro) = NULL;

WEB_Tome_PublicBoosters::WEB_Tome_PublicBoosters(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	

	MISD("#1");
	
	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();
	wlFilter = new Wt::WLineEdit();
	
	MISD("#2");
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));

	wlFilter->setWidth(Card_Size_X * 9);
	
	MISD("#3");

	//WRefresh();

	MISE;	
}

void WEB_Tome_PublicBoosters::WRefresh()
{
	MISS;
	
	std::vector <Tome_Booster*> vAllBoosters;

	wtTabelle->clear();

	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
		for (unsigned int j = 0; j < Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters.size(); j++)		
			vAllBoosters.push_back(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters[j]);
	
	switch (Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterOrder)
	{
	case 0:
		std::sort(vAllBoosters.begin(), vAllBoosters.end(), compareBoostersLfdnr);
		break;
	case 1:
		std::sort(vAllBoosters.begin(), vAllBoosters.end(), compareBoostersType);
		break;
	}
	
	Con->DrawBooster(wtTabelle, vAllBoosters, 0);

	wlFilter->setText(Con->BoosterToFilter(vAllBoosters, "AllTome"));
	
	MISE;
}
