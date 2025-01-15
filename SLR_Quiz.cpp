#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include <curl/curl.h>
#include "incl\Utility.h" 
#include "incl\Quiz.h" 
#include "incl\Question.h" 

#include <iostream> 
int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_Quiz", true, true, false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();
	L->Load_Settings("Private.ini");

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();

	Quiz* Q = new Quiz();
	Q->teachQ();
	Q->Init();
	Q->Start_Thread();

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
			printf("echo;[ID]           | Echo Quiz Vars\n");
			printf("start;[ID]          | Start Quit with ID\n");			
			printf("win                 | Shows winner of current quiz\n");
			printf("resetWins           | Resets Winner\n");
			printf("resetPoints         | Resets Winner\n");
			printf("end                 | End Quiz\n");
			printf("endX;[ID]           | End Quiz of ID\n");
			printf("winX;[ID]           | Shows winner of ID\n");
			printf("####################|###########################################\n\n");
		}
		

		if (Checker(sbuf, "echo"))Q->vQuestion[atoi(sbuf.c_str())]->echo();
		if (Checker(sbuf, "start"))Q->Start(atoi(sbuf.c_str()));
		if (Checker(sbuf, "winX"))Q->Winner(atoi(sbuf.c_str()));
		if (Checker(sbuf, "win"))Q->Winner();
		if (Checker(sbuf, "resetWins"))Q->ResetWinner();
		if (Checker(sbuf, "resetPoints"))Q->ResetPoints();
		if (Checker(sbuf, "end"))Q->End();
		if (Checker(sbuf, "endX"))Q->End(atoi(sbuf.c_str()));
		
	}

	Q->Stop_Thread();
	
	return 0;    
}

