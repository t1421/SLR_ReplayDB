//#define DF_Debug

#include "..\..\incl\Broker.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Admin_Main.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WGridLayout.h>
#include <Wt/WCheckBox.h>
#include <Wt/WComboBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WLength.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>


broker *(WEB_Lotto_Admin_Main::Bro) = NULL;


WEB_Lotto_Admin_Main::WEB_Lotto_Admin_Main(WEB_Container_Lotto *Con_) : Con(Con_)
{
	MISS;


	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();
	wbAddWeek = new Wt::WPushButton("Add Week");

	MISD("#2");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wbAddWeek)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISD("#3");
	
	wbAddWeek->clicked().connect(std::bind([=]() {
		Bro->vWeek.push_back(new LottoWeek(Bro->vWeek.size()));
		WRefresh();
		//Bro->postChatEventMIS("AddDellWeek");
	}));



	MISD("#4");

	wtTabelle->columnAt(1)->setWidth(160);

	MISD("#5");

	WRefresh();
	MISD("#6");
	
	
	MISE;
}

void WEB_Lotto_Admin_Main::WRefresh()
{
	MISS;

	wtTabelle->clear();

	int iCol = 0;
	int iRow = 0;
	Wt::WComboBox* wtCB;
	Wt::WPushButton* wtPB;
	Wt::WLineEdit* wtLE;

	wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Week"))));
	wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("BFP"))));
	wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Status"))));
	wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Save"))));
	

	for each (LottoWeek* L in Bro->vWeek)
	{
		iRow++;
		iCol = 0;	
		wtCB = new Wt::WComboBox();
		wtPB = new Wt::WPushButton("Save");
		wtLE = new Wt::WLineEdit(std::to_string(L->iBFP));

		wtCB->addItem("0;Hidden");
		wtCB->addItem("1;Activ");
		wtCB->addItem("2;Inactiv");
		wtCB->addItem("3;PullMode");
		wtCB->setCurrentIndex(L->iStatus);

		wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(L->iWeek)))));
		wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtLE)));
		wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtCB)));
		wtTabelle->elementAt(iRow, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtPB)));

		wtPB->clicked().connect(std::bind([=]() {
			L->setBFP(std::atoi(WSTRINGtoSTRING(wtLE->text()).c_str()));
			//L->iStatus = wtCB->currentIndex();
			L->setStatus(wtCB->currentIndex());
			//L->bSaveGame();
			WRefresh();
			Bro->postChatEventMIS("UpdateWeek",std::to_string(L->iWeek));
			//if(wtCB->currentIndex()==0)Bro->postChatEventMIS("AddDellWeek");
				
		}));


	}

	

	MISE;
}

