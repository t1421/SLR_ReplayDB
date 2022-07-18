// SLR_ReplayParser.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "prototypes.h"
#include "Replay.h" 

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		string sFile = string(argv[1]);

		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_ReplayDB",false,false,false);
		B->teachB();		
		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{			
			printf("Action Count: %i\n", RR->CountActions());
		}						
		else printf("An error has occurred\nYou may want to contact Ultralord \n Your Temporarily result is: %i\n" , to_string(RR->ActionMatrix.size()));
			
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");
    return 0;
}

