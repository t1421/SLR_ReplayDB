#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "WEB_Toolbar.h"
#include "WEB_Replay.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

#ifdef BOT1
class WEB_MA;
#endif
#ifdef BOT2
class WEB_MB;
#endif
#ifdef BOT3
class WEB_MC;
#endif
class WEB_MD;
class WEB_Analyser;

class MISCONTAINER : public Wt::WApplication, public WEB_Toolbar , public WEB_Replay

{
public:
	
#ifdef BOT1
	WEB_MA *MA;	
#endif
#ifdef BOT2
	WEB_MB *MB;
#endif
#ifdef BOT3
	WEB_MC *MC;
#endif
	WEB_MD *MD;
	WEB_Analyser *Analyser;

	Wt::WFileUpload  *wfuDropZone;
	Wt::WText		 *wtStatus;
	Wt::WText		 *wtMap;
	Wt::WText		 *wtDif;
	Wt::WText		 *wtTime;
	//Wt::WText		 *wtActions;
	

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


