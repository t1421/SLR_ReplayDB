#ifndef WEB_Lotto_Admin_H
#define WEB_Lotto_Admin_H

#include "..\WEB\WEB_Utility.h"
#include "../WEB/WEB_Toolbar.h"

class WEB_Container_Lotto;
class WEB_Lotto_Admin_Main;
class WEB_Lotto_Admin_Copy;
class WEB_Lotto_Admin_Pull;

class WEB_Lotto_Admin : public WebRefresh, public WEB_Toolbar
{
public:

	WEB_Lotto_Admin(WEB_Container_Lotto *Con_);

	WEB_Lotto_Admin_Main *Main;
	WEB_Lotto_Admin_Copy *Copy;
	WEB_Lotto_Admin_Pull *Pull;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	//void WRefresh();
private:
	WEB_Container_Lotto *Con;
};


#endif // WEB_Lotto_Admin_H
