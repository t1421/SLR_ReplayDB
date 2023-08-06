#ifndef WEB_Analyser_Acti_H
#define WEB_Analyser_Acti_H

#include "../WEB/WEB_Utility.h"


class WEB_Analyser;

class WEB_Analyser_Acti : public WebRefresh
{
public:

	bool newData;

	WEB_Analyser *WA;
	
	Wt::WContainerWidget *cMain;

	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_Analyser_Acti(WEB_Analyser *WA_);
	void WRefresh();

	void UpdateTabelle();
	

	
	Wt::WTable *wtPlayers;
	Wt::WTable *wtActionsTypes;
	Wt::WTable *wtActions;

	bool DoSkip(std::string sAction, std::string sPlayer);
};


#endif // WEB_Analyser_Acti
