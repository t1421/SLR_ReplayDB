#include "incl\Broker.h"
#include "incl\DEBUG.h" 
//#include "incl\CardBaseSMJ.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#define OneErrorLeave false

int main(int argc, char **argv)
{	
	if (argc > 1)
	{
		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_Event_Cecker", true, true, false);
		B->teachB();
		Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
		Bro->B->Fill_DBArray("OK", "*", "*", "true");

		//CardBaseSMJ* J = new CardBaseSMJ();
		//J->teachJ();
		//J->Init();

		Replay * RR = new Replay();
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");

	return 0;    
}

