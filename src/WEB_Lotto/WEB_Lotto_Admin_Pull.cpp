#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Pull.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>


broker *(WEB_Lotto_Admin_Pull::Bro) = NULL;


WEB_Lotto_Admin_Pull::WEB_Lotto_Admin_Pull(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;


	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();


	MISD("#2");

	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISD("#3");
	


	MISD("#4");

	wtTabelle->columnAt(1)->setWidth(160);

	MISD("#5");

	WRefresh();
	MISD("#6");
	
	
	MISE;
}

void WEB_Lotto_Admin_Pull::WRefresh()
{
	MISS;
	

	MISE;
}

