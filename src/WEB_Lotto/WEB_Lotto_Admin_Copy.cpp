#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Copy.h"
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
	
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("8; Siege of Hope"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("20; The Treasure Fleet"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("22; The Soultree"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("32; Behind Enemy Lines"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("45; Encounters with Twilight"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("57; Defending Hope"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("9; Crusade"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("18; Sunbridge"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("21; The Insane God"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("24; Nightmare Shard"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("44; Nightmare's End"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("10; Bad Harvest"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("19; The Dwarven Riddle"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("25; The Guns of Lyr"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("26; King of the Giants"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("29; Titans"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("37; Ascension"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("60; Passage to Darkness"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("88; Mo"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("84; Ocean"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("99; Orecle"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("56; Convoy"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("35; Slave Master"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("74; Blight"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("98; Raven's End"))));
	wtTabelle2->elementAt(iRow++, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("100; Empire"))));



	MISE;
}