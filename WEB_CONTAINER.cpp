#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_MA.h"
#include "WEB_MB.h"
#include "WEB_MC.h"

#include "WEB_CONTAINER.h"

broker *(MISCONTAINER::Bro) = NULL;

MISCONTAINER::MISCONTAINER(const Wt::WEnvironment& env)
	: WApplication(env)
{
	MISS;

	MISD("#1");
	auto bootstrapTheme = std::make_shared<WBootstrapTheme>();
	bootstrapTheme->setVersion(BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);

	//bMobile = env.agentIsMobileWebKit();

	WApplication::instance()->setTitle("SLR - BOT Checker");

	WApplication::instance()->useStyleSheet(WLink("./resources/main.css"));

	MISD("#3");	
	MA = new WEB_MA(this);	
	MB = new WEB_MB(this);
	MC = new WEB_MC(this);

	wtMap = new WText(" ");
	wtDif = new WText(" ");
	wtTime = new WText(" ");
	wtActions = new WText(" ");

	wfuDropZone = new WFileUpload();
	wtStatus = new WText("Waiting for Replay");	
	
	MISD("#4");
	WGridLayout *TempGrid = new WGridLayout();
	WGridLayout *ReplayInfoGrid = new WGridLayout();
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	ReplayInfo = new WContainerWidget();
	
	GlobaelContainer->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	ReplayInfo->setLayout(std::unique_ptr<WGridLayout>(std::move(ReplayInfoGrid)));

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h2><b>Replay Checking</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)),1,0,0,0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)),2,0,0,0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(tToolbar)),3,0,0,2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(sToolbar)), 4, 0,0,2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(ReplayInfo)), 0, 1, 4, 0);

	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Map: "))), 0, 0);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Difficulti: "))), 1, 0);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Playtime: "))), 2, 0);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Actions: "))), 3, 0);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 0, 1);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtDif)), 1, 1);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 2, 1);
	ReplayInfoGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtActions)), 3, 1);
	
	TempGrid->setColumnStretch(0, 5);
	TempGrid->setColumnStretch(1, 95);
	ReplayInfoGrid->setColumnStretch(0, 5);
	ReplayInfoGrid->setColumnStretch(1, 95);

	MISD("#5");

	WColor wTemp;

	wTemp = WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	

	MISD("#6");
	WEB_Toolbar::ToolBarButton(0, "BOT1", *MA->cMain, MA);
	WEB_Toolbar::ToolBarButton(1, "BOT2", *MB->cMain, MB);
	WEB_Toolbar::ToolBarButton(2, "BOT3", *MC->cMain, MC);
	WEB_Toolbar::sToolbar->setCurrentIndex(2);
	WEB_Toolbar::updateToolbar();

	MISD("#7");

	wfuDropZone->setFilters(".pmv");

	wfuDropZone->changed().connect([=] 
	{
		wfuDropZone->upload();
		wtStatus->setText("New File \n");
	});
	wfuDropZone->fileTooLarge().connect([=] 
	{
		wtStatus->setText("File is too large. \n");
	});

	wfuDropZone->uploaded().connect([=] 
	{
		wtStatus->setText("Upload done \n");

		if (NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			wtStatus->setText("PMV OK \n");
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");

		WRefresh();
		updateFrame();		

	});

	MISE;
}


MISCONTAINER::~MISCONTAINER()
{
	MISS;
	delete MA;
	delete MB;
	delete MC;
	MISE;
}

void MISCONTAINER::WRefresh()
{
	MISS;

	wtMap->setText(MapName());
	wtTime->setText(Time());
	wtDif->setText(to_string(Difficulty()));
	wtActions->setText(to_string(CountActions()));	

	MISE;
}

