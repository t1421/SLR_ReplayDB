#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\Replay.h" 

#include "..\..\incl\WEB_Lotto\WEB_Lotto_Week.h"
#include "..\..\incl\WEB_Lotto\WEB_Container_Lotto.h"

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WGridLayout.h>
#include <Wt/WCheckBox.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WBreak.h>
#include <Wt/WLength.h>
#include <Wt/WLink.h>
#include <Wt/WAnchor.h>


broker *(WEB_Lotto_Week::Bro) = NULL;


WEB_Lotto_Week::WEB_Lotto_Week(WEB_Container_Lotto *Con_, LottoWeek *BroWeek_) 
	: Con(Con_), BroWeek(BroWeek_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	
	MISD("#0");

	cMain = new Wt::WContainerWidget();
	cMain->setMaximumSize(900, Wt::WLength::Auto);
		
	MISD("#1");

	wtTabelle = new Wt::WTable();
	
	MISD("#11");
	wfuDropZone = new Wt::WFileUpload();
	wtReplayResultCard = new Wt::WTable();
	wtStatus = new Wt::WText("Waiting for Replay");
	WA = new WEB_Analyser();

	unsigned int iCol = 0;
	std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");

	MISD("#2");

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtReplayResultCard)));
	

	MISD("#3");
	

	MISD("#4");


	wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayerID"))));	

	wtTabelle->elementAt(0, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Player Name"))));
	wtTabelle->elementAt(1, iCol)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Add"))));
	wtTabelle->elementAt(2, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Multi Rem"))));

	MISD("#4");

	wtTabelle->columnAt(1)->setWidth(160);

	MISD("#5");
	
	wfuDropZone->setFilters(".pmv");

	wfuDropZone->changed().connect([=]
	{
		MISD("#changed");
		wfuDropZone->upload();
		wtStatus->setText("New File \n");
	});
	wfuDropZone->fileTooLarge().connect([=]
	{
		MISD("#fileTooLarge");
		wtStatus->setText("File is too large. \n");
	});

	wfuDropZone->uploaded().connect([=]
	{
		
		
		MISD("#uploaded");
		wtStatus->setText("Upload done \n");
		wtReplayResultCard->clear();

		if (WA->NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			//switch (WA->TomeAnalyser(wtReplayResultCard, Con->BroGameID))
			switch(1)
			{
			case 0: wtStatus->setText("<h3 style='color:Green;'>All OK</h3>");	
				break;
			case 1: wtStatus->setText("<h3 style='color:Tomato;'>Error: Could not match Players</h3>");
				break;
			case 2: wtStatus->setText("<h3 style='color:Tomato;'>Error: A not allowed Card was player</h3>");
				break;
			}	
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");	
	});
	

	MISE;
}

void WEB_Lotto_Week::WRefresh()
{
	MISS;

	//if (Con->BroGameID == -1)
	//{
		//MISEA("WTF !!!");
		//return;
	//}

	//unsigned int iCol = 0;
	//std::vector<std::pair<std::string, std::string>> EnumBoosters = Bro->J_GetEnum("EnumBoosters");
	//std::vector<WEB_Tome_Player *> Tabel_Player;

	MISE;
}

