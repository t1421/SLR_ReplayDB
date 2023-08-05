//#define DF_Debug

#include "..\..\incl\Broker.h" 

#define Log_path "LOG\\"

#include "..\..\incl\Utility.h"
#include "..\..\incl\WEB\WEB_Main.h"
#include "..\..\incl\WEB\WEB_Server.h"

#if defined BrokerWeb
#include "..\..\incl\WEB\WEB_CONTAINER.h"
#endif
#if defined BrokerTome 
#include "..\..\incl\WEB\WEB_CONTAINER_Tome.h"
#endif

broker *(WEB_Main::Bro) = NULL;

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env)
{
#if defined BrokerWeb
	return std::make_unique<WEB_Container>(env);
#endif
#if defined BrokerTome 
	return std::make_unique<WEB_Container_Tome>(env);
#endif
}

void WEB_Main::Init_W()
{
	try {
		MISS;

#if defined BrokerWeb
		sThreadName = "W";
#endif
#if defined BrokerTome 
		sThreadName = "WT";
#endif

		std::string sLog_path = Log_path;
		sLog_path = sLog_path.append(sThreadName + ".log");

		char *ARGV[3];
		ARGV[0] = ".";
		ARGV[1] = "--accesslog";
		ARGV[2] = (char*)sLog_path.c_str();

		MISD("#1");
		W = new Wt::WServer(3, ARGV, "./wt_http_" + sThreadName + ".cfg");

		MISD("#2");
		WW = new WEB_Server(*W);
		MISD("#3");
		W->addEntryPoint(Wt::EntryPointType::Application, createApplication);

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


