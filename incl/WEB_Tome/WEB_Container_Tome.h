#ifndef WEB_CONTAINER_TOME_H
#define WEB_CONTAINER_TOME_H

#include "..\WEB\WEB_Server.h"
#include "..\WEB\WEB_Toolbar.h"
//#include "..\WEB_Tome\Tome_Game.h"

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_Tome_Admin;
class WEB_Tome_Login;
class WEB_Tome_Debug;
class WEB_Tome_Player;
class WEB_Tome_Public;

class WEB_Container_Tome : public Wt::WApplication, public WEB_Server::Client, public WEB_Toolbar

{
public:
	WEB_Tome_Admin  *Admin;
	WEB_Tome_Login  *Login;
	WEB_Tome_Player *Player;
	WEB_Tome_Public *Public;
	WEB_Tome_Debug *Debug;

	int BroGameID;

	std::string sParamGameID;
	std::string sParamAdminID;
	std::string sParamPlayerID;
	std::string sParamDebug;

	void connect();
	void disconnect();
	void processChatEvent(const MISEvent& event);

	//----------------------------------------------------------------

	void WRefresh();

	WEB_Container_Tome(const Wt::WEnvironment& env);
	~WEB_Container_Tome();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	Wt::WContainerWidget *GlobaelContainer;
	std::string sGetParam(const Wt::WEnvironment& env, std::string sParam);
	//std::string sPARA;

};

#endif // WEB_CONTAINER_TOME_H


