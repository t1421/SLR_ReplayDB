#ifndef WEB_Container_Lotto_H
#define WEB_Container_Lotto_H

#include "..\..\incl\Broker.h" 

#include "../WEB/WEB_Server.h"
#include "../WEB/WEB_Toolbar.h"
//#include "WEB_Analyser.h"
//#include "WEB_Analyser_Head.h"
//#include "WEB_Analyser_Deck.h"
//#include "WEB_Analyser_Acti.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

//class WEB_ME;

class WEB_Container_Lotto : public Wt::WApplication, public WEB_Toolbar //, public WEB_Analyser

{
public:

	//----------------------------------------------------------------

	WEB_Container_Lotto(const Wt::WEnvironment& env);
	~WEB_Container_Lotto();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	void WRefresh();

	//WEB_ME *ME;
	Wt::WFileUpload  *wfuDropZone;
	Wt::WText		 *wtStatus;
	Wt::WContainerWidget *GlobaelContainer;
	Wt::WAnchor *waLink;

	std::string sPARA;
};

#endif // WEB_CONTAINER_H

