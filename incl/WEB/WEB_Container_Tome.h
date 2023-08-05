#ifndef WEB_CONTAINER_TOME_H
#define WEB_CONTAINER_TOME_H

#include "WEB_Server.h"
#include "WEB_Toolbar.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_ME;

class WEB_Container_Tome : public Wt::WApplication, public WEB_Server::Client

{
public:


	void connect();
	void processChatEvent(const MISEvent& event);

	//----------------------------------------------------------------

	WEB_Container_Tome(const Wt::WEnvironment& env);
	~WEB_Container_Tome();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	Wt::WContainerWidget *GlobaelContainer;

	void WRefresh();

	std::string sPARA;

};

#endif // WEB_CONTAINER_TOME_H


