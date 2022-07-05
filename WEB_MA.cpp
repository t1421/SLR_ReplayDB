//#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_MA.h"

broker *(WEB_MA::Bro) = NULL;

WEB_MA::WEB_MA(vector<vector<pair<WWidget*, string>>> &VVPWSWid_)
	:VVPWSWid(VVPWSWid_)
{
	MISS;

	cMain = new WContainerWidget();
	WContainerWidget* TEMP = new WContainerWidget();
	WGridLayout *TempGrid = new WGridLayout();
	cMain->setLayout(std::unique_ptr<WGridLayout>(std::move(TempGrid)));
	

	wbPrev = new WPushButton("Prev");
	wbStop = new WPushButton("Stop");
	wbPlay = new WPushButton("Play");
	wbNext = new WPushButton("Next");
	wbSync = new WPushButton("Sync");
	wbKopf = new WPushButton();
	wbTitel = new WPushButton();
	wbSongNr = new WPushButton();
	wbBarcode = new WPushButton("Barcode");

	leBarcode = new WLineEdit();
	
	wsPos = new WSlider();

	cbNote = new WComboBox;
	cbCopy = new WComboBox;

	wiREP = new WImage();
	wiMAS = new WImage();

	wbColorAnz = new WPushButton("Color Anz");
	weColorAnz = new WLineEdit();
	wbColorOffset = new WPushButton("Color Offset");
	weColorOffset = new WLineEdit();


	MISD("#1");

	MISD("#2");

	for (int i = 0; i < 2; i++)
	{
		wiCover[i] = new WImage();
		wiCover[i]->setHeight(550);
		wiCover[i]->setWidth(550);
		wiCover[i]->resize(550, 550);
		wiCover[i]->setMaximumSize(550, 550);
		wiCover[i]->setPositionScheme(Wt::PositionScheme::Absolute);
	}
		
	MISD("#3");

	wsPos->setTickInterval(10);
	wsPos->setMinimum(0);
	wsPos->setMaximum(100);

	MISD("#4");

	wiMAS->resize(100, 100);
	wiREP->resize(100, 100);
	weColorAnz->resize(100, 35);
	weColorOffset->resize(100, 35);
	
	MISD("#5");

	for (int j = 1; j <= 5; j++)
	{
		wiStar[j-1] = new WImage();
		wiStar[j-1]->resize(100, 100);
		
		TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wiStar[j - 1])), 3, j - 1);

	}

	MISD("#6");


	MISD("#6");

	TEMP->setHeight(550);
	TEMP->setWidth(550);
	TEMP->resize(550, 550);
	TEMP->setMaximumSize(550, 550);

	TEMP->addWidget(std::unique_ptr<WWidget>(std::move(wiCover[0])));
	TEMP->addWidget(std::unique_ptr<WWidget>(std::move(wiCover[1])));
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(TEMP)), 0, 0, 0, 7);

	MISD("#7");

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbKopf)), 1, 0, 0, 5);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cbNote)), 1, 5, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbSongNr)), 2, 0, 0, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbTitel)), 2, 1, 0, 4);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(cbCopy)), 2, 5, 0, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wiMAS)), 3, 5);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wiREP)), 3, 6);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbPrev)), 4, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbStop)), 4, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbPlay)), 4, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbNext)), 4, 3);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbSync)), 4, 4);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbColorAnz)), 5, 0);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(weColorAnz)), 5, 1);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbColorOffset)), 5, 2);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(weColorOffset)), 5, 3);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(leBarcode)), 6, 0, 0, 5);
	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wbBarcode)), 6, 5, 0, 2);

	TempGrid->addWidget(std::unique_ptr<WWidget>(std::move(wsPos)), 7, 0, 0, 7);

	MISD("#8");


	MISE;
}



void WEB_MA::Update_Pic(string sFrom, string sTo, int Alpha)
{
	MISS;
	stringstream ssCoverLink;

	ssCoverLink.str("");
	ssCoverLink << "./resources/Cover/" << sFrom << ".jpg";
	if(wiCover[0]->imageLink() != WLink(ssCoverLink.str()))
		wiCover[0]->setImageLink(Wt::WLink(ssCoverLink.str()));
	wiCover[0]->setStyleClass("opacity" + to_string(100 - Alpha));

	ssCoverLink.str("");
	ssCoverLink << "./resources/Cover/" << sTo << ".jpg";
	if (wiCover[0]->imageLink() != WLink(ssCoverLink.str()))
		wiCover[1]->setImageLink(Wt::WLink(ssCoverLink.str()));
	wiCover[1]->setStyleClass("opacity" + to_string(Alpha));

	MISE;
}

void WEB_MA::Update_Kopf(string _Kopf)
{
	MISS;
	wbKopf->setText(_Kopf);
	MISE;
}

void WEB_MA::Update_Pos(int _Pos)
{
	MISS;
	wsPos->setValue(_Pos);
	MISE;
}

void WEB_MA::Update_DS(string sInput)
{
	MISS;
	//wbSongNr->setText(sInput.substr(0, sInput.find("|"))); 
	sInput.erase(0, sInput.find("|") + 1); // Playliste Arry Nr

	MISD("1");
	//Titel
	wbTitel->setText(sInput.substr(0, sInput.find("|")));
	sInput.erase(0, sInput.find("|") + 1);

	MISD("2");
	//KOPF ID
	//wbsKopf->setText(sInput.substr(0, sInput.find("|")));
	sInput.erase(0, sInput.find("|") + 1);

	MISD("3");
	//STARS
	
	sInput.erase(0, sInput.find("|") + 1);

	MISD("4");
	//MAS
	if (sInput.substr(0, sInput.find("|")) == "1") wiMAS->setImageLink(Wt::WLink(
		"./resources/pics/M1.bmp"));
	else wiMAS->setImageLink(Wt::WLink(
		"./resources/pics/M0.bmp"));
	sInput.erase(0, sInput.find("|") + 1);

	MISD("5");
	//REP
	if (sInput.substr(0, sInput.find("|")) == "1") wiREP->setImageLink(Wt::WLink(
		"./resources/pics/R1.bmp"));
	else wiREP->setImageLink(Wt::WLink(
		"./resources/pics/R0.bmp"));
	sInput.erase(0, sInput.find("|") + 1);

	MISD("6");
	//COPY
	

	MISD("7");
	//iStatus = atoi(sInput.substr(0, sInput.find("|")).c_str());
	sInput.erase(0, sInput.find("|") + 1); // Is Active?

	MISD("8");
	//iStatus = atoi(sInput.substr(0, sInput.find("|")).c_str());
	sInput.erase(0, sInput.find("|") + 1); // Playliste

	MISD("9");
	wbSongNr->setText(sInput.substr(0, sInput.find("|")));
	//sInput.erase(0, sInput.find("|") + 1); // POS ID
	
	MISE;
}



void WEB_MA::UpdateColorValues(string iAnz, string iOffset)
{
	MISS;
	weColorAnz->setText(iAnz);
	weColorOffset->setText(iOffset);
	MISE;
}
