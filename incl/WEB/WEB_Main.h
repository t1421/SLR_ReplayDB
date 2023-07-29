#ifndef WEB_Main_H
#define WEB_Main_H

#include "..\..\incl\Thread_MIS.h"

#include <Wt/WServer.h>

class WEB_Server;

class WEB_Main: public Thread_MIS  //: public Wt::WApplication
{

public:

	Wt::WServer *W;
	WEB_Server *WW;

	WEB_Main() :Thread_MIS("W?") {};

	void Init_W();

	void Thread_Function();
	virtual void Stop_Thread();
	//BROKER
	static broker* Bro;
	void teachW() { Bro->W = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // WEB_Main_H

