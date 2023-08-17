#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\DataTypes.h"

#include <algorithm>
#include <random>

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Tome_PublicBoosters::Bro) = NULL;

WEB_Tome_PublicBoosters::WEB_Tome_PublicBoosters(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	

	MISD("#1");
	
	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));

	
	MISD("#2");

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

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(vAllBoosters), std::end(vAllBoosters), rng);
	
	for (unsigned int j = 0; j <vAllBoosters.size(); j++)
	{
		wtTabelle->elementAt(j, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(
			std::to_string(vAllBoosters[j]->iType)
		))));

		for (unsigned int k = 0; k < vAllBoosters[j]->vCards.size(); k++)
		{
			wtTabelle->elementAt(j, k + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(
				std::to_string(vAllBoosters[j]->vCards[k]->cardId)
			))));
		}
	}

	for (unsigned int i = 0; i < wtTabelle->columnCount(); i++) wtTabelle->columnAt(i)->setWidth(75);

	MISE;
}
