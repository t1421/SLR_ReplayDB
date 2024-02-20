#define DF_Debug

#define _CRT_SECURE_NO_WARNINGS
#define LottoMaxWeeks 3

#include "..\..\incl\Broker.h" 
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"
//#include "..\..\incl\WEB_Analyser\WEB_ME.h"
//#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"

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

	if (sAdmin == Bro->L_getAdminKey())WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Admin", *Admin->cMain, Admin);
	for (int i = Weeks.size() - 1; i > 0 && i > Weeks.size() - LottoMaxWeeks; i--)
	{
		MISD(i);
		ToolBarButton(WEB_Toolbar::bToolbar.size(), std::to_string(i), *Weeks[i]->cMain, Weeks[i]);
	}
	
		
	//WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() -2);	
	if(WEB_Toolbar::bToolbar.size()>0)WEB_Toolbar::sToolbar->setCurrentIndex(0);
	WEB_Toolbar::updateToolbar();

	MISD("#7");
	
	MISE;
}


WEB_Container_Lotto::~WEB_Container_Lotto()
{
	MISS;
	MISE;
}

void WEB_Container_Lotto::WRefresh()
{
	MISS;
	MISE;
}

Wt::WImage* WEB_Container_Lotto::SimpelIMG(std::string cardNameSimple, unsigned int iColor)
{
	MISS;

	for each (SMJLottoCard* C in SMJLottoMatrix)
	{
		if (C->cardNameSimple == cardNameSimple)
		{
			MISEA("Found");
			return C->Img[iColor];
		}
	}

	SMJLottoMatrix.push_back(new SMJLottoCard(
		cardNameSimple,
		DrawImg(Bro->J_GetLottoImg(cardNameSimple, 0), 185, 255),
		DrawImg(Bro->J_GetLottoImg(cardNameSimple, 1), 185, 255)
	));

	MISEA("NEW");
	return SMJLottoMatrix[SMJLottoMatrix.size() - 1]->Img[iColor];;
}
