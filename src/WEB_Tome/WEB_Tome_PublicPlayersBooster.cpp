#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"
#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\DataTypes.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

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
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISD("#1");

	MISD("#2");

	//WRefresh();

	MISE;
}

void WEB_Tome_PublicPlayersBooster::WRefresh()
{
	MISS;
	
	unsigned int iRow = 0;

	wtTabelle->clear();

	for (unsigned int i = 0; i < Bro->vTomeGames[Con->BroGameID]->vPlayer.size(); i++)
	{
		wtTabelle->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<H1>" + Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->sPlayerName + "</H1>"))));
		wtTabelle->elementAt(iRow++, 0)->setColumnSpan(9);

		for (unsigned int j = 0; j < Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters.size(); j++)
		{
			wtTabelle->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
				DrawImg("./resources/Boosters/" + std::to_string(Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters[j]->iType) + ".png",
					Card_Size_X, Card_Size_Y
				))));

			for (unsigned int k = 0; k < Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters[j]->vCards.size(); k++)
			{
				wtTabelle->elementAt(iRow, k + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
					DrawImg(Bro->J_GetImage(
						Bro->vTomeGames[Con->BroGameID]->vPlayer[i]->vBoosters[j]->vCards[k]->cardId,
						3,
						4,
						1,
						false),
						Card_Size_X, Card_Size_Y
					))));
			}
			iRow++;
		}
		iRow++;
	}

	for (unsigned int i = 0; i < wtTabelle->columnCount(); i++) wtTabelle->columnAt(i)->setWidth(75);
	MISE;
}
