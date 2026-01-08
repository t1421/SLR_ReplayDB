#ifndef WEB_Bounty_H
#define WEB_Bounty_H

#include "../WEB/WEB_Utility.h"

class WEB_Analyser;
class WEB_Rank;

class WEB_Bounty : public WebRefresh
{
public:

	WEB_Analyser *WR;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Bounty(WEB_Analyser *WR_);
	void WRefresh();
	bool WEB_Bounty::TabelRefresh();
	//bool Add_Player_to_Quest(std::string sEvent, unsigned long long iValue);

	Wt::WText* status;
	Wt::WTableView* table;
	Wt::WStandardItemModel* model;
	Wt::WSortFilterProxyModel* proxy;

};


#endif // WEB_Bounty
