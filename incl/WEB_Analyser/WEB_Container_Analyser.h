#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#include "../WEB/WEB_Server.h"
#include "../WEB/WEB_Toolbar.h"
#include "WEB_Analyser.h"
#include "WEB_Analyser_Head.h"
#include "WEB_Analyser_Deck.h"
#include "WEB_Analyser_Acti.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_ME;

class WEB_Container : public Wt::WApplication, public WEB_Toolbar, public WEB_Analyser

{
public:

	//----------------------------------------------------------------

	WEB_Container(const Wt::WEnvironment& env);
	~WEB_Container();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	void WRefresh();

	WEB_ME *ME;
	Wt::WFileUpload  *wfuDropZone;
	Wt::WText		 *wtStatus;
	Wt::WContainerWidget *GlobaelContainer;
	Wt::WAnchor *waLink;

	std::string sPARA;
};

#endif // WEB_CONTAINER_H


