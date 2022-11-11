#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "WEB_Toolbar.h"

class MISEvent;
class WEB_MA;
class WEB_MB;
class WEB_MC;

class MISCONTAINER : public WApplication, public WEB_Toolbar

{
public:
	
	WEB_MA *MA;	
	WEB_MB *MB;
	WEB_MC *MC;

	Wt::WContainerWidget *GlobaelContainer;
	Wt::WContainerWidget *AnzeigeFrame;

	//----------------------------------------------------------------

	MISCONTAINER(const Wt::WEnvironment& env);
	~MISCONTAINER();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:

};

#endif // WEB_CONTAINER_H


