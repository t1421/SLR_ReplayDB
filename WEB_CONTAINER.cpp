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

	WApplication::instance()->setTitle("SLR - Action counter");

	WApplication::instance()->useStyleSheet(WLink("./resources/main.css"));
	WApplication::instance()->useStyleSheet(WLink("./resources/opacity.css"));

	MISD("#3");	
	MA = new WEB_MA();	
	MB = new WEB_MB();
	
	MISD("#4");
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	//GlobaelContainer->setMaximumSize(900, 950);
	WColor wTemp;

	wTemp = WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);
	 
	MISD("#5");

	//GlobaelContainer->addWidget(std::unique_ptr<WContainerWidget>(std::move(MA->cMain)));
	GlobaelContainer->addWidget(std::unique_ptr<WContainerWidget>(std::move(MB->cMain)));

	MISE;
}
