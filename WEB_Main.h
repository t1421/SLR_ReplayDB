#ifndef WEB_Main_H
#define WEB_Main_H

#include "Thread_MIS.h"

///WT LIBS
#include <Wt/WServer.h>
#include <Wt/WString.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WLineEdit.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>
#include <Wt/WComboBox.h>
#include <Wt/WGridLayout.h>
#include <Wt/WTextArea.h>
#include <Wt/WRadioButton.h>
#include <Wt/WButtonGroup.h>
#include <Wt/WSlider.h>
#include <Wt/WEnvironment.h>
#include <Wt/WApplication.h>
#include <Wt/WBootstrapTheme.h> 
#include <Wt/WToolBar.h>
#include <Wt/WCheckBox.h>
#include <Wt/WTable.h>
#include <Wt/WSelectionBox.h>
#include <Wt/WStackedWidget.h>

using namespace Wt;

class MISSERVER;

std::unique_ptr<Wt::WApplication> createApplicationW(const WEnvironment& env);
std::unique_ptr<Wt::WApplication> createApplicationWS(const WEnvironment& env, broker *Bro);

string WSTRINGtoSTRING(WString in);

class WEB_Main: public Thread_MIS  //: public Wt::WApplication
{

public:

	WServer *W;
	MISSERVER *WW;

	WEB_Main() :Thread_MIS("W?") {};

	void Init_W();
	void Init_WS();

	void Thread_Function();
	virtual void Stop_Thread();
	//BROKER
	static broker* Bro;
	void teachW() { Bro->W = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

};


#endif // WEB_Main_H

