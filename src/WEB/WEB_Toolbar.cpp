//#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB\WEB_Utility.h"

#include "..\..\incl\WEB\WEB_Toolbar.h"



broker *(WEB_Toolbar::Bro) = NULL;


void WEB_Toolbar::ToolBarButton(int Index, std::string Name, Wt::WContainerWidget &CON, WebRefresh *WF)
{
	MISS;
	bToolbar.push_back(new Wt::WPushButton());
	bDisable.push_back(false);
	wfToolbar.push_back(WF);
	bToolbar[Index]->setText(Name);
	tToolbar->addButton(std::unique_ptr<Wt::WPushButton>(bToolbar[Index]));
	bToolbar[Index]->clicked().connect(std::bind([=]() {
		sToolbar->setCurrentIndex(Index);
		updateToolbar();
		WF->WRefresh();
	}));


	sToolbar->insertWidget(Index, std::unique_ptr<Wt::WContainerWidget>(std::move(&CON)));
	MISE;
}

void WEB_Toolbar::updateToolbar()
{
	MISS;
	std::string sCSS;
	for (unsigned short i = 0; i < bToolbar.size(); i++)
	{
		MISD(std::to_string(i));
		sCSS = WSTRINGtoSTRING(bToolbar[i]->styleClass());

		if (sCSS.find("button1") != sCSS.npos)sCSS.erase(sCSS.find("button1"), 7);
		if (sCSS.find("button0") != sCSS.npos)sCSS.erase(sCSS.find("button0"), 7);

		if (i == sToolbar->currentIndex())sCSS = "button1 " + sCSS;
		else sCSS = "button0" + sCSS;

		bToolbar[i]->setStyleClass(sCSS);
		bToolbar[i]->setDisabled(bDisable[i]);
	}
	MISE;
}


void WEB_Toolbar::updateFrame()
{
	MISS;
	wfToolbar[sToolbar->currentIndex()]->WRefresh();	
	MISE;
}
