#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_SERVER.h"
#include "WEB_MA.h"

#include "WEB_CONTAINER.h"

broker *(MISCONTAINER::Bro) = NULL;

MISCONTAINER::MISCONTAINER(const Wt::WEnvironment& env)
	: WApplication(env)
{
	MISS;

	//WContainerWidget(root());

	//Stack = new WStackedWidget();
	MISD("#1");
	auto bootstrapTheme = std::make_shared<WBootstrapTheme>();
	bootstrapTheme->setVersion(BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);

	//WBootstrapTheme * p_wtTheme = new Wt::WBootstrapTheme();
	//p_wtTheme->setVersion(WBootstrapTheme::Version3);
	//WApplication::instance()->setTheme(p_wtTheme);
	/*
	MISD("agentIsChrome      " + to_string(env.agentIsChrome()));
	MISD("agentIsGecko       " + to_string(env.agentIsGecko()));
	MISD("agentIsIE          " + to_string(env.agentIsIE()));	
	MISD("agentIsIEMobile    " + to_string(env.agentIsIEMobile()));
	MISD("agentIsMobileWebKit" + to_string(env.agentIsMobileWebKit()));
	MISD("agentIsOpera       " + to_string(env.agentIsOpera()));
	MISD("agentIsSafari      " + to_string(env.agentIsSafari()));
	MISD("agentIsSpiderBot   " + to_string(env.agentIsSpiderBot()));
	MISD("agentIsWebKit      " + to_string(env.agentIsWebKit()));
	*/
	bMobile = env.agentIsMobileWebKit();


	WApplication::instance()->setTitle("SDB 8");

	WApplication::instance()->useStyleSheet(WLink("./resources/main.css"));
	WApplication::instance()->useStyleSheet(WLink("./resources/opacity.css"));

	MISD("#3");
	
	MA = new WEB_MA(VVPWSWid_Tabs[0]);	
	
	MISD("#4");
	
	MISD("#5");
	//Fade Array


	MISD("#6");
	//Inital Werte Holen

	
	MISE;
}
 
MISCONTAINER::~MISCONTAINER()
{
	MISE;

	if (Bro->W->WW->disconnect(this))
	{
		MISD("#1");
		Wt::WApplication::instance()->enableUpdates(false);
		
		MISD("#2");
		delete MA;
		MISD("#3");		
	}

	MISE;
}

/*
void MISCONTAINER::startChat()
{
	MISS;
	connect();
	MISD("#0");

	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	GlobaelContainer->setMaximumSize(900, 950);
	toolBar = GlobaelContainer->addWidget(Wt::cpp14::make_unique<Wt::WToolBar>());

	AnzeigeFrame = GlobaelContainer->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());
	if(bMobile) AnzeigeFrame->setMaximumSize(550, 900);
	else AnzeigeFrame->setMaximumSize(900, 900); 
	AnzeigeFrame->setOverflow(Wt::Overflow::Auto); //This will enable scroll bar feature to the widget
	//doJavaScript(AnzeigeFrame->jsRef() + ".scrollTop = " + AnzeigeFrame->jsRef() + ".scrollHeight;"); //Here the widget will move to the bottom side.

	MISD("#1");

	Stack = new WStackedWidget();
	AnzeigeFrame->addWidget(std::unique_ptr<WContainerWidget>(std::move(Stack)));

	MISD("#2");
	 
	ToolBarButton(0, "MA", *MA->cMain);	
	Stack->setCurrentIndex(0);
	 
	MISE;
}
*/
void MISCONTAINER::ToolBarButton(int Index, string Name, WContainerWidget &CON)
{
	MISS;
	button[Index] = new Wt::WPushButton();
	button[Index]->setText(Name);
	toolBar->addButton(std::unique_ptr<Wt::WPushButton>(button[Index]));
	button[Index]->clicked().connect(std::bind([=]() {
		Stack->setCurrentIndex(Index);
	}));

	Stack->insertWidget(Index, std::unique_ptr<WContainerWidget>(std::move(&CON)));
	MISE;
}

