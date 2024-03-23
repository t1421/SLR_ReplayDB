#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin.h"
#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Main.h"
#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Pull.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WBreak.h>


broker *(WEB_Lotto_Admin::Bro) = NULL;


WEB_Lotto_Admin::WEB_Lotto_Admin(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");
	Main = new WEB_Lotto_Admin_Main(Con);
	Pull = new WEB_Lotto_Admin_Pull(Con);
	
	MISD("#2");
	cMain = new Wt::WContainerWidget();
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));
	
	MISD("#3");

	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Main", *Main->cMain, Main);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Pull", *Pull->cMain, Pull);

	MISD("#4");

	WEB_Toolbar::updateToolbar();

	MISD("#5");

	WRefresh();
	MISD("#6");
	
	
	MISE;
}
/*
void WEB_Lotto_Admin::WRefresh()
{
	MISS;

	

	MISE;
}

*/