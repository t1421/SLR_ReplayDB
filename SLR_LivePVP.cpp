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

	printf("%s\n", L->sLivePvPPMV);

#ifndef noManager
	Manager* M = new Manager();
	M->teachM();
	M->Start_Thread();
#endif	

	Replay* R = new Replay();
	
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
			printf("R;open              | Open File\n");
			printf("R;close             | close file\n");
			printf("R;read              | Read Delta\n");			
			printf("R;new               | New Replay\n");
			printf("####################|###########################################\n\n");							
			printf("R;echo;head         | Outputs Headerdata\n");
			printf("R;echo;allied       | Outputs Allied Table\n");
			printf("R;echo;team         | Outputs Team Table\n");
			printf("R;echo;player       | Outputs Players\n");
			printf("R;echo;deck         | Outputs Deck of Replay recorder\n");
			printf("R;echo;action;*     | Outputs all Actions\n");
			printf("R;echo;action;[ID]  | Outputs Actions with ID\n");
			printf("####################|###########################################\n\n");
		}


		if (Checker(sbuf, "R"))
		{
			
			if (Checker(sbuf, "open"))R->LoadPMV("C:\\Users\\MIS\\Documents\\BattleForge\\Diag\\movie.pmv");
			if (Checker(sbuf, "close"))R->close();
			if (Checker(sbuf, "read"))R->readDelta();
			if (Checker(sbuf, "new"))R = new Replay();	

			if (Checker(sbuf, "echo"))
			{
				if (Checker(sbuf, "head"))R->EchoHead();
				if (Checker(sbuf, "allied"))R->EchoAllied();
				if (Checker(sbuf, "team"))R->EchoTeam();
				if (Checker(sbuf, "player"))R->EchoPlayer();
				if (Checker(sbuf, "deck"))R->EchoPlayerDecks();

				if (Checker(sbuf, "action"))
				{
					R->EchoAction(sbuf);
				}
			}
			
		}
		
		if (Checker(sbuf, "x"))Bro->bAktive = false;
	}
	
#ifndef noManager
	M->Stop_Thread();
#endif

	return 0;    
}

