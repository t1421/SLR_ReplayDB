#define DF_Debug

#define _CRT_SECURE_NO_WARNINGS

#include "..\..\incl\Broker.h" 
#include "..\..\incl\Utility.h"
#include "..\..\incl\LOAD.h"
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"
#include "..\..\incl\WEB_King\WEB_Container_King.h"
#include "..\..\incl\WEB_King\WEB_King_Player.h"
#include "..\..\incl\WEB_King\WEB_King_Game.h"

#include "..\..\incl\DataTypes.h"

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <string>


broker *(WEB_Container_King::Bro) = NULL;

WEB_Container_King::WEB_Container_King(const Wt::WEnvironment& env)
	: WApplication(env) , WA(new WEB_Analyser()), WA_Admin(false)
{
	MISS;

	std::string sPARA = sGetParam(env, "PARAM");

	if (sPARA == Bro->L->sAdminKey && Bro->L->sAdminKey != "")
	{
		MISERROR("ADMIN ON");
		MISERROR("DEBUG ON");
		WA_Admin = true;
	}
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("King");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));

	MISD("#3");	

	Player = new WEB_King_Player(this,WA);
	Game = new WEB_King_Game(this,WA);
	
	MISD("#4");
	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");

	MISD("#4");
	wfuDropZone->setFilters(".pmv");

	wfuDropZone->changed().connect([=]
		{
			MISD("#changed");
			wfuDropZone->upload();
			wtStatus->setText("New File \n");
		});
	wfuDropZone->fileTooLarge().connect([=]
		{
			MISD("#fileTooLarge");
			wtStatus->setText("File is too large. \n");
		});

	wfuDropZone->uploaded().connect([=]
		{
			MISD("#uploaded");
			wtStatus->setText("Upload done \n");

			if (WA->NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))			
			{
				MISD("#NewReplay");
				wtStatus->setText("PMV OK \n");				
				KingGame KG = WA->KingData();
				
				if (KG.PlayerName1 == "" || KG.PlayerName2 == "")
				{
					MISD("#Error bei Spieler Ermitlung");
					wtStatus->setText("Error bei Spieler Ermitlung");
				}
				else if (KG.PlayerWinner == "")
				{
					MISD("#Error bei Winner");
					wtStatus->setText("Error bei Winner");
				}
				else if (Bro->DublicateKingReplay(KG.ReplayID))
				{
					MISD("#Error DublicateKingReplay");
					wtStatus->setText("Error DublicateKingReplay");
				}
				else
				{
					MISD("#NewReplay");
					WA->SaveReplay(Bro->L->sPMV_KING_PATH + std::to_string(WA->getReplayHashV2()) + ".pmv");
					Bro->vKingGames.push_back(KG);
					Bro->SaveKing();
					Bro->KalkKingPlayers();
					Bro->SaveKing();
					Bro->postChatEventMIS("UpdateKing");
				}
				
			}
			else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");

			WRefresh();

		});
	
	MISD("#5");
	
	MISD("#8");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();	
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));

	
	
	MISD("#10");
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>King</b></h2>"))),0,0,0,1);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)), 1, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)), 1, 1);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Player->cMain)),2,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Game->cMain)), 2, 1);

	MISD("#9");
	if (!WA_Admin)
	{
		wtStatus->hide();
		wfuDropZone->hide();
	}
	MISD("#11");

	Wt::WColor wTemp;

	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#99");	
	connect();
	MISE;
}


WEB_Container_King::~WEB_Container_King()
{
	MISS;
	disconnect();
	MISE;
}



void WEB_Container_King::connect()
{
	MISS;
	if (Bro->W->WW)
		if (Wt::WApplication::instance()->updatesEnabled() == false)
			if (Bro->W->WW->connect
			(this, std::bind(&WEB_Container_King::processChatEvent, this, std::placeholders::_1)))
				Wt::WApplication::instance()->enableUpdates(true);
	MISE;
}

void WEB_Container_King::disconnect()
{
	MISS;
	if (Bro->W->WW->disconnect(this))
	{
		MISD("#1");
		Wt::WApplication::instance()->enableUpdates(false);
	}
	MISE;
}


void WEB_Container_King::processChatEvent(const MISEvent& event)
{
	MISS;
	MISD(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);
	
	if (event.Value1_ == "UpdateKing")
	{
		Player->WRefresh();
		Game->WRefresh();
	}

	WApplication *app = WApplication::instance();
	app->triggerUpdate();

	MISE;
}

void WEB_Container_King::WRefresh()
{
	MISS;
	Player->WRefresh();
	Game->WRefresh();
	MISE;
}

