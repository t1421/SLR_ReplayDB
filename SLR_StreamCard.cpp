#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Stream.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#include <iostream>

int main(int argc, char** argv)
{
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;
	
	DEBUG* B = new DEBUG("SLR_StreamCard", true, true, true);
	B->teachB();
	
	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();
	
	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");

	Stream* S = new Stream();
	S->teachS();
	S->Init();
	S->Start_Thread();
		
	
//K:\c++\SLR_ReplayDB\Release\Quiz\ChatLog.log

	while (Bro->bAktive)
	{
		std::cin >> buf;
		sbuf = buf;
	
		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "x"))Bro->bAktive = false;
	}

	S->Stop_Thread();

	return 0;
}

