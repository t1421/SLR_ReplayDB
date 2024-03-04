#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#include <iostream>

int main(int argc, char **argv)
{	
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Event_Cecker", true, true, false);
	B->teachB();
	Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
	Bro->B->Fill_DBArray("OK", "*", "*", "true");

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");

	MISD("--> MAINSCHEIFE");

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

		if (Checker(sbuf, "?"))
		{

			/*
			printf("####################|###########################################\n");
			printf("C;full              | Updates all cards in MYSQL\n");
			printf("C;update            | Adds neu cards to MYSQL\n");
			printf("C;imager;0          | Loads all images from WIKI in MYSQL\n");
			printf("C;IMGtoQSL;[ID]     | Loads images for CARDID from WIKI in MYSQL\n");
			printf("C;upload;[ID]       | Uploads images for CARDID from TempDir in MYSQL\n");
			printf("C;download;[ID]     | Loads images for MYSQL\n");
			printf("####################|###########################################\n\n");
			*/			
		}


		if (Checker(sbuf, "J"))
		{
			//if (Checker(sbuf, "update"))J->SMJtoSQL(false);			
		}

		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;
	}

	MISD("<-- MAINSCHEIFE");
	
	return 0;    
}

