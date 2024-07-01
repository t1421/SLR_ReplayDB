//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\..\incl\MIS_Rank.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>

broker *(WEB_Rank::Bro) = NULL;

WEB_Rank::WEB_Rank(unsigned int _iRankList)
{
	MISS;
	iRankList = _iRankList;
	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISE;
}



void WEB_Rank::WRefresh()
{
	MISS;
	
	wtTabelle->clear();
	if (Bro->A[iRankList]->RankMode == 0)
	{
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Leaderboard </h3>"))));
		MISEA("no Rank")
		return;
	}

	MISD("#1: " + std::to_string(iBOTLIST));
	
	std::vector<ROW> vListe;
	

	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	vListe = Bro->A[iRankList]->getRankeROW();
	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Rank </h4>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h4>"))));	
		
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(200);
	
	if (iRankList != 0)
	{
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Power </h4>"))));
		wtTabelle->columnAt(3)->setWidth(100);
	}
	switch (iRankList)	
	{ 
	case 0:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Points </h4>"))));		
		break;
	case 3:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Buildings </h4>"))));
		break;
	case 5:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Units </h4>"))));
		break;
	case 7:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Score </h4>"))));
		break;
	default:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));		
	}
	wtTabelle->columnAt(2)->setWidth(100);

	MISD("#2" + std::to_string(vListe.size()));
	for (unsigned int i = 0; i <vListe.size(); i++)
	{	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID + "#" + std::to_string(vListe[i].ReplayID)))));  //Bro->GetTeamName(vListe[i].ID)
		if (iRankList != 0)wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string( vListe[i].Stamps[2])))));
		switch (iRankList)
		{
		case 0:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			break;
		case 3:
		case 5:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			break;
		case 7:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(
				std::to_string(vListe[i].Stamps[0])
				+ "/" +
				std::to_string(vListe[i].Stamps[1])
			))));
			break;
		default:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
		}			
	}	
	MISE;
}