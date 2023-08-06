//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\..\incl\MIS_Rank.h"
#include "..\..\incl\Utility.h"

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

	MISD("#1: " + std::to_string(iBOTLIST));
	
	std::vector<ROW> vListe;
	

	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	if (iBOTLIST == BOT4LIST)  vListe = Bro->A[BOT4LIST]->getRankeROW(iBOTLIST);
	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Rank </h3>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Player </h3>"))));	
	wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Time </h3>"))));	
	if (iBOTLIST == BOT4LIST)
	{ 
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Stamp1 </h3>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Stamp2 </h3>"))));
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Stamp3 </h3>"))));
		wtTabelle->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Stamp4 </h3>"))));
	}
	
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(300);
	wtTabelle->columnAt(2)->setWidth(100);
	 if (iBOTLIST == BOT4LIST)
	{
		wtTabelle->columnAt(3)->setWidth(100);
		wtTabelle->columnAt(4)->setWidth(100);
		wtTabelle->columnAt(5)->setWidth(100);
		wtTabelle->columnAt(6)->setWidth(100);
	}
	MISD("#2" + std::to_string(vListe.size()));
	for (unsigned int i = 0; i <vListe.size(); i++)
	{	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));
		switch (iBOTLIST)
		{
		case BOT4LIST:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[3])))));
			wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[4])))));
			break;		
		}			
	}	
	MISE;
}