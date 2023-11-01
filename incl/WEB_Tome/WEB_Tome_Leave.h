#ifndef WEB_Tome_Leave_H
#define WEB_Tome_Leave_H

#include "..\WEB\WEB_Utility.h"

#include <Wt/WTextArea.h>


class WEB_Container_Tome;

class WEB_Tome_Leave : public WebRefresh
{
public:

	WEB_Tome_Leave(WEB_Container_Tome *Con_);

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
	

private:
	WEB_Container_Tome *Con;
};


#endif // WEB_Tome_Leave_H
