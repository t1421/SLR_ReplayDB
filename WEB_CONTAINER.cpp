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
	MA = new WEB_MA();	
	MB = new WEB_MB();
	MC = new WEB_MC();
	
	MISD("#4");
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	GlobaelContainer->addWidget(std::unique_ptr<WWidget>(std::move(tToolbar)));
	AnzeigeFrame = GlobaelContainer->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	
	AnzeigeFrame->addWidget(std::unique_ptr<WWidget>(std::move(sToolbar)));

	WColor wTemp;

	wTemp = WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#5");

	WEB_Toolbar::ToolBarButton(0, "BOT1", *MA->cMain);
	WEB_Toolbar::ToolBarButton(1, "BOT2", *MB->cMain);
	WEB_Toolbar::ToolBarButton(2, "BOT3", *MC->cMain);
	WEB_Toolbar::sToolbar->setCurrentIndex(2);
	WEB_Toolbar::updateToolbar();

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
