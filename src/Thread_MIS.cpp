//#define DF_Debug

#include "..\incl\Broker.h"

#include "..\incl\Thread_MIS.h"

broker *(Thread_MIS::Bro) = NULL;

void Thread_MIS::Start_Thread()
{
	MISD("--> " + sThreadName);
	bRunning = true;
	if(tThread.joinable())tThread.join();
	tThread = std::thread(&Thread_MIS::Thread_Function, this);
	MISD("<-- " + sThreadName);
}

void Thread_MIS::Stop_Thread()
{
	MISD("--> " + sThreadName);
	bRunning = false;
	tThread.join();
	MISD("<--" + sThreadName);
}

void Thread_MIS::Thread_Function()
{
	MISD("-->" + sThreadName);
	MISD("KEINE THREAD FUCTION DEFFINIERT");
	MISD("<--" + sThreadName);
}

std::string Thread_MIS::Status()
{
	MISD("-->" + sThreadName);
	std::string sreturn = sThreadName + "=" + std::to_string(bRunning);
	MISD("<--" + sThreadName);
	return sreturn;
}