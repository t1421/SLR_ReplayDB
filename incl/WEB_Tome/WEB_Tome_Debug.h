#ifndef WEB_Tome_Debug_H
#define WEB_Tome_Debug_H

#include "..\WEB\WEB_Utility.h"

#include <Wt/WTextArea.h>


class WEB_Container_Tome;

class WEB_Tome_Debug : public WebRefresh
{
public:

	WEB_Tome_Debug(WEB_Container_Tome *Con_);
	void UpdateMes(std::string _Input);
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	void WRefresh();
	

private:
	WEB_Container_Tome *Con;

	void send();
	
	Wt::WContainerWidget	*messages_;
	Wt::WTextArea			*messageEdit_;
	Wt::WPushButton			*sendButton_;
};


#endif // WEB_Tome_Debug_H
