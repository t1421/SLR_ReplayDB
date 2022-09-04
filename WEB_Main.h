#ifndef WEB_Main_H
#define WEB_Main_H

#include "Thread_MIS.h"

///WT LIBS
#include <Wt/WServer.h>
#include <Wt/WString.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WGridLayout.h> 
#include <Wt/WEnvironment.h>
#include <Wt/WBootstrapTheme.h> 
#include <Wt/WFileUpload.h>

#include <Wt/WTable.h>

#include <Wt/WSslInfo.h>
#include <Wt/WValidator.h>
#include <Wt/WSslCertificate.h>

using namespace Wt;

std::unique_ptr<Wt::WApplication> createApplicationW(const WEnvironment& env);

string WSTRINGtoSTRING(WString in);

class WEB_Main: public Thread_MIS  //: public Wt::WApplication
{

public:

	WServer *W;

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

