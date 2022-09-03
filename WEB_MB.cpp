#define DF_Debug

#include "prototypes.h"
#include "Replay.h" 
#include "WEB_Main.h"
#include "WEB_MB.h"
#include "CardBase.h" 

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
	Head		= new WText();
	

	Head->setText("<h1><b>Check PMV for Event</b></h1>");
	wtStatus->setText("Select PMV (or drag and drop on the button)");
	
	
	MISD("#1");

	Bro->C->LoadCardsFromSQL();

	MISD("#3");
	wfuDropZone->setFilters(".pmv");
	MISD("#4");

	wfuDropZone->changed().connect([=] {
		wfuDropZone->upload();
		wtStatus->setText("New File");
	});
	
	MISD("#5");
	
	wfuDropZone->uploaded().connect([=] {
		wtStatus->setText("Upload done");

		R = new Replay();
		
		if (R->LoadPMV(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			wtStatus->setText("Calculationg results...");
			//wtStatus->setText("<h3> The restult is: " + to_string(R->CountActions()) + "</h3>");
			showResults();
			wtStatus->setText(" ");
			//MISERROR(to_string(R->CountActions()));
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4>" );

	});

	MISD("#6");

	wfuDropZone->fileTooLarge().connect([=] {
		wtStatus->setText("File is too large.");
	});


	MISD("#10");
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Head)), 0, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wfuDropZone)), 1, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wtStatus)), 2, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cResult)), 3, 0, 0, 1);
	
	MISE;
}




bool WEB_MB::showResults()
{
	MISS;

	if (FillWebDeck() == false)
	{
		MISEA("X1");
		return false;
	}

	cResult->clear();

	WContainerWidget *cResultX = new WContainerWidget();
	cResult->addWidget(std::unique_ptr<WWidget>(std::move(cResultX)));
	WGridLayout *TempGrid;
	
	TempGrid = new WGridLayout();
	cResultX->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));

	WImage	*Deck;

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Tier Check</h3>"))), 0, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 1"))), 1, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 2"))), 2, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 3"))), 3, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Tier 4"))), 4, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))), 5, 0, 0, 2);


	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Type Check</h3>"))), 6, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Unit"))), 7, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Building"))), 8, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Spell"))), 9, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))), 10, 0, 0, 2);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("<h3>Color Check</h3>"))), 11, 0, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Fire"))), 12, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Nature"))), 13, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Frost"))), 14, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Shadow"))), 15, 0, 0, 1);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Twilight"))), 16, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Stonekin"))), 17, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Lost Souls"))), 18, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Bandits"))), 19, 0, 0, 1);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText("Others"))), 20, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(new WText(" "))), 21, 0, 0, 2);
	
	
	//Deck = new WImage("./resources/Cards/1448.png");

	//TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(Deck)), 0, 0);
	

	MISE;
	return true;
}


bool WEB_MB::FillWebDeck()
{
	MISS;

	WebCard *Card_TEMP;

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

void WEB_MB::addCard(unsigned short uiCardID, bool Unit, bool Spell, bool Building)
{
	MISS;
	unsigned int uiFound = 0;
	for (unsigned int i = 0; i < WebDeck.size(); i++)
	{
		if (uiCardID == WebDeck[i]->CardID)uiFound = i;
	}

	if (uiFound != 0)WebDeck[uiFound]->playCount++;
	else
	{
		WebCard *Card_TEMP = new WebCard;
		Card_TEMP->CardID = uiCardID;
		Card_TEMP->bUnit = Unit;
		Card_TEMP->bSpell = Spell;
		Card_TEMP->bBuilding = Building;

		WebDeck.push_back(Card_TEMP);
	}
	MISE;
}

void WEB_MB::addColors()
{
	MISS;
	for (unsigned int i = 0; i < WebDeck.size(); i++)
	{
		MISD(to_string(WebDeck[i]->CardID));
		for (unsigned int j = 0; j < Bro->C->SQLCardMatrix.size(); j++)
		{
			if (Bro->C->SQLCardMatrix[j]->cardId == WebDeck[i]->CardID)
			{
				WebDeck[i]->bFire = Bro->C->SQLCardMatrix[j]->fireOrbs != 0;
				WebDeck[i]->bFrost = Bro->C->SQLCardMatrix[j]->frostOrbs != 0;
				WebDeck[i]->bShadow = Bro->C->SQLCardMatrix[j]->shadowOrbs != 0;
				WebDeck[i]->bNature = Bro->C->SQLCardMatrix[j]->natureOrbs != 0;
				break;
			}
		}
		
	}
	MISE;
}