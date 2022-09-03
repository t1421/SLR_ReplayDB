#ifndef WEB_CONTAINER_H
#define WEB_CONTAINER_H

#define MaxRegister 1

class MISEvent;
class WEB_MA;
class WEB_MB;

class MISCONTAINER : public WApplication 

{
public:
	
	//Wt::WContainerWidget *AnzeigeFrame;

	WEB_MA *MA;	
	WEB_MB *MB;

	Wt::WContainerWidget *GlobaelContainer;
	
	//----------------------------------------------------------------

	MISCONTAINER(const Wt::WEnvironment& env);


	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:

	//bool bMobile;

};

#endif // WEB_CONTAINER_H


