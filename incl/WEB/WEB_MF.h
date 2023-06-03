#ifndef WEB_MF_H
#define WEB_MF_H

#include "WEB_Toolbar.h"

class WEB_MFA;
class WEB_Rank;
class WEB_Analyser;


class WEB_MF : public WEB_Toolbar , public WebRefresh
{
public:

	WEB_MFA *A;
	WEB_Rank *B[4];	

	//Wt::WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MF(WEB_Analyser *WA_);
	void WRefresh();
	
};


#endif // WEB_MF
