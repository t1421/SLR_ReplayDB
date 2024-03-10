#ifndef Manager_H
#define Manager_H

#include "Thread_MIS.h"

class Replay;
#ifndef noSQL
class PMV_to_SQL;
class SQL_MIS_New;
#endif

class Manager : public Thread_MIS
{
public:
	Manager();

	//BROKER
	static broker* Bro;
	void teachM() { Bro->M = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:
	
	void Thread_Function();

	Replay * RR;

#ifndef noSQL
	PMV_to_SQL * PP;
	SQL_MIS_New * NN;
#endif


};

#endif //Manager_H

