//#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_MA.h"
#include "WEB_MB.h"

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
	MA = new WEB_MA();	
	MB = new WEB_MB();
	
	MISD("#4");
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	toolBar = GlobaelContainer->addWidget(Wt::cpp14::make_unique<Wt::WToolBar>());
	AnzeigeFrame = GlobaelContainer->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	Stack = new WStackedWidget();
	AnzeigeFrame->addWidget(std::unique_ptr<WContainerWidget>(std::move(Stack)));

	//GlobaelContainer->setMaximumSize(900, 950);
	WColor wTemp;

	wTemp = WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#5");

	ToolBarButton(0, "BOT1", *MA->cMain);
	ToolBarButton(1, "BOT2", *MB->cMain);
	Stack->setCurrentIndex(1);
	updateToolbar(1);

	//GlobaelContainer->addWidget(std::unique_ptr<WContainerWidget>(std::move(MA->cMain)));
	//GlobaelContainer->addWidget(std::unique_ptr<WContainerWidget>(std::move(MB->cMain)));

	MISE;
}


MISCONTAINER::~MISCONTAINER()
{
	MISS;
	delete MA;
	delete MB;
	MISE;
}

void MISCONTAINER::ToolBarButton(int Index, string Name, WContainerWidget &CON)
{
	MISS;
	button[Index] = new Wt::WPushButton();
	button[Index]->setText(Name);
	toolBar->addButton(std::unique_ptr<Wt::WPushButton>(button[Index]));
	button[Index]->clicked().connect(std::bind([=]() {				
		Stack->setCurrentIndex(Index);
		updateToolbar(Index);
	}));

	Stack->insertWidget(Index, std::unique_ptr<WContainerWidget>(std::move(&CON)));
	MISE;
}

void MISCONTAINER::updateToolbar(int iAktiv)
{
	MISS;
	string sCSS;
	for (int i = 0; i < MaxRegister; i++)
	{
		sCSS = WSTRINGtoSTRING(button[i]->styleClass());

		if (sCSS.find("button1") != sCSS.npos)sCSS.erase(sCSS.find("button1"), 7);
		if (sCSS.find("button0") != sCSS.npos)sCSS.erase(sCSS.find("button0"), 7);

		if( i == iAktiv)sCSS = "button1 " + sCSS;
		else sCSS = "button0" + sCSS;
		
		button[i]->setStyleClass(sCSS);
	}		
	

	MISE;
}
