#ifndef WEB_Toolbar_H
#define WEB_Toolbar_H

#include <Wt/WPushButton.h>
#include <Wt/WToolBar.h>
#include <Wt/WStackedWidget.h>

#include "WEB_Utility.h"

class WEB_Toolbar
{
public:

	WEB_Toolbar() :sToolbar(new Wt::WStackedWidget), tToolbar(new Wt::WToolBar) {};


	void ToolBarButton(int Index, std::string Name, Wt::WContainerWidget &CON, WebRefresh *WF);
	void updateToolbar();
	void updateFrame();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	Wt::WStackedWidget *getToolbar() { return sToolbar; };

	Wt::WStackedWidget *sToolbar;
	Wt::WToolBar *tToolbar;
	std::vector <Wt::WPushButton *> bToolbar;
	std::vector <WebRefresh *> wfToolbar;
protected:

private:

};

#endif //WEB_Toolbar_H


