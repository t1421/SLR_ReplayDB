//#define DF_Debug

#include "..\..\incl\Broker.h" 

#define Log_path "LOG\\"

#include "..\..\incl\Utility.h"
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_CONTAINER.h"

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
	#ifdef __linux__
	W = new Wt::WServer(3,ARGV, "./Release/wt_http_Linux.cfg");
	#else
	W = new Wt::WServer(3,ARGV, "./wt_http.cfg");
	#endif
	
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


