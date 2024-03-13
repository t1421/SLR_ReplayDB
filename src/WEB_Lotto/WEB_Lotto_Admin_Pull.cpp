#define DF_Debug

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


broker *(WEB_Lotto_Admin_Pull::Bro) = NULL;


WEB_Lotto_Admin_Pull::WEB_Lotto_Admin_Pull(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;


	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();

	wbAddCard = new Wt::WPushButton("Add Card");
	wlCardName = new Wt::WLineEdit();
	wcMaps = new Wt::WComboBox();
	wtPullWeek = new Wt::WText();;

	MISD("#2");
	
	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPullWeek)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wcMaps)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbAddCard)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wlCardName)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	
	MISD("#3");
	
	for each(std::string sMap in Con->vMaps)wcMaps->addItem(sMap);
	

	MISD("#4");

	wbAddCard->clicked().connect(std::bind([=]() {
		CardPulled();
	}));
	wlCardName->enterPressed().connect(std::bind([=]() {
		CardPulled();
	}));

	wcMaps->changed().connect(std::bind([=]() {
		Bro->getPullWeek()->setMap(atoi(entry(WSTRINGtoSTRING(wcMaps->currentText()),0).c_str()));
		WRefresh();
		Bro->postChatEventMIS("Pull");
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

	wtTabelle->clear();

	LottoWeek *PullWeek = Bro->getPullWeek();
	
	if (PullWeek->iWeek == 0)return;

	wtPullWeek->setText("Pull Week" + std::to_string(PullWeek->iWeek));

	wcMaps->setCurrentIndex(0);
	for (unsigned int i = 0; i < Con->vMaps.size(); i++)if (atoi(entry(Con->vMaps[i], 0).c_str()) == PullWeek->iMapPull) wcMaps->setCurrentIndex(i);
	
		

	wtTabelle->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Card " + std::to_string(PullWeek->vCardsPulled.size()) +  "</h3>"))));
	wtTabelle->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3>Remove</h3>"))));

	for each(std::string sCard in PullWeek->vCardsPulled)
	{
		iRow++;

		wtTabelle->elementAt(iRow, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4>" + sCard + "</h4>"))));
		wtTabelle->elementAt(iRow, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WPushButton("Remove"))));
		dynamic_cast<Wt::WPushButton *>(wtTabelle->elementAt(iRow, 1)->widget(0))->clicked().connect(std::bind([=]() {
			PullWeek->RemovePull(sCard);
			WRefresh();
			Bro->postChatEventMIS("Pull");
		}));
	}
	MISE;
}

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
