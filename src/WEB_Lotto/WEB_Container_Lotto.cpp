#define DF_Debug

#define _CRT_SECURE_NO_WARNINGS

#include "..\..\incl\Broker.h" 
#include "..\..\incl\Utility.h"
#include "..\..\incl\LOAD.h"
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"

#include "..\..\incl\Replay.h" 

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <string>


broker *(WEB_Container_Lotto::Bro) = NULL;

WEB_Container_Lotto::WEB_Container_Lotto(const Wt::WEnvironment& env)
	: WApplication(env)
{
	MISS;

	FillMapVector();

	MISD("#0");

	std::string sAdmin = sGetParam(env, "Admin");	
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("Lotto");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));

	MISD("#3");	

	Admin = new WEB_Lotto_Admin(this);
	for each (LottoWeek* W in Bro->vWeek)
		if(W->iStatus > 0)
		Weeks.push_back(new WEB_Lotto_Week(this, W));
	
	MISD("#4");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();	
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Lotto</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::tToolbar)),1,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::sToolbar)), 2, 0);

	MISD("#5");

	Wt::WColor wTemp;

	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#6");

	for (int i = Weeks.size() - 1; i >= 0; i--)
	{		
		MISD(i);
		ToolBarButton(WEB_Toolbar::bToolbar.size(), std::to_string(Weeks[i]->BroWeek->iWeek), *Weeks[i]->cMain, Weeks[i]);
	}
	if (sAdmin == Bro->L->sAdminKey)WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Admin", *Admin->cMain, Admin);
		
	if(WEB_Toolbar::bToolbar.size()>0)WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();

	MISD("#7");	
	connect();
	MISE;
}


WEB_Container_Lotto::~WEB_Container_Lotto()
{
	MISS;
	disconnect();
	MISE;
}

void WEB_Container_Lotto::WRefresh()
{
	MISS;
	MISE;
}

void WEB_Container_Lotto::FillMapVector()
{
	MISS;
	vMaps.push_back("0; None");
	vMaps.push_back("8; Siege of Hope");
	vMaps.push_back("20; The Treasure Fleet");
	vMaps.push_back("22; The Soultree");
	vMaps.push_back("32; Behind Enemy Lines");
	vMaps.push_back("45; Encounters with Twilight");
	vMaps.push_back("57; Defending Hope");
	vMaps.push_back("9; Crusade");
	vMaps.push_back("18; Sunbridge");
	vMaps.push_back("21; The Insane God");
	vMaps.push_back("24; Nightmare Shard");
	vMaps.push_back("44; Nightmare's End");
	vMaps.push_back("10; Bad Harvest");
	vMaps.push_back("19; The Dwarven Riddle");
	vMaps.push_back("25; The Guns of Lyr");
	vMaps.push_back("26; King of the Giants");
	vMaps.push_back("29; Titans");
	vMaps.push_back("37; Ascension");
	vMaps.push_back("60; Passage to Darkness");
	vMaps.push_back("88; Mo");
	vMaps.push_back("84; Ocean");
	vMaps.push_back("99; Orecle");
	vMaps.push_back("56; Convoy");
	vMaps.push_back("35; Slave Master");
	vMaps.push_back("74; Blight");
	vMaps.push_back("98; Raven's End");
	vMaps.push_back("100; Empire");
}

void WEB_Container_Lotto::connect()
{
	MISS;
	if (Bro->W->WW)
		if (Wt::WApplication::instance()->updatesEnabled() == false)
			if (Bro->W->WW->connect
			(this, std::bind(&WEB_Container_Lotto::processChatEvent, this, std::placeholders::_1)))
				Wt::WApplication::instance()->enableUpdates(true);
	MISE;
}

void WEB_Container_Lotto::disconnect()
{
	MISS;
	if (Bro->W->WW->disconnect(this))
	{
		MISD("#1");
		Wt::WApplication::instance()->enableUpdates(false);
	}
	MISE;
}



void WEB_Container_Lotto::processChatEvent(const MISEvent& event)
{
	MISS;
	MISD(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);

	if (event.Value1_ == "Pull" && WEB_Toolbar::sToolbar->currentIndex() < Weeks.size())
	{
		if (WEB_Toolbar::bToolbar[WEB_Toolbar::sToolbar->currentIndex()]->text() == std::to_string(Bro->getPullWeek()->iWeek))
		{
			updateFrame();
		}
	}

	if (event.Value1_ == "UpdateWeek" && WEB_Toolbar::sToolbar->currentIndex() < Weeks.size())
	{
		MISD(WSTRINGtoSTRING(WEB_Toolbar::bToolbar[WEB_Toolbar::sToolbar->currentIndex()]->text()));
		
		if (WEB_Toolbar::bToolbar[WEB_Toolbar::sToolbar->currentIndex()]->text() == event.Value2_)
		{
			updateFrame();
		}
	}

	//if (event.Value1_ == "AddDellWeek")

	WApplication *app = WApplication::instance();
	app->triggerUpdate();

	//if (sParamDebug == "1")Debug->UpdateMes(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);

	MISE;
}


std::string WEB_Container_Lotto::getMapName(unsigned int iMap)
{
	for (std::string M : vMaps)	if (atoi(entry(M, 0).c_str()) == iMap)return M;
	return "";
}