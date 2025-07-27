#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#define OneErrorLeave false

int main(int argc, char **argv)
{	
	
	if (argc > 1)
	{
		std::string sFile = std::string(argv[1]);

		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_Event_Cecker", true, true, false);
		B->teachB();
		Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
		Bro->B->Fill_DBArray("OK", "*", "*", "true");


		CardBaseSMJ* J = new CardBaseSMJ();
		J->teachJ();
		J->Init();

		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{
			std::string sFile = std::string(argv[1]);			
			Bro->B->StatusE("OK", "FILE", "TIME;ID;health_hasher;position_hasher;power_hasher;health_rounded_hasher;position_rounded_hasher;power_rounded_hasher;figures_count;entities_count;steps");

			for (auto A : RR->ActionMatrix)
			{
				//Bro->B->StatusE("OK", std::to_string(A->Type), "");
				
				if (A->Type == 4045)
					if(entry(A->AdditionalInfo,0) == "2")
						Bro->B->StatusE("OK", std::string(argv[1]), std::to_string(A->Time) + ";" + A->AdditionalInfo);
				//MISD(std::to_string(A->Type) + ";" + std::to_string(A->X) + ";" + std::to_string(A->Y));
				
			}		
		}
					
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	//system("Pause");

	return 0;    
}

