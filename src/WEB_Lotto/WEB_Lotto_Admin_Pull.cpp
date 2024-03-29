//#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Pull.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WComboBox.h>
#include <Wt/WText.h>

#define Card_Size_X 185 / 2
#define Card_Size_Y 255 / 2

broker *(WEB_Lotto_Admin_Pull::Bro) = NULL;


WEB_Lotto_Admin_Pull::WEB_Lotto_Admin_Pull(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;


	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();

	wbBooster = new Wt::WPushButton("Open Booster");
	wbMap = new Wt::WPushButton("Pull Map");
	wlMapName = new Wt::WLineEdit();
	
	wtPullWeek = new Wt::WText();;

	MISD("#2");
	
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPullWeek)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbMap)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlMapName)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbBooster)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	
	MISD("#3");

	MISD("#4");

	wbBooster->clicked().connect(std::bind([=]() {
		PullBooster();
	}));
	wbMap->clicked().connect(std::bind([=]() {
		PullMap();
	}));

	MISD("#5");

	WRefresh();
	MISD("#6");
	
	
	MISE;
}

void WEB_Lotto_Admin_Pull::WRefresh()
{
	MISS;
	unsigned int iRow = 0;
	unsigned int iCol = 0;

	wtTabelle->clear();

	LottoWeek *PullWeek = Bro->getPullWeek();
	
	if (PullWeek->iWeek == 0)return;

	wtPullWeek->setText("Pull Week " + std::to_string(PullWeek->iWeek)
		+ " Pulled Cards: " + std::to_string(PullWeek->vCardsPulled.size())
		+ " (" + std::to_string(PullWeek->vCardsPulled.size() / 8) + ")"
	);
	

	//wcMaps->setCurrentIndex(0);
	for (unsigned int i = 0; i < Con->vMaps.size(); i++)if (atoi(entry(Con->vMaps[i], 0).c_str()) == PullWeek->iMapPull) wlMapName->setText(Con->vMaps[i]);

	for each(std::string sCard in PullWeek->vCardsPulled)
	{
		MISD(std::to_string(iCol) + sCard);
		MISD(Bro->J_GetLottoImg(sCard, 1));
		wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DrawImg(Bro->J_GetLottoImg(sCard, 1), Card_Size_X, Card_Size_Y))));
				
		if (iCol == 8)
		{
			iCol = 0;
			iRow++;
		}
		//else iCol++;
	}
	MISE;
}

/*
void WEB_Lotto_Admin_Pull::CardPulled()
{
	MISS;
	if (wlCardName->text() == "") return;
	
	Bro->getPullWeek()->AddPull(WSTRINGtoSTRING(wlCardName->text()));
	wlCardName->setText("");
	WRefresh();
	Bro->postChatEventMIS("Pull");
	MISE;
}
*/

void WEB_Lotto_Admin_Pull::PullBooster()
{
	MISS;
	Bro->getPullWeek()->OpenBooster();
	WRefresh();
	Bro->postChatEventMIS("Pull");
	MISE;
}

void WEB_Lotto_Admin_Pull::PullMap()
{
	MISS;
	Bro->getPullWeek()->setMap(atoi(entry(Bro->getPullWeek()->OpenMap(Con->vMaps), 0).c_str()));
	WRefresh();
	Bro->postChatEventMIS("Pull");
	MISE;
}