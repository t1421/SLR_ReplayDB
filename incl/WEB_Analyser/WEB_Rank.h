#ifndef WEB_Rank_H
#define WEB_Rank_H

#include "../WEB/WEB_Utility.h"

class WEB_Rank: public WebRefresh
{
public:
	
	Wt::WContainerWidget *cMain;
	Wt::WTable *wtTabelle;

	unsigned int iBOTLIST;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Rank(unsigned int _iBOTLIST);
	void WRefresh();
};


#endif // WEB_Rank
