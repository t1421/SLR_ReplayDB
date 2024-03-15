#ifndef Manager_H
#define Manager_H

#include "Thread_MIS.h"

class Replay;
#ifndef noSQL
class PMV_to_SQL;
class SQL_MIS_New;
#endif

struct Action;


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
#ifdef BrokerPVP
	void ResteLiveFiles();
	void UpdateFiles();
	int processActions();
	void AddCardToPlayer(Action *Import);
	void SetCard(unsigned int POS, unsigned short CardID, unsigned char Upgrade, unsigned char Charges, unsigned int Count);
	void SetCardBack(unsigned int POS, unsigned int iCount);
	void SetPlayer(unsigned int POS, std::string sName);
		
	unsigned int iLastAction;
	unsigned long minActionPlayer;
	unsigned long maxActionPlayer;
	
#endif
};

#endif //Manager_H

