//#define DF_Debug

#include "..\..\incl\Broker.h" 
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"
#include "..\..\incl\WEB_Analyser\WEB_EEE.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_CONTAINER_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Event.h"

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <string>


broker *(WEB_Container::Bro) = NULL;

WEB_Container::WEB_Container(const Wt::WEnvironment& env)
	: WApplication(env)
{
	MISS;
	if (!env.getParameterValues("PARAM").empty())
	{
		const std::string *PARA = (env.getParameter("PARAM"));
		sPARA.assign(PARA->c_str());
	}
	if (sPARA == "DEBUG")
	{
		MISERROR("DEBUG ON");
		WA_Debug = true;
		ReNewTaps();
	}
	if (sPARA == "ADMIN")
	{
		MISERROR("ADMIN ON");
		MISERROR("DEBUG ON");
		WA_Admin = true;
		WA_Debug = true;
		ReNewTaps();
	}
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("SLR - Replay Analyser");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));

	MISD("#3");	

	EEE = new WEB_EEE(this);
	//Event = new WEB_Event(this, 100); //EVENT NR
	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");
	
	MISD("#4");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	waLink = new Wt::WAnchor();
	waLink->setText("Switch to Tome Fight Maker");
	waLink->setLink(Wt::WLink(WebTome));
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Replay Analyser</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)), 1, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)),2,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)),3,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::tToolbar)),4,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::sToolbar)), 5, 0);

	MISD("#5");

	Wt::WColor wTemp;

	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#6");

	if (Bro->L_getEEEStatus() != 10 || sPARA == "SSS")
		WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "SSS", *EEE->cMain, EEE);

//	if (Bro->L_getEventStatus(0) < 10 || sPARA == "EVENT") //EVENT NR
//		WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "EVENT", *Event->cMain, Event);

	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Head", *this->Head->cMain, this->Head);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Deck", *this->Deck->cMain, this->Deck);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Acti", *this->Acti->cMain, this->Acti);
	
	WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() -2);	
	if (Bro->L_getEEEStatus() != 10)WEB_Toolbar::sToolbar->setCurrentIndex(0);
	if (Bro->L_getEventStatus(0) < 10)WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();

	MISD("#7");

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

		if (NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			MISD("#NewReplay");
			wtStatus->setText("PMV OK \n");
			Bro->L_ReplayPlus();
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");

		WRefresh();
		WEB_Toolbar::updateFrame();

	});

	MISE;
}


WEB_Container::~WEB_Container()
{
	MISS;
	MISE;
}

void WEB_Container::WRefresh()
{
	MISS;
	MISE;
}

