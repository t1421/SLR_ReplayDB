#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB\WEB_MFA.h"
#include "..\..\incl\WEB\WEB_Analyser.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WHBoxLayout.h>


broker *(WEB_MFA::Bro) = NULL;

WEB_MFA::WEB_MFA(WEB_Analyser *WR_) : WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	Wt::WHBoxLayout *TempBox = new Wt::WHBoxLayout();
	cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTabelle[0] = new Wt::WTable();
	wtTabelle[1] = new Wt::WTable();
	wtTabelle[2] = new Wt::WTable();
	wcTabelle[0] = new Wt::WContainerWidget();
	wcTabelle[1] = new Wt::WContainerWidget();
	wcTabelle[2] = new Wt::WContainerWidget();
	
	MISD("#1");

	//cMap = new Wt::WContainerWidget();
	wiMap = new Wt::WImage("./resources/kingofthegiants.jpg");
	wiMap->setHeight(500);
	wiMap->setWidth(500);
	wiMap->resize(500, 500);
	wiMap->setMaximumSize(500, 500);
	//cMap->setStyleClass("crop");
	
	MISD("#2");
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)), 1, 0);
	TempGrid->addLayout(std::unique_ptr<Wt::WLayout>(std::move(TempBox)), 2, 0);

	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wiMap)));
	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTabelle[0])));
	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTabelle[1])));
	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcTabelle[2])));
	TempBox->setDirection(Wt::LayoutDirection::LeftToRight);
	TempBox->addStretch(1);

	wcTabelle[0]->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[0])));
	wcTabelle[1]->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[1])));
	wcTabelle[2]->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[2])));
	
	wcTabelle[0]->setWidth(150);
	wcTabelle[1]->setWidth(150);
	wcTabelle[2]->setWidth(150);

	wcTabelle[0]->setContentAlignment(Wt::AlignmentFlag::Left);
	wcTabelle[1]->setContentAlignment(Wt::AlignmentFlag::Left);
	wcTabelle[2]->setContentAlignment(Wt::AlignmentFlag::Left);
	
	MISE;
}

void WEB_MFA::WRefresh()
{
	MISS;

	unsigned long iTimes[3];

	wtTabelle[0]->clear();
	wtTabelle[1]->clear();
	wtTabelle[2]->clear();
	std::string sReturn = WR->Kalk_KOTG(wtTabelle, iTimes);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		//wtStatus->setText("<h3>All looks good :-)</h3> ");
		std::string sTeamID = WR->GetTeamID();
		std::string sTeamName = Bro->GetTeamName(sTeamID);
		Bro->AddRankPlayer(KOTGLIST1, sTeamID, iTimes[0], sTeamName, iTimes[0], iTimes[0]);
		Bro->AddRankPlayer(KOTGLIST2, sTeamID, iTimes[1], sTeamName, iTimes[1], iTimes[1]);
		Bro->AddRankPlayer(KOTGLIST3, sTeamID, iTimes[2], sTeamName, iTimes[2], iTimes[2]);
		Bro->KOTGTotalRanking();

		wtStatus->setText("<h3>Hello there Team " + sTeamName + ", nice run :-)</h3> ");

		MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}

	MISE;
}

