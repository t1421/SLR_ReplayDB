#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_SERVER.h"
#include "WEB_CONTAINER.h"

broker *(WEB_Main::Bro) = NULL;

std::unique_ptr<Wt::WApplication> createApplicationW(const WEnvironment& env)
{
	//MISS;
	return Wt::cpp14::make_unique<MISCONTAINER>(env);
	//MISE;
}

string WSTRINGtoSTRING(WString in)
{
	//MISS;
	stringstream ss;
	ss << in;
	return ss.str();
	//MISE;
}

void WEB_Main::Init_W()
{
	MISS;

	sThreadName = "W";

	string sLog_path = Log_path + "W.log";
	
	char *ARGV[13];
	ARGV[0] = ".";
	ARGV[1] = "--docroot";
	ARGV[2] = ".";
	ARGV[3] = "--http-address";
	ARGV[4] = "0.0.0.0";
	ARGV[5] = "--http-port";
	ARGV[6] = "8080";
	ARGV[7] = "--accesslog";
	ARGV[8] = (char*)sLog_path.c_str();
	ARGV[9] = "--resources-dir";
	ARGV[10] = "./resources";
	ARGV[11] = "--c";
	ARGV[12] = "wt_config_W.xml";

	MISD("#1");
	
	W = new WServer(ARGV[0]);
	MISD("#2");
	W->setServerConfiguration(13, ARGV, WTHTTP_CONFIGURATION);
	MISD("#3");
	WW = new MISSERVER(*W);
	MISD("#4");
	W->addEntryPoint(Wt::EntryPointType::Application, createApplicationW);
	
	MISE;
}

void WEB_Main::Thread_Function()
{
	MISS;
	W->start();
	MISD("#1");
	while (bRunning)Sleep(1000);
	MISE;
}

void WEB_Main::Stop_Thread()
{
	MISS;
	W->stop();
	MISD("#1");
	Thread_MIS::Stop_Thread();	
	MISE;
}


