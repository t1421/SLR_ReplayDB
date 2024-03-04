// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//
#define DF_Debug

#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\WEB\WEB_Main.h"
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Utility.h" 


int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Lotto", true, true, false);
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

	Bro->INIT();

	

	while (Bro->bAktive)
	{
		std::cin >> buf;
		sbuf = buf;
		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;

		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");			
			printf("J;echo;[ID]         | print Card data\n");
			printf("J;ALL_S             | Downloads all Cards Simpel (incl SW) \n");
			printf("####################|###########################################\n\n");
		}
		if (Checker(sbuf, "J"))
		{
			if (Checker(sbuf, "echo"))J->EchoCard(sbuf);			
			if (Checker(sbuf, "ALL_S"))J->AllIMGSimpel();
		}
		
	}

	W->Stop_Thread();
	return 0;
}

