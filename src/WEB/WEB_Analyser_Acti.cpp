#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\Utility.h" 

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_Analyser_Acti.h"

#include "..\..\incl\DataTypes.h" 


#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>

broker *(WEB_Analyser_Acti::Bro) = NULL;

WEB_Analyser_Acti::WEB_Analyser_Acti(WEB_Analyser *WA_) : WA(WA_), newData(true)
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
	if (WA->isOK() != true)
	{
		MISEA("no Replay");
		return;
	}

	if (!newData)
	{
		MISEA("not New");
		return;
	}

	unsigned int iCol;
	unsigned int iRow;

	wtPlayers->clear();
	wtActionsTypes->clear();

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
		if (WA->ActionSums[i]->iCount == 0)continue;
		WA->ActionSums[i]->wcBox->setText(WA->ActionSums[i]->sActionName + "(" + std::to_string(WA->ActionSums[i]->iCount)+ ")");
		wtActionsTypes->elementAt(iRow, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WA->ActionSums[i]->wcBox)));
		WA->ActionSums[i]->wcBox->clicked().connect(std::bind([=]() {
			UpdateTabelle();
			//Switch Color
		}));

		iCol++;
		if (iCol % 5 == 4)
		{
			iRow++;
			iCol = 0;
		}
	}

	UpdateTabelle();

	newData = !newData;
	MISE;
}



void WEB_Analyser_Acti::UpdateTabelle()
{
	MISS;

	wtActions->clear();
	wtActions->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Time"))));
	wtActions->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Type"))));
	wtActions->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player"))));
	wtActions->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Info"))));
	wtActions->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Img"))));

	for (unsigned int i = 0; i < WA->Actions.size(); i++)
	{
		if (DoSkip(WA->Actions[i]->sActionName, WA->Actions[i]->sPlayerName)) continue;
		wtActions->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(WA->Actions[i]->Time)))));
		wtActions->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(WA->Actions[i]->sActionName))));
		wtActions->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(WA->Actions[i]->sPlayerName))));
		wtActions->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(WA->Actions[i]->Info))));
		//wtPlayers->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WImage(
		//iImage >0 = card | <0 stuff
	}

	MISE;
}

bool WEB_Analyser_Acti::DoSkip(std::string sAction, std::string sPlayer)
{
	//MISS;
	for (unsigned int i = 0; i < WA->Players.size(); i++)
		if (WA->Players[i]->Name == sPlayer && !WA->Players[i]->wcBox->isChecked()) return true;
	for (unsigned int i = 0; i < WA->ActionSums.size(); i++)
		if (WA->ActionSums[i]->sActionName == sAction && !WA->ActionSums[i]->wcBox->isChecked()) return true;
	
	//MISE;
	return false;
}