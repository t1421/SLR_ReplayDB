#ifndef Thread_MIS_H
#define Thread_MIS_H

#include <chrono>
#include <thread>

class Thread_MIS
{
public:
	
	Thread_MIS():sThreadName("?"){};
	Thread_MIS(std::string sName) :sThreadName(sName) {};

	virtual void Start_Thread();
	virtual void Stop_Thread();
	virtual void Thread_Function();
	std::string Status();

	std::thread tThread;
	bool bRunning;
	std::string sThreadName;

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:

};

#endif //Thread_MIS_H


