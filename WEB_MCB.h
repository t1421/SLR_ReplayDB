#ifndef WEB_MCB_H
#define WEB_MCB_H


class WEB_MCB: public WebRefresh
{
public:
	
	WContainerWidget *cMain;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	WEB_MCB();	
};


#endif // WEB_MCB
