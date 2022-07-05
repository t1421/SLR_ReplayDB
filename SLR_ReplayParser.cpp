// SLR_ReplayParser.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "prototypes.h"
#include "Replay.h" 

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		string sFile = string(argv[1]);
		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{			
			printf("Action Count: %i\n", RR->ActionMatrix.size());
		}						
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");
    return 0;
}

