#include "Broker.h" 
#include "DEBUG.h" 
#include "Replay.h" 

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		std::string sFile = std::string(argv[1]);

		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_ReplayDB",true,true,false);
		B->teachB();		
		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{			
			printf("Action Count: %i\n", RR->CountActions());
		}						
		else printf("An error has occurred\nYou may want to contact Ultralord \n Your Temporarily result is: %i\n" , int(RR->ActionMatrix.size()));
			
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");
    return 0;
}

