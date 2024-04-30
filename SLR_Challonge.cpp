#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\LOAD.h" 
#include "incl\Challonge.h"
#include "incl\Utility.h" 

#include <iostream> 
int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Challonge", true, true, false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");

	Challonge* C = new Challonge();
	C->teachC();
	C->Init();
	C->Start_Thread();



	while (Bro->bAktive)
	{
		if (argc > 1 && argc > iArcCout)
		{

			sbuf = argv[iArcCout];
			iArcCout++;
			std::cout << "ARG:" << sbuf << std::endl;
		}
		else
		{
			std::cin >> buf;
			sbuf = buf;
		}

		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;
	
		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");
			printf("C;set;[ID]          | Set the Challonge ID to track\n");
			printf("C;update            | Updates Matches\n");
			printf("C;players           | Updates Players\n");
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "C"))
		{
			if (Checker(sbuf, "set"))
				C->setID(sbuf.c_str());
			if (Checker(sbuf, "update"))
				C->getMatches();
			if (Checker(sbuf, "players"))
				C->getPlayers();
		}
	}

	C->Stop_Thread();
	
	return 0;    
}

