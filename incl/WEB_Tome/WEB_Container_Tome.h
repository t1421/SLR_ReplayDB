#ifndef WEB_CONTAINER_TOME_H
#define WEB_CONTAINER_TOME_H

#include "..\WEB\WEB_Server.h"
#include "..\WEB\WEB_Toolbar.h"
#include "..\..\incl\DataTypes.h" 

#include <Wt/WText.h>
#include <Wt/WFileUpload.h>
#include <Wt/WApplication.h>

class WEB_Tome_Admin;
class WEB_Tome_Login;
class WEB_Tome_Debug;
class WEB_Tome_Player;
class WEB_Tome_Public;
class WEB_Tome_Leave;

#define Booster_Size_X 32
#define Booster_Size_Y 38

#define Card_Size_X 93
#define Card_Size_Y 128

class WEB_Container_Tome : public Wt::WApplication, public WEB_Server::Client, public WEB_Toolbar

{
public:
	WEB_Tome_Admin  *Admin;
	WEB_Tome_Login  *Login;
	WEB_Tome_Player *Player;
	WEB_Tome_Public *Public;
	WEB_Tome_Leave *Leave;
	WEB_Tome_Debug *Debug;

	int BroGameID;

	std::string sParamGameID;
	std::string sParamAdminID;
	std::string sParamPlayerID;
	std::string sParamDebug;

	void connect();
	void disconnect();
	void PublicReset();
	void processChatEvent(const MISEvent& event);

	void DrawBooster(Wt::WTable *wtTabelle, std::vector <Tome_Booster*> vAllBoosters, bool bFilter);
	void DrawCard(Wt::WTable* wtTabelle, std::vector <SMJCard*> vAllCards);
	std::string BoosterToFilter(std::vector <Tome_Booster*> vAllBoosters, std::string sName);
	std::string getPlayerID();

	//----------------------------------------------------------------

	void WRefresh();

	WEB_Container_Tome(const Wt::WEnvironment& env);
	~WEB_Container_Tome();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:

	Wt::WContainerWidget *GlobaelContainer;
	Wt::WAnchor *waLink;
	Wt::WAnchor *waLink2;
	//std::string sGetParam(const Wt::WEnvironment& env, std::string sParam);
	

};

#endif // WEB_CONTAINER_TOME_H


