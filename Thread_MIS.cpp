//#define DF_Debug

#include "prototypes.h"

#include "Thread_MIS.h"

broker *(Thread_MIS::Bro) = NULL;

void Thread_MIS::Start_Thread()
{
	MISD("--> " + sThreadName);
	bRunning = true;
	tThread = thread(&Thread_MIS::Thread_Function, this);
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

string Thread_MIS::Status()
{
	MISD("-->" + sThreadName);
	string sreturn = sThreadName + "=" + to_string(bRunning);
	MISD("<--" + sThreadName);
	return sreturn;
}