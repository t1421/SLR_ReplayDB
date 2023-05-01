//#define DF_Debug

#include "..\..\incl\Broker.h" 
#include "..\..\incl\WEB\WEB_Utility.h"
#include "..\..\incl\WEB\WEB_MD.h"
#include "..\..\incl\WEB\WEB_ME.h"
#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_CONTAINER.h"

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <string>


broker *(MISCONTAINER::Bro) = NULL;

MISCONTAINER::MISCONTAINER(const Wt::WEnvironment& env)
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
		MISERROR("DEBUG ON")
		WA_Debug = true;
		ReNewTaps();
	}
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("SLR - Replay Checker");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));

	MISD("#3");	

	MD = new WEB_MD(this);	
	ME = new WEB_ME(this);
	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");
	
	MISD("#4");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Replay Checking</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)),1,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)),2,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::tToolbar)),3,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::sToolbar)), 4, 0);

	MISD("#5");

	Wt::WColor wTemp;

	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#6");

	if (Bro->L_getBOTRankMode(VornskrLIST) <10
		|| sPARA == "BETA")WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Vornskr", *MD->cMain, MD);

	if (Bro->L_getBOTRankMode(BOT4LIST) <10
		|| sPARA == "BOT4")WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "BOT4", *ME->cMain, ME);

	//WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Analyser", *cMainAnalyser, this);

	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Head", *this->Head->cMain, this->Head);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Deck", *this->Deck->cMain, this->Deck);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Acti", *this->Acti->cMain, this->Acti);
	
	//WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() -1);	
	WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() - 2);
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
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");

		WRefresh();
		WEB_Toolbar::updateFrame();

	});

	MISE;
}


MISCONTAINER::~MISCONTAINER()
{
	MISS;
	MISE;
}

void MISCONTAINER::WRefresh()
{
	MISS;
	MISE;
}

