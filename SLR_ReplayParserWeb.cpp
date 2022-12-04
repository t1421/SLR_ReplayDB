// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "Broker.h"
#include "DEBUG.h" 
#include "WEB_Main.h"
#include "LOAD.h" 

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayParserWeb",true,true,false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->LoadCards();
	
	WEB_Main* W = new WEB_Main();
	W->teachW();
	W->Init_W();
	W->Start_Thread();

	while (Bro->bAktive)
	{
		std::cin >> buf;
		if (std::string(buf) == "x")Bro->bAktive = false;
	}

	W->Stop_Thread();
    return 0;
}

