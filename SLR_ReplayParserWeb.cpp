// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

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

	DEBUG* B = new DEBUG("SLR_ReplayParserWeb",true,true,false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->LoadCards();

	MISD(Bro->L_getRANK_PATH());
	
	WEB_Main* W = new WEB_Main();
	W->teachW();
	W->Init_W();
	W->Start_Thread();

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();

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
			printf("J;new               | New Istance\n");
			printf("J;init              | calls init\n");
			printf("J;echo;[ID]         | print Card data\n");
			printf("J;imager            | Download image\n");
			printf("J;convert           | get SW image\n");
			printf("####################|###########################################\n\n");
		}
		if (Checker(sbuf, "J"))
		{
			if (Checker(sbuf, "new")) J = new CardBaseSMJ();
			if (Checker(sbuf, "init")) J->Init();
			if (Checker(sbuf, "echo"))J->EchoCard(sbuf);
			if (Checker(sbuf, "imager"))J->DownloadImage(1348,1,1);
			if (Checker(sbuf, "convert"))J->GetSWImage(1348, 1, 1);
			

		}

	}

	W->Stop_Thread();
    return 0;
}

