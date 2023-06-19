//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Rank.h"
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
	//std::vector<std::pair<std::string, unsigned long>> vListe = Bro->A[iBOTLIST]->getRankePair(iBOTLIST);
	std::vector<ROW> vListe;
	//vListe.reserve(Bro->A[KOTGLISTX]->RankRows.size());

	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	if( iBOTLIST == KOTGLIST1 ||
		iBOTLIST == KOTGLIST2 ||
		iBOTLIST == KOTGLIST3)		
		vListe = Bro->A[KOTGLISTX]->getRankeROW(iBOTLIST);
	else if (iBOTLIST == KOTGLIST4) vListe = Bro->A[KOTGLISTX]->getRankeKOTG();
	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Rank </h3>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Player </h3>"))));	
	wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Time </h3>"))));
	if (iBOTLIST == KOTGLIST4)wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> Ranke </h3>"))));
	
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(300);
	wtTabelle->columnAt(2)->setWidth(100);
	if (iBOTLIST == KOTGLIST4)wtTabelle->columnAt(3)->setWidth(100);
	MISD("#2" + std::to_string(vListe.size()));
	for (unsigned int i = 0; i <vListe.size(); i++)
	{
		
		MISD("#2 0-> " + std::to_string(vListe[i].Stamps[0]));
		MISD("#2 1-> " + std::to_string(vListe[i].Stamps[1]));
		MISD("#2 2-> " + std::to_string(vListe[i].Stamps[2]));
		MISD("#2 3-> " + std::to_string(vListe[i].Stamps[3]));
		MISD("#2 4-> " + std::to_string(vListe[i].Stamps[4]));
		
	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));
		switch (iBOTLIST)
		{
		case KOTGLIST1:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[0])))));
			break;
		case KOTGLIST2:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[1])))));
			break;
		case KOTGLIST3:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[2])))));
			break;
		case KOTGLIST4:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[4])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(
				vListe[i].Stamps[3]
					)))));
			break;
		}	
		
	}
	
	MISE;
}