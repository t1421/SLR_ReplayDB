#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB\WEB_MFA.h"
#include "..\..\incl\WEB\WEB_Analyser.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>

broker *(WEB_MFA::Bro) = NULL;

WEB_MFA::WEB_MFA(WEB_Analyser *WR_) : WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	//cReplay = new Wt::WContainerWidget();
	//cReplayResult = new Wt::WContainerWidget();
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTabelle[0] = new Wt::WTable();
	wtTabelle[1] = new Wt::WTable();
	wtTabelle[2] = new Wt::WTable();
	
	MISD("#1");

	//cMap = new Wt::WContainerWidget();
	wiMap = new Wt::WImage("./resources/kingofthegiants.jpg");
	//cMap->setStyleClass("crop");
	
	MISD("#2");
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)), 1, 0, 0, 4);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wiMap)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[0])), 2, 1);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[1])), 2, 2);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle[2])), 2, 3);
	
	//TempGrid->setColumnStretch(0, 5);
	//TempGrid->setColumnStretch(1, 95);

	//cReplayResult->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	//cReplayResult->setContentAlignment(Wt::AlignmentFlag::Left);
	
	//cMap->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wiMap)));
	//cMap->setMaximumSize(400, 400);
	
	MISE;
}

void WEB_MFA::WRefresh()
{
	MISS;

	unsigned long iTimes[4];

	wtTabelle[0]->clear();
	wtTabelle[1]->clear();
	wtTabelle[2]->clear();
	std::string sReturn = WR->Kalk_KOTG(wtTabelle, iTimes);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		//wtStatus->setText("<h3>All looks good :-)</h3> ");
		MISD("#1");
		std::string sTeamID = WR->GetTeamID();
		MISD("#2");
		std::string sTeamName = Bro->GetTeamName(sTeamID);
		MISD("#3");
		Bro->AddRankPlayer(KOTGLIST1, sTeamID, iTimes[0], sTeamName);
		MISD("#4");
		Bro->AddRankPlayer(KOTGLIST2, sTeamID, iTimes[1], sTeamName);
		Bro->AddRankPlayer(KOTGLIST3, sTeamID, iTimes[2], sTeamName);
		Bro->AddRankPlayer(KOTGLIST4, sTeamID, iTimes[3], sTeamName);
		/*
		switch (Bro->AddRankPlayer(KOTGLIST1, WR->Player(), iTime, sRankName))
		{
		case 5: //Slower
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> but slower :-)</h3> ");
			break;
		case 9: //Same
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> same time as before :-)</h3> ");
			break;
		case 10: //Faster
			wtStatus->setText("<h3>Welcome back " + sRankName + ", nice run: " + sTime(iTime) + " -> faster then your last :-)</h3> ");
			break;
		case 15: //New Player
			wtStatus->setText("<h3>Welcome to the Leaderboard " + sRankName + ": " + sTime(iTime) + ":-)</h3> ");
			break;
		default: //Should not happen
			wtStatus->setText("<h3>WHAT HAPPEND?</h3> ");
		}		
		*/
		MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}

	MISE;
}
