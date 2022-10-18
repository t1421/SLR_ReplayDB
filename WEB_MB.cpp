#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MB.h"
#include "Load.h" 

broker *(WEB_MB::Bro) = NULL;

WEB_MB::WEB_MB()
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
	toolBar     = new WToolBar();
	
	Head->setText("<h1><b>BOT 2 Replay Checker</b></h1>");
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
			MISERROR(to_string(iAktiveToolbar) + "#" + WSTRINGtoSTRING(wtStatus->text()));
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

	MISD("#7");

	ToolBarButton(0, "Cards Played");
	ToolBarButton(1, "Cards in Deck");	
	iAktiveToolbar = 0;
	updateToolbar();

	MISD("#10");
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Head)), 0, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(toolBar)), 1, 0);	
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)), 2, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 3, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtMap)), 4, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtTime)), 5, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cResult)), 6, 0);	
	cResult->addWidget(std::unique_ptr<WWidget>(std::move(wtTabelle)));
	
	MISE;
}




string WEB_MB::showResults()
{
	MISS;

	unsigned short iRow = 0;
	unsigned short iCol = 0;

	WebDeck.clear();
	wtTabelle->clear();	
	MISD("#0");

	if (FillWebDeck() == false)
	{
		MISEA("X1");
		return "<h4>Something is wrong in your deck</h4>";
	}

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
	
	MISE;
	return "<h4>All looks good :-)</h4>";
}

bool WEB_MB::FillWebDeck()
{
		if(iAktiveToolbar==0)return FillWebDeckAction();	
		else return FillWebDeckDeck();
}

bool WEB_MB::FillWebDeckAction()
{
	MISS;

	for (unsigned int i = 0; i < R->ActionMatrix.size(); i++)
	{
		switch (R->ActionMatrix[i]->Type)
		{
		case 4009: //summon unit
			addCard(R->ActionMatrix[i]->Card, true, false, false);
			break;
		case 4010: //cast spell
		case 4011: //cast line spell
			addCard(R->ActionMatrix[i]->Card, false, true, false);
			break;
		case 4012: //cast building
			addCard(R->ActionMatrix[i]->Card, false, false, true);
			break;
		}
	}

	addColors();

	MISE;
	return true;
}

bool WEB_MB::FillWebDeckDeck()
{
	MISS;

	for (unsigned int i = 0; i < R->PlayerMatrix.size(); i++)
	{
		//MISD("i:" + to_string(i))
		if (R->PlayerMatrix[i]->Deck.size() == 0) continue;
		for (unsigned int j = 0; j < R->PlayerMatrix[i]->Deck.size(); j++)
		{
			if (R->PlayerMatrix[i]->Deck[j]->CardID == 0)continue;
			//MISD("j:" + to_string(j))
			addCard(R->PlayerMatrix[i]->Deck[j]->CardID, 
				getFromCSVUnit(R->PlayerMatrix[i]->Deck[j]->CardID),
				getFromCSVSpell(R->PlayerMatrix[i]->Deck[j]->CardID),
				getFromCSVBuilding(R->PlayerMatrix[i]->Deck[j]->CardID));
		}

		if (WebDeck.size() != 0)break;
	}
	
	if (WebDeck.size() == 0)
	{
		MISEA("No Deck?");
		return false;
	}

	addColors();

	MISE;
	return true;
}

void WEB_MB::addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building)
{
	MISS;
	unsigned int uiFound = -1;

	for (unsigned int i = 0; i < WebDeck.size(); i++)if (uiCardID == WebDeck[i]->CardID)uiFound = i;
	
	if (uiFound != -1)WebDeck[uiFound]->playCount++;
	else
	{
		MISD(to_string(uiCardID));
		WebCard *Card_TEMP = new WebCard;
		Card_TEMP->CardID = uiCardID;
		Card_TEMP->bUnit = Unit;
		Card_TEMP->bSpell = Spell;
		Card_TEMP->bBuilding = Building;

		for (int i = 0; i < 3; i++)
		{
			Card_TEMP->IMG[i] = new WImage("./resources/Cards/" + to_string(uiCardID) + ".png");
			Card_TEMP->IMG[i]->setHeight(IMG_SIZE);
			Card_TEMP->IMG[i]->setWidth(IMG_SIZE);
			Card_TEMP->IMG[i]->resize(IMG_SIZE, IMG_SIZE);
			Card_TEMP->IMG[i]->setMaximumSize(IMG_SIZE, IMG_SIZE);
		}

		

		WebDeck.push_back(Card_TEMP);
	}
	MISE;
}

void WEB_MB::addColors()
{
	MISS;
	for (unsigned int i = 0; i < WebDeck.size(); i++)
	{
		//MISD(to_string(WebDeck[i]->CardID));
		for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		{
			if (Bro->L->CsvAllCards[j]->CardID == WebDeck[i]->CardID)
			{
				WebDeck[i]->iFire = Bro->L->CsvAllCards[j]->iFire;
				WebDeck[i]->iFrost = Bro->L->CsvAllCards[j]->iFrost;
				WebDeck[i]->iShadow = Bro->L->CsvAllCards[j]->iShadow;
				WebDeck[i]->iNature = Bro->L->CsvAllCards[j]->iNature;
				WebDeck[i]->iNeutral = Bro->L->CsvAllCards[j]->iNeutral;				
				break;
			}
		}
		
	}
	MISE;
}

void WEB_MB::ToolBarButton(int Index, string Name)
{
	MISS;
	button[Index] = new Wt::WPushButton();
	button[Index]->setText(Name);
	toolBar->addButton(std::unique_ptr<Wt::WPushButton>(button[Index]));
	button[Index]->clicked().connect(std::bind([=]() {		
		iAktiveToolbar = Index;
		updateToolbar();
		if (R != NULL)if (R->OK)
		{
			wtStatus->setText(showResults());
			MISERROR(to_string(iAktiveToolbar) + "#" + WSTRINGtoSTRING(wtStatus->text()));
		}
	}));
	MISE;
}

void WEB_MB::updateToolbar()
{
	MISS;

	string sCSS;
	for (int i = 0; i < MaxRegister; i++)
	{
		MISD(to_string(i));
		sCSS = WSTRINGtoSTRING(button[i]->styleClass());

		if (sCSS.find("button1") != sCSS.npos)sCSS.erase(sCSS.find("button1"), 7);
		if (sCSS.find("button0") != sCSS.npos)sCSS.erase(sCSS.find("button0"), 7);

		if (i == iAktiveToolbar)sCSS = "button1 " + sCSS;
		else sCSS = "button0" + sCSS;

		button[i]->setStyleClass(sCSS);
	}


	MISE;
}

bool WEB_MB::getFromCSVBuilding(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bBuilding;

	return false;
}

bool WEB_MB::getFromCSVSpell(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bSpell;

	return false;
}

bool WEB_MB::getFromCSVUnit(unsigned short uiCardID)
{
	for (unsigned int j = 0; j < Bro->L->CsvAllCards.size(); j++)
		if (Bro->L->CsvAllCards[j]->CardID == uiCardID)return Bro->L->CsvAllCards[j]->bUnit;

	return false;
}