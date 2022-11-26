#ifndef WEB_MA_H
#define WEB_MA_H

#include "WEB_Utility.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

class WEB_Replay;


class WEB_MA : public WebRefresh
{
public:

	Wt::WText		 *wtStatus;

	Wt::WContainerWidget *cMain;
	WEB_Replay *WR;

	void WRefresh();

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MA(WEB_Replay *WR_);

};


#endif // WEB_MA
