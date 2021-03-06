//#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
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
	try {
	MISS;

	sThreadName = "W";

	string sLog_path = Log_path + "W.log";
	
	char *ARGV[3];
	ARGV[0] = ".";
	ARGV[1] = "--accesslog";
	ARGV[2] = (char*)sLog_path.c_str();

	MISD("#1");
	W = new WServer(3,ARGV, "./wt_http.cfg");
	MISD("#2");
	W->addEntryPoint(Wt::EntryPointType::Application, createApplicationW);

	MISE;
	}
	catch (WServer::Exception& e) {
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


