// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\WEB\WEB_Main.h"
#include "incl\LOAD.h" 
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

	

	Bro->INIT();

	while (Bro->bAktive)
	{
		std::cin >> buf;
		sbuf = buf;		
		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;

	}

	W->Stop_Thread();
    return 0;
}

