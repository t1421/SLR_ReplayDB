#ifndef WEB_Lotto_Admin_Copy_H
#define WEB_Lotto_Admin_Copy_H

#include "..\WEB\WEB_Utility.h"

class WEB_Container_Lotto;

class WEB_Lotto_Admin_Copy : public WebRefresh
{
public:

	WEB_Lotto_Admin_Copy(WEB_Container_Lotto *Con_);

	Wt::WTable *wtTabelle1;
	Wt::WTable *wtTabelle2;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	//void WRefresh();
private:
	WEB_Container_Lotto *Con;

	void FillCards();
	void FillMaps();
	
};


#endif // WEB_Lotto_Admin_Copy
