#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#define MaxRegister 1

class MISEvent;
class WEB_MA;

class MISCONTAINER : public WApplication, public MISSERVER::Client 

{
public:

	vector<WWidget*> vWid;
	vector<vector<pair<WWidget*, string>>> VVPWSWid_Main;
	vector<vector<pair<WWidget*, string>>> VVPWSWid_Tabs[MaxRegister];
	
	WStackedWidget *Stack;

	Wt::WContainerWidget *AnzeigeFrame;

	WEB_MA *MA;	

	Wt::WContainerWidget *GlobaelContainer;
	Wt::WToolBar *toolBar;
	Wt::WPushButton *button[MaxRegister];

	//----------------------------------------------------------------

	MISCONTAINER(const Wt::WEnvironment& env);
	~MISCONTAINER();

	//void startChat();

	void MISCONTAINER::ToolBarButton(int Index, string Name, WContainerWidget &CON);

	

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:

	bool bMobile;
	void processChatEvent(const MISEvent& event);

	void setFadeStatus(int iStatus, int iIndex);

};

#endif // WEB_CONTAINER_H


