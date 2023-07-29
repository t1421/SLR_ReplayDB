#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "WEB_Server.h"
#include "WEB_Toolbar.h"
#include "WEB_Analyser.h"
#include "WEB_Analyser_Head.h"
#include "WEB_Analyser_Deck.h"
#include "WEB_Analyser_Acti.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_ME;
class WEB_MF;

class MISCONTAINER : public Wt::WApplication, public WEB_Toolbar, public WEB_Analyser, public WEB_Server::Client

{
public:


	void connect();
	void processChatEvent(const MISEvent& event);

	//----------------------------------------------------------------

	MISCONTAINER(const Wt::WEnvironment& env);
	~MISCONTAINER();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	void WRefresh();

	WEB_ME *ME;
	WEB_MF *MF;
	Wt::WFileUpload  *wfuDropZone;
	Wt::WText		 *wtStatus;
	Wt::WContainerWidget *GlobaelContainer;


	std::string sPARA;
	std::string sBETA;

	

};

#endif // WEB_CONTAINER_H


