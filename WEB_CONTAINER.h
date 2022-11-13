#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

class MISEvent;
class WEB_MA;
class WEB_MB;
class WEB_MC;

class MISCONTAINER : public WApplication, public WEB_Toolbar , public WEB_Replay

{
public:
	
	WEB_MA *MA;	
	WEB_MB *MB;
	WEB_MC *MC;

	WFileUpload  *wfuDropZone;
	WText		 *wtStatus;
	WText		 *wtMap;
	WText		 *wtDif;
	WText		 *wtTime;
	WText		 *wtActions;
	

	Wt::WContainerWidget *GlobaelContainer;
	Wt::WContainerWidget *ReplayInfo;

	void WRefresh();

	//----------------------------------------------------------------

	MISCONTAINER(const Wt::WEnvironment& env);
	~MISCONTAINER();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:

};

#endif // WEB_CONTAINER_H


