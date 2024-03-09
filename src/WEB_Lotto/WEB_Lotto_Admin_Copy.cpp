#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Copy.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\..\incl\Utility.h"
#include "..\..\incl\CardBaseSMJ.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>


broker *(WEB_Lotto_Admin_Copy::Bro) = NULL;


WEB_Lotto_Admin_Copy::WEB_Lotto_Admin_Copy(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;


	cMain = new Wt::WContainerWidget();
	Wt::WHBoxLayout *TempGrid = new Wt::WHBoxLayout();

	MISD("#1");
	cMain->setLayout(std::unique_ptr<Wt::WHBoxLayout>(std::move(TempGrid)));
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#2");

	wtTabelle1 = new Wt::WTable();
	wtTabelle2 = new Wt::WTable();

	

	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle1)));
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle2)));
	
	MISD("#3");

	FillCards();
	FillMaps();

	MISD("#4");

	MISD("#5");

	WRefresh();

	MISD("#6");
	
	
	MISE;
}
/*
void WEB_Lotto_Admin_Copy::WRefresh()
{
	MISS;

	//wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Save"))));	

	MISE;
}
*/
void WEB_Lotto_Admin_Copy::FillCards()
{
	MISS;

	unsigned int iRow = 0;

	wtTabelle1->clear();
	wtTabelle1->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>CARDS</h3>"))));

	std::vector<std::string> vCards;
	for each (SMJCard * C in Bro->J->SMJMatrix)vCards.push_back(C->cardNameSimple);
	std::sort(vCards.begin(), vCards.end());
	vCards.erase(std::unique(vCards.begin(), vCards.end()), vCards.end());

	for each (std::string C in vCards)
		wtTabelle1->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(C))));

	MISE;
}

void WEB_Lotto_Admin_Copy::FillMaps()
{
	MISS;

	unsigned int iRow = 0;

	wtTabelle2->clear();
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>MAPS</h3>"))));
	wtTabelle2->setMaximumSize(500, 750);
	for each(std::string sMap in Con->vMaps)
		if(sMap!="0; None")wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sMap))));
	
	MISE;
}