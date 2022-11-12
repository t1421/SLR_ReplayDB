#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MCA.h"
#include "Load.h" 

broker *(WEB_MCA::Bro) = NULL;

WEB_MCA::WEB_MCA(WEB_Replay *WR_) : WR(WR_)
{
	MISS;

	cMain = new WContainerWidget();	
	cReplay = new WContainerWidget();
	cReplayResult = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();	
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	MISD("#0");

	wtStatus	= new WText(" ");
	wtMap       = new WText(" ");
	wtDif       = new WText(" ");
	wtTime      = new WText(" ");
	wtTabelle   = new WTable();
	
	MISD("#1");

	cMap = new WContainerWidget();
	wiMap = new WImage("./resources/TheTreasureFleet.webp");
	cMap->setStyleClass("crop");
	
	MISD("#2");
	
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 1, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 2, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtDif)), 3, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 4, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cMap)), 5, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cReplayResult)), 5, 1);
	
	TempGrid->setColumnStretch(0, 5);
	TempGrid->setColumnStretch(1, 95);

	cReplayResult->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)));
	cReplayResult->setContentAlignment(AlignmentFlag::Left);
	
	cMap->addWidget(std::unique_ptr<WWidget>(std::move(wiMap)));
	cMap->setMaximumSize(400, 400);
	
	MISE;
}












void WEB_MCA::WRefresh()
{
	MISS;






	wtStatus->setText(" ");
	wtMap->setText("Map: ");
	wtTime->setText("Playtime; ");
	wtDif->setText("Difficulty: ");


	if (WR->BOT3())
	{
		wtMap->setText("Map: " + WR->MapName());
		wtTime->setText("Time: " + WR->Time());
		wtDif->setText("Difficulty: " + to_string(WR->Difficulty()));

		wtTabelle->clear();
		for (unsigned int i = 0; i < WR->vMarker.size(); i++)
			cMap->addWidget(std::unique_ptr<WWidget>(std::move(WR->vMarker[i]->IMG)));

		//MAP Check
		if (WR->MapName() != "11101_PvE_01p_TugOfWar.map")
		{
			wtStatus->setText("<h4 style='color:Tomato;'>  Wrong Map </h4>");
			MISEA("Wrong Map");
			return;
		}

		WR->BOT3WellsAndOrbUnit();
		WR->FillTableBOT3(wtTabelle);
		

		// ERROR Checks
		if (WR->Difficulty() != 1)
		{
			wtStatus->setText("<h4 style='color:Tomato;'>  Wrong Difficulty </h4>");
			MISEA("Wrong Difficulty");
			return;
		}

		if (WR->CountActions("4007") != 2)
		{
			wtStatus->setText("<h4 style='color:Tomato;'>  You have to save the first 2 Wagons </h4>");
			MISEA("2 Wagons Count");
			return;
		}

		if (WR->Playtime() > 10000)
		{
			wtStatus->setText("<h4 style='color:Tomato;'>  You have to save the first 2 Wagons </h4>");
			MISEA("First 2 Wagons");
			return;
		}

		for (unsigned j = 0; j < WR->vMarker.size(); j++) if (WSTRINGtoSTRING(WR->vMarker[j]->Time->text()) == "XX:XX")
		{
			wtStatus->setText("<h4 style='color:Tomato;'> You did not build all Orbs and/or Wells </h4>");
			MISEA("Not build all");
			return;
		}

		wtStatus->setText("<h4>All looks good :-)</h4> ");
	}
	else wtStatus->setText("<h3> somthing went wrong </h3>");

	MISE;
}
