//#define DF_Debug

#include "..\..\incl\Broker.h" 
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"
#include "..\..\incl\WEB\WEB_Utility.h"
#include "..\..\incl\WEB\WEB_ME.h"
#include "..\..\incl\WEB\WEB_MF.h"
#include "..\..\incl\WEB\WEB_Analyser.h"
#include "..\..\incl\WEB\WEB_CONTAINER.h"

#include <Wt/WBootstrapTheme.h> 
#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WGridLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WApplication.h>
#include <Wt/WEnvironment.h>
#include <string>


broker *(MISCONTAINER::Bro) = NULL;

MISCONTAINER::MISCONTAINER(const Wt::WEnvironment& env)
	: WApplication(env)
{
	MISS;
	if (!env.getParameterValues("PARAM").empty())
	{
		const std::string *PARA = (env.getParameter("PARAM"));
		sPARA.assign(PARA->c_str());
	}
	if (sPARA == "DEBUG")
	{
		MISERROR("DEBUG ON")
		WA_Debug = true;
		ReNewTaps();
	}
	
	MISD("#1");
	auto bootstrapTheme = std::make_shared<Wt::WBootstrapTheme>();
	bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
	bootstrapTheme->setResponsive(true);

	MISD("#2");

	WApplication::instance()->setTheme(bootstrapTheme);
	WApplication::instance()->setTitle("SLR - Replay Checker");
	WApplication::instance()->useStyleSheet(Wt::WLink("./resources/main.css"));

	MISD("#3");	

	ME = new WEB_ME(this);
	MF = new WEB_MF(this);
	wfuDropZone = new Wt::WFileUpload();
	wtStatus = new Wt::WText("Waiting for Replay");
	
	MISD("#4");
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	GlobaelContainer = root()->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>());	
	GlobaelContainer->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h2><b>Replay Checking</b></h2>"))),0,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wfuDropZone)),1,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtStatus)),2,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::tToolbar)),3,0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(WEB_Toolbar::sToolbar)), 4, 0);

	MISD("#5");

	Wt::WColor wTemp;

	wTemp = Wt::WColor(222, 222, 222);
	root()->decorationStyle().setForegroundColor(wTemp);

	wTemp = Wt::WColor(20, 20, 20);
	root()->decorationStyle().setBackgroundColor(wTemp);

	MISD("#6");

#ifdef VornskrLIST
	if (Bro->L_getBOTRankMode(VornskrLIST) <10
		|| sPARA == "BETA")WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Old School Efficiency", *MD->cMain, MD);
#endif

	if (Bro->L_getBOTRankMode(BOT4LIST) <10
		|| sPARA == "BOT4")WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "BOT4", *ME->cMain, ME);

	if (Bro->L_getBOTRankMode(KOTGLIST1) <10
		|| sPARA == "KOTG")WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "KOTG", *MF->cMain, MF);

	//WEB_Toolbar::ToolBarButton(WEB_Toolbar::bToolbar.size(), "Analyser", *cMainAnalyser, this);

	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Head", *this->Head->cMain, this->Head);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Deck", *this->Deck->cMain, this->Deck);
	ToolBarButton(WEB_Toolbar::bToolbar.size(), "Acti", *this->Acti->cMain, this->Acti);
	
	//WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() -1);	
	if (Bro->L_getBOTRankMode(BOT4LIST) <10 || sPARA == "KOTG")WEB_Toolbar::sToolbar->setCurrentIndex(0);
	else WEB_Toolbar::sToolbar->setCurrentIndex(WEB_Toolbar::bToolbar.size() - 2);
	WEB_Toolbar::updateToolbar();

	MISD("#7");

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

		if (NewReplay(WSTRINGtoSTRING(wfuDropZone->spoolFileName())))
		{
			MISD("#NewReplay");
			wtStatus->setText("PMV OK \n");
		}
		else wtStatus->setText("<h4> An error has occurred </h4> <h4> You may want to contact Ultralord </h4> \n");

		WRefresh();
		WEB_Toolbar::updateFrame();

	});

	MISE;
}


MISCONTAINER::~MISCONTAINER()
{
	MISS;
	MISE;
}

void MISCONTAINER::WRefresh()
{
	MISS;
	MISE;
}


void MISCONTAINER::connect()
{
	MISS;
	if (Bro->W->WW)
		if (Bro->W->WW->connect
		(this, std::bind(&MISCONTAINER::processChatEvent, this, std::placeholders::_1)))
			Wt::WApplication::instance()->enableUpdates(true);
	MISE;
}


void MISCONTAINER::processChatEvent(const MISEvent& event)
{
	MISS;
	MISD(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);
	
	WApplication *app = WApplication::instance();
	/*
	if (event.Value1_ == "Volume")
	{
		DV->setVolume(atoi(event.Value2_.c_str()), atoi(event.Value3_.c_str()));
	}

	if (event.Value1_ == "Switch")
	{
		DV->setAktive(atoi(event.Value2_.c_str()), event.Value3_ == "1");
	}

	if (event.Value1_ == "MA_Kopf")
	{
		MA->Update_Kopf(event.Value3_);
		MA->Update_Note(atoi(event.Value4_.c_str()));
	}

	if (event.Value1_ == "MA_DS")
	{
		MA->Update_DS(event.Value2_);
	}

	if (event.Value1_ == "INIT")
	{
		if (event.Value2_ == "LastInit")DB->UpdateLastInit(event.Value3_);
		if (event.Value2_ == "Ordner")DB->UpdateOrdner(event.Value3_);
		if (event.Value2_ == "LastFullInit")DB->UpdateLastFullInt(event.Value3_);
	}

	if (event.Value1_ == "Pos")
	{
		MA->Update_Pos(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "InStart")
	{
		FA->setVolume(0, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "OutStart")
	{
		FA->setVolume(1, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "Fade")
	{
		FA->setVolume(2, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "JumpFade")
	{
		FA->setVolume(3, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "FadeDelay")
	{
		FA->setVolume(4, atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PlayMode")
	{
		FA->setPlayMode(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PL_ANZ")
	{
		PL->Neue_Anzahl_WS(atoi(event.Value2_.c_str()));
	}

	if (event.Value1_ == "PL_Song")
	{
		PL->Update_WS_Row(atoi(event.Value2_.c_str()), event.Value3_);
	}

	if (event.Value1_ == "InitWD")
	{
		DV->Init_WD_Row(atoi(event.Value2_.c_str()), event.Value3_);
	}

	if (event.Value1_ == "MA_Info")
	{
		MA->Update_DS(event.Value2_);
	}

	if (event.Value1_ == "COLOR_NEW")
	{
		int iColorIndex = atoi(event.Value2_.c_str());
		istringstream iss = istringstream(event.Value3_);
		string sColor;

		for (int i = 0; getline(iss, sColor, '_') && i < 3; i++)
		{
			if (sColor.length() == 0) break;
			Colors[cSOL][iColorIndex][i] = atoi(sColor.c_str());
		}
	}

	if (event.Value1_ == "KOPF_NEW")
	{
		MA->sCover_ID[cSOL] = event.Value2_;
	}

	if (event.Value1_ == "FADE_SONG")
	{
		int iStatus = atoi(event.Value2_.c_str());
		if (iStatus <= 0) iStatus = 1;
		if (iStatus >= 100) iStatus = 100;
		setFadeStatus(iStatus, Stack->currentIndex());

		if (Stack->currentIndex() == 2)MA->setFadeStatus(iStatus);


		if (iStatus >= 99)
		{
			for (int i = 0; i < MaxColorIndex; i++)
				for (int j = 0; j < 3; j++)
					Colors[cIST][i][j] = Colors[cSOL][i][j];

			for (int i = 0; i < MaxRegister; i++) setFadeStatus(100, i);
			MA->setFadeStatus(100);

		}
	}

	if (event.Value1_ == "SAVE")
	{
		Bro->L_TriggerSave();
	}

	if (event.Value1_ == "FP")
	{
		if (event.Value2_ == "FP_Value")FP->UpdateFP(event.Value3_);
	}

	if (event.Value1_ == "TH")
	{
		if (event.Value2_ == "FP")TH->UpdateFP(event.Value3_);
		if (event.Value2_ == "IN")TH->UpdateIN(event.Value3_);
		if (event.Value2_ == "TH")TH->UpdateTH(event.Value3_);
		if (event.Value2_ == "DB")TH->UpdateDB(event.Value3_);
	}

	if (event.Value1_ == "MA_Color")
	{
		MA->UpdateColorValues(event.Value2_, event.Value3_);
	}
	*/
	app->triggerUpdate();

	//DB->UpdateMes(event.Value1_ + ";" + event.Value2_ + ";" + event.Value3_ + ";" + event.Value4_);

	MISE;
}
