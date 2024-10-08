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
	case 101:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Adv </h4>"))));
		wtTabelle->elementAt(0, 2)->widget(0)->setToolTip("Finish Unexpected Visitors on advanced difficulty or higher");
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Exp </h4>"))));
		wtTabelle->elementAt(0, 3)->widget(0)->setToolTip("Finish Unexpected Visitors on expert difficulty");
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Deck </h4>"))));
		wtTabelle->elementAt(0, 4)->widget(0)->setToolTip("Finish Unexpected Visitors with only shadow or amii cards");
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Adv </h4>"))));
		wtTabelle->elementAt(0, 5)->widget(0)->setToolTip("Finish Into the Jungle on advanced difficulty or higher");
		wtTabelle->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Exp </h4>"))));
		wtTabelle->elementAt(0, 6)->widget(0)->setToolTip("Finish Into the Jungle on expert difficulty");
		wtTabelle->elementAt(0, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Deck </h4>"))));
		wtTabelle->elementAt(0, 7)->widget(0)->setToolTip("Finish Into the Jungle with only nature or amii cards");
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
		//if(iRankList<100 || iRankList==101)wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID + "#" + std::to_string(vListe[i].ReplayID)))));  //Bro->GetTeamName(vListe[i].ID)
		if (iRankList<100 || iRankList == 101)wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID))));  
		else wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));  
		//if (iRankList != 0)wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string( vListe[i].Stamps[2])))));
		switch (iRankList)
		{
		case 0:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			break;
		case 2:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
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
		case 101:
			if (vListe[i].Stamps[0] == 1)wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[1] == 1)wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[2] == 1)wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[3] == 1)wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[4] == 1)wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[5] == 1)wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));

			/*
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[3])))));
			wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[4])))));
			wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[5])))));
			*/

			
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
	if (iRankList == 101)
	{
		wtTabelle->removeColumn(0);
		wtTabelle->columnAt(2)->setWidth(100);
		wtTabelle->columnAt(3)->setWidth(100);
		wtTabelle->columnAt(4)->setWidth(100);
		wtTabelle->columnAt(5)->setWidth(100);
		wtTabelle->columnAt(6)->setWidth(100);
		wtTabelle->columnAt(7)->setWidth(100);
	}
	MISE;
}
