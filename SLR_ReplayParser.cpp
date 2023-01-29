#include "incl\Broker.h" 
#include "incl\DEBUG.h" 
#include "incl\Replay.h" 

int main(int argc, char **argv)
{
	int iOut = 0;

	if (argc > 1)
	{
		std::string sFile = std::string(argv[1]);
printf("File %s\n", sFile.c_str());
		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_ReplayDB",true,true,false);
		B->teachB();		
		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{			
			printf("Action Count: %i\n", RR->CountActions());

			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type != 4014)continue;
				if (RR->ActionMatrix[i]->AdditionalInfo == "2002218")iOut++;
			}
			printf("Gate Switch Count: %i\n", iOut);

			
		}						
		//else printf("An error has occurred\nYou may want to contact Ultralord \n Your Temporarily result is: %i\n" , int(RR->ActionMatrix.size()));
			
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");
    return 0;
}

