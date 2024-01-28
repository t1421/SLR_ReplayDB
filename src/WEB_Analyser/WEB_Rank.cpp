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
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Leaderboard </h3>"))));
		MISEA("no Rank")
		return;
	}

	MISD("#1: " + std::to_string(iBOTLIST));
	
	std::vector<ROW> vListe;
	

	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	if (iBOTLIST == BOT6LIST)  vListe = Bro->A[BOT6LIST]->getRankeROW(iBOTLIST);
	MISD("vListe Size1 : " + std::to_string(vListe.size()));
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Rank </h3>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h3>"))));	
	wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h3>"))));	
	if (iBOTLIST == BOT6LIST)
	{ 
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'cyan' >Cyan</font></h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'blue'>Blue </font></h4>"))));
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'silver'>Black </font></h4>"))));
		wtTabelle->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'green'>Green </font></h4>"))));
		wtTabelle->elementAt(0, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'yellow'>Yellow</font></h4>"))));
		wtTabelle->elementAt(0, 8)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'magenta'>Magenta </font></h4>"))));
		wtTabelle->elementAt(0, 9)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'red'>Red </font></h4>"))));
		wtTabelle->elementAt(0, 10)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4><font color = 'white'>White</font> </h4>"))));
	}
	
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(200);
	wtTabelle->columnAt(2)->setWidth(100);
	 if (iBOTLIST == BOT6LIST)
	{
		wtTabelle->columnAt(3)->setWidth(100);
		wtTabelle->columnAt(4)->setWidth(100);
		wtTabelle->columnAt(5)->setWidth(100);
		wtTabelle->columnAt(6)->setWidth(100);
		wtTabelle->columnAt(7)->setWidth(100);
		wtTabelle->columnAt(8)->setWidth(100);
		wtTabelle->columnAt(9)->setWidth(100);
		wtTabelle->columnAt(10)->setWidth(100);
	}
	MISD("#2" + std::to_string(vListe.size()));
	for (unsigned int i = 0; i <vListe.size(); i++)
	{	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));
		switch (iBOTLIST)
		{
		case BOT6LIST:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[3])))));
			wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[4])))));
			wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[5])))));
			wtTabelle->elementAt(i + 1, 8)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[6])))));
			wtTabelle->elementAt(i + 1, 9)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[7])))));
			wtTabelle->elementAt(i + 1, 10)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTime(vListe[i].Stamps[8])))));
			break;		
		}			
	}	
	MISE;
}