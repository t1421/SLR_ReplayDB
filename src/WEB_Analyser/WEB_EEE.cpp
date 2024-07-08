//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_EEE.h"
#include "..\..\incl\WEB_Analyser\WEB_EEE_Check.h"

#include <Wt/WSlider.h>
#include <Wt/WBreak.h>
#include <iomanip>

broker *(WEB_EEE::Bro) = NULL;


std::string WEB_EEE::TimeToText(std::time_t timestamp)
{
	std::tm localTime;
	localtime_s(&localTime, &timestamp);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%d.%m.%Y %H:%M:%S");
	return oss.str();
}

WEB_EEE::WEB_EEE(WEB_Analyser *WA_)
{
	MISS;

	Bro->EEEUpdateRankModes();

	cMain = new Wt::WContainerWidget();

	slider = new Wt::WSlider();
	sliderText = new Wt::WText();
	sliderTextLow = new Wt::WText();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderText)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(slider)));	
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sliderTextLow)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WBreak())));
	

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(tToolbar)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(sToolbar)));

	MISD("#10");

	ALL = new WEB_EEE_Check(WA_, 0);
	WEB_Toolbar::ToolBarButton(0, "Total", *ALL->cMain, ALL);

	MISD("#11");
	for (unsigned int i = 1; i < EEESize; i++)
	{
		Check[i] = new WEB_EEE_Check(WA_, i);
		WEB_Toolbar::ToolBarButton(i, std::to_string(i), *Check[i]->cMain, Check[i]);
		WEB_Toolbar::bDisable[i] = (Bro->L_getEEE_RankMode(i) == 10);
		if(!WEB_Toolbar::bDisable[i]) WEB_Toolbar::sToolbar->setCurrentIndex(i);
	}
	MISD("#100");

	slider->resize(300, 50);
	slider->disable();

	MISD("#102");

	WEB_Toolbar::updateToolbar();
	WRefresh();
	
	MISE;
}

void WEB_EEE::WRefresh()
{
	MISS;

	std::time_t timestampS;
	std::time_t timestampE;

	sliderText->setText(" ");
	sliderTextLow->setText("Now: " + TimeToText(Bro->L_getEEE_Now()));
	slider->setRange(0, 0);
	slider->setValue(0);

	MISD("#11");
	for (unsigned int i = 1; i < EEESize; i++)
	{
		WEB_Toolbar::bDisable[i] = (Bro->L_getEEE_RankMode(i) == 10);
		//if (!WEB_Toolbar::bDisable[i]) WEB_Toolbar::sToolbar->setCurrentIndex(i);

		if (Bro->L_getEEE_RankMode(i) == 2)
		{
			timestampS = Bro->L_getEEE_Start(i);
			timestampE = Bro->L_getEEE_End(i);
			std::stringstream Text;
			Text << "SSS " << std::to_string(i) << " Timeframe: " << TimeToText(timestampS) << " - " << TimeToText(timestampE);
			sliderText->setText(Text.str());
			
			slider->setRange(timestampS, timestampE);
			slider->setValue(Bro->L_getEEE_Now());

			//WEB_Toolbar::sToolbar->setCurrentIndex(i);
		}
	}

	if (sliderText->text() == " ")for (unsigned int i = 1; i < EEESize; i++)
		{
			timestampS = Bro->L_getEEE_Start(i);
			if (timestampS > Bro->L_getEEE_Now())
				sliderText->setText("Next SSS is " + std::to_string(i) + " starting at " + TimeToText(timestampS));
		}

	if (sliderText->text() == " ")
	{
		sliderText->setText("SSS is over, THX for joining");
		slider->setHidden(true);
		sliderTextLow->setHidden(true);
	}

	MISD("#101");
	//MISD(sToolbar->currentIndex());

	updateFrame();
	MISE;
}

