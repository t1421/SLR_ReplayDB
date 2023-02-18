#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_MA;
class WEB_MB;
class WEB_MC;
class WEB_MD;
class WEB_Analyser;

class MISCONTAINER : public Wt::WApplication, public WEB_Toolbar , public WEB_Replay

{
public:
	
	WEB_MA *MA;	
	WEB_MB *MB;
	WEB_MC *MC;
	WEB_MD *MD;
	WEB_Analyser *Analyser;

	Wt::WFileUpload  *wfuDropZone;
	Wt::WText		 *wtStatus;
	Wt::WText		 *wtMap;
	Wt::WText		 *wtDif;
	Wt::WText		 *wtTime;
	Wt::WText		 *wtActions;
	

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

	std::string sPARA;
	std::string sBETA;

};

#endif // WEB_CONTAINER_H


