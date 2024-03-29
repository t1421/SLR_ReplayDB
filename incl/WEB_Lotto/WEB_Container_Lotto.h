#ifndef WEB_Container_Lotto_H
#define WEB_Container_Lotto_H

#include "..\..\incl\Broker.h" 

#include "../WEB/WEB_Server.h"
#include "../WEB/WEB_Toolbar.h"

#include "../WEB_Lotto/WEB_Lotto_Admin.h"
#include "../WEB_Lotto/WEB_Lotto_Week.h"

#include <Wt/WText.h>
#include <Wt/WApplication.h>


class Replay;

class WEB_Container_Lotto : public Wt::WApplication, public WEB_Server::Client, public WEB_Toolbar

{
public:
	
	void FillMapVector();
	std::vector<std::string> vMaps;
	std::string getMapName(unsigned int iMap);

	//----------------------------------------------------------------

	WEB_Container_Lotto(const Wt::WEnvironment& env);
	~WEB_Container_Lotto();

	void connect();
	void disconnect();
	void processChatEvent(const MISEvent& event);

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:
	void WRefresh();

	WEB_Lotto_Admin *Admin;
	std::vector<WEB_Lotto_Week *> Weeks;

	Wt::WContainerWidget *GlobaelContainer;
};

#endif // WEB_CONTAINER_H


