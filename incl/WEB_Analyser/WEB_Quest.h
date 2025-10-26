#ifndef WEB_Quest_H
#define WEB_Quest_H

#include "../WEB/WEB_Utility.h"

class WEB_Analyser;
class WEB_Rank;

class WEB_Quest : public WebRefresh
{
public:

	WEB_Analyser *WR;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Quest(WEB_Analyser *WR_);
	void WRefresh();


	Wt::WLineEdit* filterEdit;
	Wt::WText* status;
	Wt::WTableView* table;
	Wt::WStandardItemModel* model;
	Wt::WSortFilterProxyModel* proxy;

};


#endif // WEB_Quest
