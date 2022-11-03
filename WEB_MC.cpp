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
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	
	wfuDropZone = new WFileUpload();
	wtStatus	= new WText();
	wtMap       = new WText();
	wtTime      = new WText();
	Head		= new WText();
	wtTabelle   = new WTable();
	
	Head->setText("<h1><b>BOT 3 Replay Checker</b></h1>");
	wtStatus->setText("<h4>Select PMV (or drag and drop on the button)</h4>");
		
	MISD("#1");	

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
		wtMap->setText(" ");
		wtTime->setText(" ");

		R = new Replay();
		
		if (R->LoadPMV(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			wtStatus->setText("<h4>Calculationg results...</h4>");
			//wtStatus->setText("<h3> The restult is: " + to_string(R->CountActions()) + "</h3>");			
			
			wtMap->setText("Map: " + R->MapName);
			wtTime->setText("Time: " + R->sTime(R->Playtime));
			
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
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Head)), 0, 0);
	//TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(toolBar)), 1, 0);	
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 3, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 4, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 5, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cResult)), 6, 0);	
	cResult->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)));
	
	MISE;
}




string WEB_MC::showResults()
{
	MISS;

	unsigned short iRow = 0;
	unsigned short iCol = 0;

	wtTabelle->clear();	
	MISD("#0");
	/*
	if (FillWebDeck() == false)
	{
		MISEA("X1");
		return "<h4>Something is wrong in your deck</h4>";
	}
	*/
	MISD("#3");

	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Tier Check</h3>"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 1"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 2"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 3"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 4"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))));

	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Type Check</h3>"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Unit"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Building"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Spell"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))));

	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Color Check</h3>"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Fire"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Nature"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Frost"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Shadow"))));

	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Twilight"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Stonekin"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Lost Souls"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Bandits"))));

	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Others"))));
	wtTabelle->elementAt(iRow++,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))));
	iRow--;
	/*
	for (int i = 0; i < iRow; i++)
	{
		wtTabelle->elementAt(i, iCol)->setHeight(IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->addWidget(std::unique_ptr<WWidget>(std::move(new WImage(""))));
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setHeight(IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setWidth(IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->resize(IMG_SIZE, IMG_SIZE);
		wtTabelle->elementAt(i, iCol + 1)->widget(0)->setMaximumSize(IMG_SIZE, IMG_SIZE);
	}
	
	iCol++;
	iCol++;
	MISD("#4");

	for (unsigned int i = 0; i < WebDeck.size() ; i++)
	{
		wtTabelle->elementAt(WebDeck[i]->iFire + WebDeck[i]->iNature + WebDeck[i]->iFrost + WebDeck[i]->iShadow + WebDeck[i]->iNeutral,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[0])));

		
		if (WebDeck[i]->bUnit)wtTabelle->elementAt(7,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[1])));
		if (WebDeck[i]->bBuilding)wtTabelle->elementAt(8,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[1])));
		if (WebDeck[i]->bSpell)wtTabelle->elementAt(9,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[1])));
		
		if(WebDeck[i]->iFire != 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(12,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(13,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(14,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(15,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));

		else if (WebDeck[i]->iFire != 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(16,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature != 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow == 0)wtTabelle->elementAt(17,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire == 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost != 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(18,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else if (WebDeck[i]->iFire != 0 && WebDeck[i]->iNature == 0 && WebDeck[i]->iFrost == 0 && WebDeck[i]->iShadow != 0)wtTabelle->elementAt(19,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));
		else wtTabelle->elementAt(20,iCol)->addWidget(std::unique_ptr<WWidget>(std::move(WebDeck[i]->IMG[2])));	
	}

	iCol--;
	MISD("#Z1");
	//Tier check
	for (int i = 1; i < 5; i++)
	{
		//static_cast
		if (wtTabelle->elementAt(i, iCol + 1)->count() == 4)dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	//Type check
	for (int i = 7; i < 10; i++)
	{
		//static_cast
		if (wtTabelle->elementAt(i, iCol + 1)->count() <= 6 && wtTabelle->elementAt(i, iCol + 1)->count() >= 5)dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	//Color check1
	if (wtTabelle->elementAt(12, iCol + 1)->count() +
		wtTabelle->elementAt(13, iCol + 1)->count() +
		wtTabelle->elementAt(14, iCol + 1)->count() +
		wtTabelle->elementAt(15, iCol + 1)->count() == 16)
	{
		for (int i = 12; i < 16; i++)
		{
			if (wtTabelle->elementAt(i, iCol + 1)->count() == 4)dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
			else dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
		}
		for (int i = 16; i < 20; i++)
		{
			if (wtTabelle->elementAt(i, iCol + 1)->count() == 0)dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
			else dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
		}
	}
	else for (int i = 12; i < 20; i++)
	{
		if (wtTabelle->elementAt(i, iCol + 1)->count() == 2)dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/1.png");
		else dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->setImageLink("./resources/0.png");
	}

	if (wtTabelle->elementAt(20, iCol + 1)->count() == 0)dynamic_cast<WImage *>(wtTabelle->elementAt(20, iCol)->widget(0))->setImageLink("./resources/1.png");
	else dynamic_cast<WImage *>(wtTabelle->elementAt(20, iCol)->widget(0))->setImageLink("./resources/0.png");

	//wtTabelle->elementAt(i, iCol + 1)->widget(0)->setHeight(IMG_SIZE);

	MISD("##5");
	for (int i = 0; i < iRow; i++)
	{
		//MISD(to_string(i));
		if (dynamic_cast<WImage *>(wtTabelle->elementAt(i, iCol)->widget(0))->imageLink() == WLink("./resources/0.png"))
		{
			MISEA("X1");
			return "<h4>Something is wrong in your deck</h4>";
		}
	}
	*/
	MISE;
	return "<h4>All looks good :-)</h4>";
}

