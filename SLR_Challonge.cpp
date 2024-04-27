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
			printf("C;update            | Set the Challonge ID to track\n");
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "C"))
		{
			if (Checker(sbuf, "set"))
				C->setID(sbuf.c_str());
			if (Checker(sbuf, "update"))
				C->getMatches();


			/// if new stage then getPlayers();

			/*
			if (Checker(sbuf, "img"))		
				for each (SMJCard* iCard in J->SMJMatrix)
				{
					printf("%i\n", iCard->cardId);
					Bro->J_GetImage(
						iCard->cardId,
						3,
						3,
						1,
						false);
				}
			*/
			/*
			if (Checker(sbuf, "booster"))
			{
				Tome_Booster* TB = J->OpenBooster(sbuf.c_str());
				for (int i = 0; i < TB->vCards.size(); i++)
					printf("%i\n", TB->vCards[i]->cardId);
					//MISD(TB->vCards[i]->cardId + "#" + TB->vCards[i]->cardName);
			}
			*/
		}
	}
	
	return 0;    
}

