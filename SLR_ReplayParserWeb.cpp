// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "prototypes.h"

#include "WEB_Main.h"

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayParserWeb");
	B->teachB();

	WEB_Main* W = new WEB_Main();
	W->teachW();

	W->Init_W();
	W->Start_Thread();

	while (Bro->bAktive)
	{
		std::cin >> buf;
		if (string(buf) == "x")Bro->bAktive = false;
	}

	W->Stop_Thread();
    return 0;
}

