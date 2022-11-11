#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_Toolbar.h"

broker *(WEB_Toolbar::Bro) = NULL;

void WEB_Toolbar::ToolBarButton(int Index, string Name, WContainerWidget &CON)
{
	MISS;
	bToolbar.push_back(new Wt::WPushButton());
	bToolbar[Index]->setText(Name);
	tToolbar->addButton(std::unique_ptr<Wt::WPushButton>(bToolbar[Index]));
	bToolbar[Index]->clicked().connect(std::bind([=]() {
		sToolbar->setCurrentIndex(Index);
		updateToolbar();
	}));

	sToolbar->insertWidget(Index, std::unique_ptr<WContainerWidget>(std::move(&CON)));
	MISE;
}

void WEB_Toolbar::updateToolbar()
{
	MISS;
	string sCSS;
	for (unsigned short i = 0; i < bToolbar.size(); i++)
	{
		MISD(to_string(i));
		sCSS = WSTRINGtoSTRING(bToolbar[i]->styleClass());

		if (sCSS.find("button1") != sCSS.npos)sCSS.erase(sCSS.find("button1"), 7);
		if (sCSS.find("button0") != sCSS.npos)sCSS.erase(sCSS.find("button0"), 7);

		if (i == sToolbar->currentIndex())sCSS = "button1 " + sCSS;
		else sCSS = "button0" + sCSS;

		bToolbar[i]->setStyleClass(sCSS);
	}
	MISE;
}