//#define DF_Debug

#include "..\..\incl\Broker.h" 
//#include "..\..\incl\DataTypes.h" 

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

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <Wt/WTable.h>
#include <Wt/WLineEdit.h>
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
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Welcome to the Tome Fight Maker</b></h2>"))),0,0);
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
	
	WApplication *app = WApplication::instance();
	/*
	if (event.Value1_ == "Volume")
	{
		DV->setVolume(atoi(event.Value2_.c_str()), atoi(event.Value3_.c_str()));
	}

	if (event.Value1_ == "Switch")
	{
		DV->setAktive(atoi(event.Value2_.c_str()), event.Value3_ == "1");
	}

	if (event.Value1_ == "MA_Kopf")
	{
		MA->Update_Kopf(event.Value3_);
		MA->Update_Note(atoi(event.Value4_.c_str()));
	}

	if (event.Value1_ == "MA_DS")
	{
		MA->Update_DS(event.Value2_);
	}

	if (event.Value1_ == "INIT")
	{
		if (event.Value2_ == "LastInit")DB->UpdateLastInit(event.Value3_);
		if (event.Value2_ == "Ordner")DB->UpdateOrdner(event.Value3_);
		if (event.Value2_ == "LastFullInit")DB->UpdateLastFullInt(event.Value3_);
	}

	if (event.Value1_ == "Pos")
	{
		MA->Update_Pos(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "InStart")
	{
		FA->setVolume(0, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "OutStart")
	{
		FA->setVolume(1, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "Fade")
	{
		FA->setVolume(2, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "JumpFade")
	{
		FA->setVolume(3, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "FadeDelay")
	{
		FA->setVolume(4, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PlayMode")
	{
		FA->setPlayMode(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PL_ANZ")
	{
		PL->Neue_Anzahl_WS(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PL_Song")
	{
		PL->Update_WS_Row(atoi(event.Value2_.c_str()), event.Value3_);
	}

	if (event.Value1_ == "InitWD")
	{
		DV->Init_WD_Row(atoi(event.Value2_.c_str()), event.Value3_);
	}

	if (event.Value1_ == "MA_Info")
	{
		MA->Update_DS(event.Value2_);
	}

	if (event.Value1_ == "COLOR_NEW")
	{
		int iColorIndex = atoi(event.Value2_.c_str());
		istringstream iss = istringstream(event.Value3_);
		string sColor;

		for (int i = 0; getline(iss, sColor, '_') && i < 3; i++)
		{
			if (sColor.length() == 0) break;
			Colors[cSOL][iColorIndex][i] = atoi(sColor.c_str());
		}
	}

	if (event.Value1_ == "KOPF_NEW")
	{
		MA->sCover_ID[cSOL] = event.Value2_;
	}

	if (event.Value1_ == "FADE_SONG")
	{
		int iStatus = atoi(event.Value2_.c_str());
		if (iStatus <= 0) iStatus = 1;
		if (iStatus >= 100) iStatus = 100;
		setFadeStatus(iStatus, Stack->currentIndex());

		if (Stack->currentIndex() == 2)MA->setFadeStatus(iStatus);


		if (iStatus >= 99)
		{
			for (int i = 0; i < MaxColorIndex; i++)
				for (int j = 0; j < 3; j++)
					Colors[cIST][i][j] = Colors[cSOL][i][j];

			for (int i = 0; i < MaxRegister; i++) setFadeStatus(100, i);
			MA->setFadeStatus(100);

		}
	}

	if (event.Value1_ == "SAVE")
	{
		Bro->L_TriggerSave();
	}

	if (event.Value1_ == "FP")
	{
		if (event.Value2_ == "FP_Value")FP->UpdateFP(event.Value3_);
	}

	if (event.Value1_ == "TH")
	{
		if (event.Value2_ == "FP")TH->UpdateFP(event.Value3_);
		if (event.Value2_ == "IN")TH->UpdateIN(event.Value3_);
		if (event.Value2_ == "TH")TH->UpdateTH(event.Value3_);
		if (event.Value2_ == "DB")TH->UpdateDB(event.Value3_);
	}

	if (event.Value1_ == "MA_Color")
	{
		MA->UpdateColorValues(event.Value2_, event.Value3_);
	}
	*/
	app->triggerUpdate();
	Debug->UpdateMes(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);

	MISE;
}

std::string WEB_Container_Tome::sGetParam(const Wt::WEnvironment& env, std::string sParam)
{
	MISS;
	if (!env.getParameterValues(sParam).empty())
	{
		const std::string *PARA = (env.getParameter(sParam));
		MISE;
		return PARA->c_str();
	}
	MISEA("V2");
	return "";
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
					4,
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
	if (Bro->vTomeGames[BroGameID]->bCheckPlayer(WSTRINGtoSTRING(Login->wlPlayerID->text())) == false
		|| Login->wlPlayerID->text() == "")
	{
		MISEA("Not found");
		return "";
	}

	MISE;
	return WSTRINGtoSTRING(Login->wlPlayerID->text());
}