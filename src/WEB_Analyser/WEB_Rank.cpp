//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\..\incl\DataTypes.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/Utils.h>


broker *(WEB_Rank::Bro) = NULL;

WEB_Rank::WEB_Rank(WEB_Analyser *WR_, unsigned int _iRankList):WR(WR_)
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
	
	Wt::WAnchor *waLink;

	wtTabelle->clear();
	if (Bro->A_getRankMode(iRankList) == 0)
	{
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Leaderboard </h3>"))));
		MISEA("no Rank")
		return;
	}

	MISD("#1: " + std::to_string(iRankList));
	
	std::vector<ROW> vListe;
	

	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	vListe = Bro->A_getRankeROW(iRankList);
	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Rank </h4>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h4>"))));	
		
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(200);
	
	if(iRankList < 100 && iRankList != 0)
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Power </h4>"))));

	switch (iRankList)	
	{ 
	case 0:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Points </h4>"))));			
		break;
	case 2:		
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Score </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
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
	case 100:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Power </h4>"))));
		break;
	default:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));		
	}
	wtTabelle->columnAt(2)->setWidth(100);
	wtTabelle->columnAt(3)->setWidth(100);

	MISD("#2" + std::to_string(vListe.size()));
	for (unsigned int i = 0; i <vListe.size(); i++)
	{	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		if(iRankList<100)wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID + "#" + std::to_string(vListe[i].ReplayID)))));  //Bro->GetTeamName(vListe[i].ID)
		else wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));  
		//if (iRankList != 0)wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string( vListe[i].Stamps[2])))));
		switch (iRankList)
		{
		case 0:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			break;
		case 2:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0] + vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			break;
		case 1:		
		case 4:
		case 6:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 3:
		case 5:			
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 7:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(
				std::to_string(vListe[i].Stamps[0])
				+ "/" +
				std::to_string(vListe[i].Stamps[1])
			))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 100:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			break;
		default:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
		}	

		if (WR->WA_Admin)
		{
			waLink = new Wt::WAnchor();
			waLink->setText("#");
			waLink->setLink(Wt::WLink(Bro->L_getPMV_WEB_PATH() + Wt::Utils::urlEncode(std::to_string(iRankList) + "_" + vListe[i].ID + ".pmv")));
			wtTabelle->elementAt(i + 1, 9)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
		}
	}	
	MISE;
}
