//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"
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

broker *(WEB_Tome_PublicPlayersBooster::Bro) = NULL;

WEB_Tome_PublicPlayersBooster::WEB_Tome_PublicPlayersBooster(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
		
	MISD("#0");

	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();
	wlFilter = new Wt::WLineEdit();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlFilter)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISD("#1");

	wlFilter->setWidth(Card_Size_X * 9);

	MISD("#2");

	//WRefresh();

	MISE;
}

void WEB_Tome_PublicPlayersBooster::WRefresh()
{
	MISS;
	
	unsigned int iRow = 0;
	Wt::WTable *wtTabelleTemp;
	std::vector <Tome_Booster*> vAllBoosters;

	wtTabelle->clear();

	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
	{
		wtTabelle->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<H1>" + Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerName + "</H1>"))));
		//wtTabelle->elementAt(iRow++, 0)->setColumnSpan(9);

		vAllBoosters.clear();
		for (unsigned int j = 0; j < Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters.size(); j++)
			vAllBoosters.push_back(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters[j]);

		switch (Bro->vTomeGames[Con->BroGameID]->iTapShowBoosterPerPlayerOrder)
		{
		case 0:
			std::sort(vAllBoosters.begin(), vAllBoosters.end(), compareBoostersLfdnr);
			break;
		case 1:
			std::sort(vAllBoosters.begin(), vAllBoosters.end(), compareBoostersType);
			break;
		}

		wtTabelleTemp = new Wt::WTable();
		wtTabelle->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelleTemp)));
		Con->DrawBooster(wtTabelleTemp, vAllBoosters, 2);
		wtTabelle->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<H1> </H1>"))));

		wlFilter->setText(Con->BoosterToFilter(vAllBoosters, 2));
	}

	MISE;
}
