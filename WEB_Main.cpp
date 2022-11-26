//#define DF_Debug

#include "Broker.h" 

#define Log_path "LOG\\"

#include "Utility.h"
#include "WEB_Main.h"
#include "WEB_CONTAINER.h"

broker *(WEB_Main::Bro) = NULL;

std::unique_ptr<Wt::WApplication> createApplicationW(const Wt::WEnvironment& env)
{
	return std::make_unique<MISCONTAINER>(env);
}

void WEB_Main::Init_W()
{
	try {
	MISS;

	sThreadName = "W";

	std::string sLog_path = Log_path;
	sLog_path = sLog_path.append("W.log");
	
	char *ARGV[3];
	ARGV[0] = ".";
	ARGV[1] = "--accesslog";
	ARGV[2] = (char*)sLog_path.c_str();

	MISD("#1");
	W = new Wt::WServer(3,ARGV, "./wt_http.cfg");
	MISD("#2");
	W->addEntryPoint(Wt::EntryPointType::Application, createApplicationW);

	MISE;
	}
	catch (Wt::WServer::Exception& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
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


