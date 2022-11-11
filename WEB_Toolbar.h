#ifndef WEB_Toolbar_H
#define WEB_Toolbar_H



class WEB_Toolbar
{
public:
	
	WEB_Toolbar() :sToolbar(new WStackedWidget),tToolbar(new WToolBar) {};
	
	WStackedWidget *sToolbar;
	WToolBar *tToolbar;
	vector <WPushButton *> bToolbar;
	void ToolBarButton(int Index, string Name, WContainerWidget &CON);
	void updateToolbar();


	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

};

#endif //WEB_Toolbar_H


