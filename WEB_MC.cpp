#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MC.h"
#include "Load.h" 

broker *(WEB_MC::Bro) = NULL;

WEB_MC::WEB_MC()
{
	MISS;

	WColor wTemp;

	cMain = new WContainerWidget();
	
	cResult = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();
	WGridLayout *TempGrid2 = new WGridLayout();
	
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	wfuDropZone = new WFileUpload();
	wtStatus	= new WText();
	wtMap       = new WText();
	wtDif       = new WText();
	wtTime      = new WText();
	Head		= new WText();
	wtTabelle   = new WTable();

	cMap = new WContainerWidget();
	wiMap = new WImage("./resources/TheTreasureFleet.webp");
	cMap->setStyleClass("crop");
	
	MISD("#1");

	Head->setText("<h1><b>BOT 3 Replay Checker</b></h1>");
	wtStatus->setText("<h4>Select PMV (or drag and drop on the button)</h4>");
	wtMap->setText("Map: ");
	wtTime->setText("Time; ");
	wtDif->setText("Difficulty: ");
		
	

	MISD("#3");
	wfuDropZone->setFilters(".pmv");
	MISD("#4");

	wfuDropZone->changed().connect([=] {
		wfuDropZone->upload();
		wtStatus->setText("<h4>New File</h4>");
	});
	
	MISD("#5");
	
	wfuDropZone->uploaded().connect([=] {
		//wfuDropZone->hide();
		wtStatus->setText("<h4>Upload done</h4>");
		wtMap->setText("Map: ");
		wtTime->setText("Time; ");
		wtDif->setText("Difficulty: ");
		
		


		R = new Replay();
		
		if (R->LoadPMV(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			wtStatus->setText("<h4>Calculationg results...</h4>");
			//wtStatus->setText("<h3> The restult is: " + to_string(R->CountActions()) + "</h3>");			
			
			if (R->MapName != "11101_PvE_01p_TugOfWar.map")
			{
				wtStatus->setText("<h4> Wrong Map </h4>");
				MISEA("Wrong Map");
				return;
			}

			if (R->DifficultyID != 1)
			{
				wtStatus->setText("<h4> Wrong Difficulty </h4>");
				MISEA("Wrong Difficulty");
				return;
			}

			if (R->CountActions("4007") != 2)
			{
				wtStatus->setText("<h4> You have to save 2 Wagons </h4>");
				MISEA("2 Wagons");
				return;
			}

			if (R->Playtime > 10000)
			{
				wtStatus->setText("<h4> You have to Save the first 2 Wagons </h4>");
				MISEA("First 2 Wagons");
				return;
			}

			wtMap->setText("Map: " + R->MapName);
			wtDif->setText("Difficulty: " + to_string(R->DifficultyID));
			wtTime->setText("Time: " + R->sTime(R->Playtime));

			addStartingWells();
			addUnitToFirstOrb();

			R->EchoAction("4029"); 
			R->EchoAction("4030");
			R->EchoAction("4031");

			
			wtStatus->setText(showResults());
			//MISERROR(to_string(iAktiveToolbar) + "#" + WSTRINGtoSTRING(wtStatus->text()));
			//if()wtStatus->setText("<h4>All looks good :-)</h4>");
			//else wtStatus->setText("<h4>Something is wrong in your deck</h4>");
			
			//MISERROR(to_string(R->CountActions()));
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4>" );

	});

	MISD("#6");

	wfuDropZone->fileTooLarge().connect([=] {
		wtStatus->setText("<h4>File is too large.</h4>");
	});
	

	MISD("#10");
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Head)), 0, 0,0,2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)), 1, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 2, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 3, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtDif)), 4, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 5, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cMap)), 6, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cResult)), 6, 1);
	
	TempGrid->setColumnStretch(0, 5);
	TempGrid->setColumnStretch(1, 95);

	cResult->setContentAlignment(AlignmentFlag::Left);		
	cMap->setMaximumSize(400, 400);
	cResult->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)));

	
	cMap->addWidget(std::unique_ptr<WWidget>(std::move(wiMap)));
	InitVector();

	MISE;
}




string WEB_MC::showResults()
{
	MISS;

	unsigned int iRow;
	unsigned int iMaxAction = 0;	
	unsigned long iUnit;

	wtTabelle->clear();	
	MISD("#0");

	

	MISD("#3");

	wtTabelle->elementAt(0,0)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3> Wells </h3>"))));
	wtTabelle->elementAt(0,1)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3> Orbs </h3>"))));
	wtTabelle->elementAt(0,2)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3> Walls </h3>"))));
	wtTabelle->columnAt(0)->setWidth(100);
	wtTabelle->columnAt(1)->setWidth(100);
	wtTabelle->columnAt(2)->setWidth(100);
	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type != 4029
			&& R->ActionMatrix[i]->Type != 4030
			&& R->ActionMatrix[i]->Type != 4031)continue;

		iUnit = atoi(R->ActionMatrix[i]->AdditionalInfo.erase(0, R->ActionMatrix[i]->AdditionalInfo.find(";") + 1).c_str());

		for (unsigned int j = 0; j < vMarker.size(); j++)
		{
			if (vMarker[j]->Unit == iUnit && WSTRINGtoSTRING(vMarker[j]->Time->text()) == "XX:XX")
			{
				vMarker[j]->Time->setText(R->sTime(R->ActionMatrix[i]->Time));
				iMaxAction = i;
			}
		}
	}


	iUnit = atoi(R->ActionMatrix[iMaxAction]->AdditionalInfo.erase(0, R->ActionMatrix[iMaxAction]->AdditionalInfo.find(";") + 1).c_str());
	
	for (unsigned int i = 0; i < 3; i++)
	{
		
		for (unsigned int j = 0, iRow = 1; j < vMarker.size(); j++)
		{
			if (vMarker[j]->Type != i) continue;
			
			wtTabelle->elementAt(++iRow, vMarker[j]->Type)->addWidget(std::unique_ptr<WWidget>(std::move(vMarker[j]->Time)));
			if (WSTRINGtoSTRING(vMarker[j]->Time->text()) == "XX:XX")wtTabelle->elementAt(iRow, vMarker[j]->Type)->setStyleClass("red");
			if (vMarker[j]->Unit == iUnit)wtTabelle->elementAt(iRow, vMarker[j]->Type)->setStyleClass("green");

			wtTabelle->elementAt(iRow, vMarker[j]->Type)->mouseWentOver().connect([=] {
				vMarker[j]->IMG->setHidden(false);
			});

			wtTabelle->elementAt(iRow, vMarker[j]->Type)->mouseWentOut().connect([=] {
				vMarker[j]->IMG->setHidden(true);
			});
			
		}
	}

	MISE;
	return "<h4>All looks good :-)</h4>";
}



void WEB_MC::addUnitToFirstOrb()
{
	MISS;
	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		if (R->ActionMatrix[i]->Type != 4031)continue;
		R->ActionMatrix[i]->AdditionalInfo = R->ActionMatrix[i]->AdditionalInfo + ";4555";
		MISE;
		return;
	}
	MISEA("FAIL");
}

void WEB_MC::addStartingWells()
{
	MISS;
	Action * Action_TEMP;
	unsigned int Player;

	for (Player = 0; Player < R->PlayerMatrix.size(); Player++)
	{
		if (R->PlayerMatrix[Player]->Type != 1)continue;
		else break;
	}

	for (unsigned int i = 0; i < 3; i++)
	{
		Action_TEMP = new Action;
		Action_TEMP->Time = 0;
		Action_TEMP->Type = 4030;
		Action_TEMP->ActionPlayer = R->PlayerMatrix[Player]->ActionPlayer;
		Action_TEMP->AdditionalInfo = to_string(4550 + i);
		R->ActionMatrix.insert(R->ActionMatrix.begin() , Action_TEMP);
	}
	
	MISE;
}


void WEB_MC::InitVector()
{
	MISS;

	
	vMarker.clear();
	MISD(to_string(90 + Xoffset) + "#" + to_string(267 + Yoffset));
	vMarker.push_back(new Marker(1, 4555,  90 , 267 ));
	vMarker.push_back(new Marker(1, 4556, 157 , 318 ));
	vMarker.push_back(new Marker(1, 4557,  60 , 142 ));
	vMarker.push_back(new Marker(1, 4558, 332 , 103 ));

	vMarker.push_back(new Marker(0, 4535, 155, 368));
	vMarker.push_back(new Marker(0, 4536, 145, 368));
	vMarker.push_back(new Marker(0, 4537, 157, 244));
	vMarker.push_back(new Marker(0, 4538, 158, 249));
	vMarker.push_back(new Marker(0, 4539, 339, 330));
	vMarker.push_back(new Marker(0, 4540, 342, 257));
	vMarker.push_back(new Marker(0, 4541, 247, 148));
	vMarker.push_back(new Marker(0, 4542, 188,  36));
	vMarker.push_back(new Marker(0, 4543, 247, 154));
	vMarker.push_back(new Marker(0, 4544, 328, 96));
	vMarker.push_back(new Marker(0, 4545, 325, 103));
	vMarker.push_back(new Marker(0, 4546, 328, 110));
	vMarker.push_back(new Marker(0, 4547,  65, 136));
	vMarker.push_back(new Marker(0, 4548,  59, 148));
	vMarker.push_back(new Marker(0, 4549,  67, 144));
	vMarker.push_back(new Marker(0, 4550,  85, 263));
	vMarker.push_back(new Marker(0, 4551,  79, 262));
	vMarker.push_back(new Marker(0, 4552,  83, 258));
	vMarker.push_back(new Marker(0, 4553,  46, 286));
	vMarker.push_back(new Marker(0, 4554,  45, 293));

	vMarker.push_back(new Marker(2, 4452,  75, 316));
	vMarker.push_back(new Marker(2, 4453, 151, 347));
	vMarker.push_back(new Marker(2, 4455, 291, 76));
	
	for(unsigned int i = 0; i < vMarker.size();i++)
	cMap->addWidget(std::unique_ptr<WWidget>(std::move(vMarker[i]->IMG)));

	MISE;
}
