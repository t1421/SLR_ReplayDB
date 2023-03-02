#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_Analyser_Acti.h"

#include "..\..\incl\DataTypes.h" 

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

broker *(WEB_Analyser_Acti::Bro) = NULL;

WEB_Analyser_Acti::WEB_Analyser_Acti(WEB_Analyser *WA_) : WA(WA_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	
	wtPlayers = new Wt::WTable();
	wtActionsTypes = new Wt::WTable();
	wtActions = new Wt::WTable();
	
	MISD("#1");	

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPlayers)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtActionsTypes)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtActions)));
	
	

	MISD("#3");

	
	MISE;
}

void WEB_Analyser_Acti::WRefresh()
{
	MISS;

	unsigned int iCol;
	unsigned int iRow;

	iCol = 0;
	iRow = 0;
	
	for (unsigned int i = 0; i < WA->Players.size(); i++)
	{
		wtPlayers->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WA->Players[i]->wcBox)));
		WA->Players[i]->wcBox->clicked().connect(std::bind([=]() {
			UpdateTabelle();
			//Switch Color
		}));

		iCol++;
		if (i % 5 == 4)
		{
			iRow++;
			iCol = 0;
		}
	}

	

	MISD("#2");

	iCol = 0;
	iRow = 0;	
	for (unsigned int i = 0; i < WA->ActionSums.size(); i++)
	{
		wtActionsTypes->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WA->ActionSums[i]->wcBox)));
		WA->ActionSums[i]->wcBox->clicked().connect(std::bind([=]() {
			UpdateTabelle();
			//Switch Color
		}));

		iCol++;
		if (i % 5 == 4)
		{
			iRow++;
			iCol = 0;
		}
	}

	MISE;
}


void WEB_Analyser_Acti::UpdateTabelle()
{
	MISS;


	MISE;
}

