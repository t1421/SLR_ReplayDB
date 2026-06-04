#ifndef WEB_Container_King_H
#define WEB_Container_King_H

#include "..\..\incl\Broker.h" 

#include "../WEB/WEB_Server.h"
//#include "../WEB/WEB_Toolbar.h"

#include "../WEB_King/WEB_King_Player.h"
#include "../WEB_King/WEB_King_Game.h"
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"

#include <Wt/WText.h>
#include <Wt/WApplication.h>
class WEB_Analyser;

class WEB_Container_King : public Wt::WApplication, public WEB_Server::Client //, public WEB_Toolbar

{
public:
	bool WA_Admin;	

	Wt::WFileUpload* wfuDropZone;
	Wt::WText* wtStatus;

	
	//----------------------------------------------------------------

	WEB_Container_King(const Wt::WEnvironment& env);
	~WEB_Container_King();

	std::string AddGame();

	void connect();
	void disconnect();
	void processChatEvent(const MISEvent& event);

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:
	void WRefresh();

	WEB_King_Player *Player;
	WEB_King_Game* Game;
	WEB_Analyser* WA;

	Wt::WContainerWidget *GlobaelContainer;
};

#endif // WEB_Container_King_H


