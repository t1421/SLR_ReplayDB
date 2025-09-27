
#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Replay.h" 
#include "incl\Manager.h"
#include "incl\Utility.h" 

#ifndef noManager
#include "incl\Manager.h"
#endif
#include <iostream>

int main(int argc, char **argv)
{	
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Event_Cecker", true, true, false);
	B->teachB();	

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();	

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");	
	L->ProcessArg(argc, argv);
	if (L->sSetting != "")L->Load_Settings(L->sSetting);

	printf("%s\n", L->sLivePvPPMV);

#ifndef noManager
	Manager* M = new Manager();
	M->teachM();
	M->Start_Thread();
#endif	

	//Replay* R = new Replay();
	
	while (Bro->bAktive)
	{
		/*
		if (argc > 1 && argc > iArcCout)
		{

			sbuf = argv[iArcCout];
			iArcCout++;
			std::cout << "ARG:" << sbuf << std::endl;
		}
		else */
		{
			std::cin >> buf;
			sbuf = buf;
		}

		

		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");						
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "x"))Bro->bAktive = false;
	}
	
#ifndef noManager
	M->Stop_Thread();
#endif

	return 0;    
}

