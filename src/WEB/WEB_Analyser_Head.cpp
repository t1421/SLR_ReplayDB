#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\Replay.h"
#include "..\..\incl\WEB\WEB_Analyser_Head.h"
#include "..\..\incl\Replay.h" 
#include "..\..\incl\Utility.h" 

#include <Wt/WContainerWidget.h>
#include <Wt/WGridLayout.h>
#include <Wt/WText.h>

broker *(WEB_Analyser_Head::Bro) = NULL;

WEB_Analyser_Head::WEB_Analyser_Head(WEB_Analyser *WA_): WA(WA_), newData(false)
{
	MISS;

	cMain = new Wt::WContainerWidget();		
				
	MISD("#1");	
	Playtime = new Wt::WText(" ");
	FileVersion = new Wt::WText(" ");
	GameVersion = new Wt::WText(" ");
	MapName = new Wt::WText(" ");
	Seed = new Wt::WText(" ");
	MapID = new Wt::WText(" ");
	DifficultyID = new Wt::WText(" ");
	PlayModeID = new Wt::WText(" ");
	ActionBlock = new Wt::WText(" ");
	PMVPlayerID = new Wt::WText(" ");
	GroupCount = new Wt::WText(" ");
	WinningTeam = new Wt::WText(" ");
	//FileName = new Wt::WText(" ");
	Unknow3 = new Wt::WText(" ");
	Unknow4 = new Wt::WText(" ");

	MatrixCount = new Wt::WText(" ");
	TeamCount = new Wt::WText(" ");
	DifficultyID2 = new Wt::WText(" ");
	Playtime2 = new Wt::WText(" ");
	PlayModeID2 = new Wt::WText(" ");
	PMVPlayerID2 = new Wt::WText(" ");
		


	MISD("#2");
	Wt::WGridLayout *CLGrid = new Wt::WGridLayout();
	Wt::WContainerWidget *CWGrid = new Wt::WContainerWidget();	
	CWGrid->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(CLGrid)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(CWGrid)));
	
	
	int x = 0;
	int y = 0;
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Playtime: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Playtime)), x++, y--);
	
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("MapName: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(MapName)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Seed: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Seed)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("DifficultyID: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DifficultyID)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayModeID: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(PlayModeID)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PMVPlayerID: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(PMVPlayerID)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("WinningTeam: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WinningTeam)), x++, y--);



	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("MapID: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(MapID)), x++, y--);

	//CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("FileVersion: "))), x, y++);
	//CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(FileName)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("GameVersion: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(GameVersion)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("GroupCount: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(GroupCount)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("DifficultyID2: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(DifficultyID2)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Playtime2: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Playtime2)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PlayModeID2: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(PlayModeID2)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("PMVPlayerID2: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(PMVPlayerID2)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("ActionBlock: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(ActionBlock)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Unknow3: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Unknow3)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Unknow4: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(Unknow4)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("MatrixCount: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(MatrixCount)), x++, y--);

	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("TeamCount: "))), x, y++);
	CLGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(TeamCount)), x++, y--);

	CLGrid->setColumnStretch(0, 5);
	CLGrid->setColumnStretch(1, 95);
	
	MISE;
}

void WEB_Analyser_Head::WRefresh()
{
	MISS;
	if (WA->isOK() != true)
	{
		MISEA("no Replay");
		return;
	}

	if (!newData)
	{
		MISEA("not New");
		return;
	}
	
	Playtime->setText(sTime(WA->R->Playtime));
	
	MapName->setText(WA->R->MapName);
	Seed->setText(std::to_string(WA->R->Seed));
	switch (WA->R->DifficultyID)
	{
	case 1:
		DifficultyID->setText("Std");
		break;
	case 2:
		DifficultyID->setText("Adv");
		break;
	case 3:
		DifficultyID->setText("Exp");
		break;
	}
	switch (WA->R->PlayModeID)
	{
	case 1:
		PlayModeID->setText("PvE");
		break;
	case 2:
		PlayModeID->setText("PvP");
		break;
	}
	
	for (int i = 0; i < WA->R->PlayerMatrix.size();i++)
		if(WA->R->PlayerMatrix[i]->PlayerID== WA->R->PMVPlayerID)PMVPlayerID->setText(WA->R->PlayerMatrix[i]->Name);


	
	WinningTeam->setText(WA->R->WinningTeam);
	//FileName->setText(WA->R->FileName);

	FileVersion->setText(std::to_string(WA->R->FileVersion));
	GameVersion->setText(std::to_string(WA->R->GameVersion));
	GroupCount->setText(std::to_string(WA->R->GroupCount));
	MatrixCount->setText(std::to_string(WA->R->MatrixCount));
	TeamCount->setText(std::to_string(WA->R->TeamCount));


	DifficultyID2->setText(std::to_string(WA->R->DifficultyID));
	Playtime2->setText(std::to_string(WA->R->Playtime));
	PlayModeID2->setText(std::to_string(WA->R->PlayModeID));
	PMVPlayerID2->setText(std::to_string(WA->R->PMVPlayerID));
	ActionBlock->setText(std::to_string(WA->R->ActionBlock));
	Unknow3->setText(std::to_string(WA->R->Unknow3));
	Unknow4->setText(std::to_string(WA->R->Unknow4));
	MapID->setText(std::to_string(WA->R->MapID));
	
	newData = !newData;
	MISE;
}

