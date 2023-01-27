//#define DF_Debug

#include "Broker.h"

#include "WEB_Rank.h"
#include "MIS_Rank.h"
#include "Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Rank::Bro) = NULL;

WEB_Rank::WEB_Rank(unsigned int _iBOTLIST)
{
	MISS;
	iBOTLIST = _iBOTLIST;
	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISE;
}



void WEB_Rank::WRefresh()
{
	MISS;

	wtTabelle->clear();
	if (Bro->A[iBOTLIST]->RankMode == 0)
	{
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Leaderboard at the moment </h3>"))));
		MISEA("no Rank")
		return;

	}

	

	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Rank </h3>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Player </h3>"))));
	if(iBOTLIST==0) wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Actions </h3>"))));
	else wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Time </h3>"))));

	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(200);
	wtTabelle->columnAt(2)->setWidth(100);

	for (unsigned int i = 0; i < Bro->A[iBOTLIST]->RankRows.size(); i++)
	{
		//wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->A[iBOTLIST]->RankRows[i]->Player)))));
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->A[iBOTLIST]->RankRows[i]->Name))));
		if (iBOTLIST == 0) wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(Bro->A[iBOTLIST]->RankRows[i]->Time)))));
		else wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(Bro->A[iBOTLIST]->RankRows[i]->Time)))));
	}

	MISE;
}