//#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"

#include "..\..\incl\WEB_Tome\WEB_Container_Tome.h"

#include "..\..\incl\WEB_Tome\WEB_Tome_Admin.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Debug.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Public.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Leave.h"
#include "..\..\incl\WEB_Tome\Tome_Game.h"

#include "..\..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTable.h>
#include <Wt/WLineEdit.h>
#include <Wt/WButtonGroup.h>
#include <string>
#include <algorithm>

broker *(WEB_Container_Tome::Bro) = NULL;

bool compareBoosters(const Tome_Booster * a, const Tome_Booster * b) { return a->iLfdnr > b->iLfdnr; }

WEB_Container_Tome::WEB_Container_Tome(const Wt::WEnvironment& env)
	: WApplication(env), BroGameID(-1)
{
	MISS;
	sParamGameID = sGetParam(env, "gameID");
	sParamAdminID = sGetParam(env, "adminID");
	sParamPlayerID = sGetParam(env, "playerID");
	sParamDebug = sGetParam(env, "debug");
	
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("SLR - Tome Fight Maker");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));
	WApplication::instance()->declareJavaScriptFunction("CopyToClip", 
		"function(text) { navigator.clipboard.writeText(text) }");

	MISD("#3");

	Wt::WColor wTemp;
	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);
	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);
	
	MISD("#4");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	waLink = new Wt::WAnchor();
	waLink2 = new Wt::WAnchor();
	waLink->setText("Switch to Replay Analyser");
	waLink2->setText("How to Use Tome Fight Maker");
	waLink->setLink(Wt::WLink(WebAnalyser));
	waLink2->setLink(Wt::WLink("https://youtu.be/sMLBZydTQPE"));

	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));

	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)), 1, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Tome Fight Maker</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink2)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)),3,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)), 4, 0);	

	MISD("#6");

	Admin  = new WEB_Tome_Admin(this);
	Login  = new WEB_Tome_Login(this);
	Player = new WEB_Tome_Player(this);
	Public = new WEB_Tome_Public(this);
	Leave = new WEB_Tome_Leave(this);
	
	
	MISD("#7");

	WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Login",  *Login->cMain,  Login);
	WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Public", *Public->cMain, Public);
	WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Player", *Player->cMain, Player);
	WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Admin",  *Admin->cMain,  Admin);
	WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Leave", *Leave->cMain, Leave);
	

	MISD("#8");

	WEB_Toolbar::bDisable[0] = false;
	WEB_Toolbar::bDisable[1] = true;
	WEB_Toolbar::bDisable[2] = true;
	WEB_Toolbar::bDisable[3] = true;
	WEB_Toolbar::bDisable[4] = true;
	

	if (sParamDebug == "1")
	{
		Debug = new WEB_Tome_Debug(this);
		WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Debug", *Debug->cMain, Debug);
		WEB_Toolbar::bDisable[5] = false;		
	}

	WEB_Toolbar::sToolbar->setCurrentIndex(0);	
	WEB_Toolbar::updateToolbar();
	//if (Bro->L_getBOTRankMode(BOT4LIST) <10)WEB_Toolbar::sToolbar->setCurrentIndex(0); 
	//WEB_Toolbar::updateToolbar();

	
	MISD("#9");
	
	if(sParamGameID!="")
		Login->Parameter(sParamGameID, sParamPlayerID, sParamAdminID);

	MISE;
}


WEB_Container_Tome::~WEB_Container_Tome()
{
	MISS;
	MISE;
}

void WEB_Container_Tome::WRefresh()
{
	MISS;
	WEB_Toolbar::updateToolbar();
	MISE;
}

void WEB_Container_Tome::connect()
{
	MISS;	
	if (Bro->W->WW)
		if(Wt::WApplication::instance()->updatesEnabled() == false)
		if (Bro->W->WW->connect
		(this, std::bind(&WEB_Container_Tome::processChatEvent, this, std::placeholders::_1)))
			Wt::WApplication::instance()->enableUpdates(true);	
	MISE;
}

void WEB_Container_Tome::disconnect()
{
	MISS;
	if (Bro->W->WW->disconnect(this))
	{
		MISD("#1");
		Wt::WApplication::instance()->enableUpdates(false);
	}
	MISE;
}

void WEB_Container_Tome::processChatEvent(const MISEvent& event)
{
	MISS;
	MISD(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);
	if (BroGameID == -1)
	{
		MISEA("WTF");
		return;
	}

	if (std::to_string(BroGameID) != event.Value1_)
	{
		MISEA("wrong game");
		return;
	}

	if (event.Value2_ == "booster" && WEB_Toolbar::sToolbar->currentIndex() == 1)
	{
		if (Public->WEB_Toolbar::sToolbar->currentIndex() == 0
			&& Bro->vTomeGames[BroGameID]->bShowBoostersOfPlayer //nur wen opend boosters
			&& Bro->vTomeGames[BroGameID]->bShowPlayers)
			Public->PP->WRefresh();
		if (Public->WEB_Toolbar::sToolbar->currentIndex() == 1
			&& Bro->vTomeGames[BroGameID]->bShowBoosters)
			Public->PB->WRefresh();
		if (Public->WEB_Toolbar::sToolbar->currentIndex() == 2
			&& Bro->vTomeGames[BroGameID]->bShowBoostersOfPlayer)
			Public->PPB->WRefresh();
	}
	if (event.Value2_ == "player")
	{
		if (WEB_Toolbar::sToolbar->currentIndex() == 1
			&& Public->WEB_Toolbar::sToolbar->currentIndex() == 0
			&& Bro->vTomeGames[BroGameID]->bShowPlayers)
			Public->PP->WRefresh();
		if (Public->WEB_Toolbar::sToolbar->currentIndex() == 1
			&& Bro->vTomeGames[BroGameID]->bShowBoosters)
			Public->PB->WRefresh();
		if (WEB_Toolbar::sToolbar->currentIndex() == 1
			&& Public->WEB_Toolbar::sToolbar->currentIndex() == 2
			&& Bro->vTomeGames[BroGameID]->bShowBoostersOfPlayer)
			Public->PPB->WRefresh();
		if (WEB_Toolbar::sToolbar->currentIndex() == 2)
			//&& getPlayerID() == event.Value3_
			Player->WRefresh();
	}
	if (event.Value2_ == "global")
		switch (WEB_Toolbar::sToolbar->currentIndex())
		{
		case 1: 
			Public->WRefresh();
			switch (Public->WEB_Toolbar::sToolbar->currentIndex())
			{
			case 0: Public->PP->WRefresh();	 break;
			case 1: Public->PB->WRefresh();	 break;
			case 2: Public->PPB->WRefresh(); break;
			}
			break;
		case 2:
			Player->WRefresh();
			break;
		}


	WApplication *app = WApplication::instance();
	app->triggerUpdate();
	
	if(sParamDebug=="1")Debug->UpdateMes(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);

	MISE;
}

void WEB_Container_Tome::DrawBooster(Wt::WTable *wtTabelle, std::vector <Tome_Booster*> vAllBoosters)
{
	MISS;

	std::sort(vAllBoosters.begin(), vAllBoosters.end(), compareBoosters);

	for (unsigned int j = 0; j <vAllBoosters.size(); j++)
	{
		wtTabelle->elementAt(j, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
			DrawImg("./resources/Boosters/" + vAllBoosters[j]->sType + ".png",
				Card_Size_X, Card_Size_Y
			))));

		for (unsigned int k = 0; k < vAllBoosters[j]->vCards.size() && vAllBoosters[j]->vCards[k]->cardId != 0; k++)
		{
			wtTabelle->elementAt(j, k + 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(
				DrawImg(Bro->J_GetImage(
					vAllBoosters[j]->vCards[k]->cardId,
					3,
					3,
					1,
					false),
					Card_Size_X, Card_Size_Y
				))));
		}
	}

	for (unsigned int i = 0; i < wtTabelle->columnCount(); i++) wtTabelle->columnAt(i)->setWidth(75);
	MISE;
}

std::string WEB_Container_Tome::BoosterToFilter(std::vector <Tome_Booster*> vAllBoosters, std::string sName)
{
	MISS;

	std::vector <unsigned int> iCards;
	bool found;
	std::stringstream ssOUT;

	for (unsigned int j = 0; j <vAllBoosters.size(); j++)
	{
		for (unsigned int k = 0; k < vAllBoosters[j]->vCards.size() && vAllBoosters[j]->vCards[k]->cardId != 0; k++)
		{
			found = false;
			for (unsigned int i = 0; i < iCards.size() && found == false; i++)
				found = iCards[i] == vAllBoosters[j]->vCards[k]->cardId;
			
			if (found)continue;
			iCards.push_back(vAllBoosters[j]->vCards[k]->cardId);

		}
	}

	ssOUT << ",{ ";
	ssOUT << "\"name\":\"" << sName << "\",";
	ssOUT << "\"_comment\":\"Your cards for the Tome Event\",";
	ssOUT << "\"text\" : \"ID=0";
	for (unsigned int i = 0; i < iCards.size() ; i++)ssOUT << "|ID="<< iCards[i];
	ssOUT << "\"}";
	
	MISE;
	return ssOUT.str();
}

void WEB_Container_Tome::PublicReset()
{
	MISS;
	Public->sToolbar->setCurrentIndex(3);
	MISE;
}

std::string WEB_Container_Tome::getPlayerID()
{
	MISS;
	if (Bro->vTomeGames[BroGameID]->bCheckPlayer(WSTRINGtoSTRING(Login->wlUserID->text())) == false
		|| Login->wlUserID->text() == ""
		|| Login->gbJoinMode->checkedId() != 1)
	{
		MISEA("Not found");
		return "";
	}

	MISE;
	return WSTRINGtoSTRING(Login->wlUserID->text());
}