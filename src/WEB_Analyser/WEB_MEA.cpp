//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\WEB_Analyser\WEB_MEA.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"

#include <Wt/WTable.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>

broker *(WEB_MEA::Bro) = NULL;

WEB_MEA::WEB_MEA(WEB_Analyser *WR_) : WR(WR_)
{
	MISS;

	cMain = new Wt::WContainerWidget();	
	Wt::WContainerWidget *cTempContainer = new Wt::WContainerWidget();
	Wt::WContainerWidget *cSpacerContainer = new Wt::WContainerWidget();
	Wt::WHBoxLayout *TempBox = new Wt::WHBoxLayout();
		
	MISD("#0");

	wtStatus	= new Wt::WText(" ");
	wtTabelle   = new Wt::WTable();

	cTempContainer->setLayout(std::unique_ptr<Wt::WHBoxLayout>(std::move(TempBox)));
	
	MISD("#1");
	
	
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(cTempContainer)));
	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	TempBox->addWidget(std::unique_ptr<Wt::WWidget>(std::move(cSpacerContainer)));
	
	//cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	MISD("#2");
	cMain->setContentAlignment(Wt::AlignmentFlag::Left);
	cTempContainer->setWidth(900);
	cSpacerContainer->setWidth(50);
	
	MISE;
}

void WEB_MEA::WRefresh()
{
	MISS;
	
	unsigned long iTimes[RankRowStamps] = {0};

	wtTabelle->clear();
	std::string sReturn = WR->Kalk_BOT6(wtTabelle, iTimes);
	
	if (sReturn != "")wtStatus->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
	else
	{
		
		//iTimes[0] = WR->getPlaytime();		
		std::string sTeamID = WR->GetTeamID();
		Bro->AddPlayer(BOT6LIST, sTeamID, WR->getReplayHash(), iTimes);
		wtStatus->setText("<h3>Hello there Team " + Bro->GetTeamName(sTeamID) + " (" + std::to_string(WR->getReplayHash()) + "), nice run :-)</h3> ");
		MISERROR(WSTRINGtoSTRING(wtStatus->text()));
	}
	
	MISE;
}
