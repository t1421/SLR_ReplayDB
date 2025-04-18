#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\WEB\WEB_Main.h"
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Utility.h" 

int main()
{
	char buf[1024] = { '0' };
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Tome", true, true, false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();

	WEB_Main* W = new WEB_Main();
	W->teachW();
	W->Init_W();
	W->Start_Thread();

	while (Bro->bAktive)
	{
		std::cin >> buf;
		sbuf = buf;
		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;
	
		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");
			printf("J;img               | Download needed Img Files\n");
			printf("J;booster;[ID]      | Opens a Booster\n");			
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "J"))
		{
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
	W->Stop_Thread();
	return 0;    
}

