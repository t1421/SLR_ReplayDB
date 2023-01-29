//#define DF_Debug

#include "..\incl\Broker.h" 

#include "..\incl\Manager.h"
#include "..\incl\Replay.h" 
#include "..\incl\PMV_to_SQL.h" 
#include "..\incl\SQL_MIS_New.h" 

#include "..\incl\Utility.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

broker *(Manager::Bro) = NULL;

Manager::Manager() :Thread_MIS("Manager")
{
	MISS;
	NN = new SQL_MIS_New("Manager");	
	MISE;
}

void Manager::Thread_Function()
{
	MISS;

	std::stringstream ssCMD;

	while (bRunning)
	{
		
		path p = Bro->L_getPMV_AUTO_PATH();
		recursive_directory_iterator it = recursive_directory_iterator(p);
	
		while (it != recursive_directory_iterator{})
		{
		
			if (!(it->path().extension() == ".pmv" || it->path().extension() == ".PMV"))
			{
				it++;
				continue;
			}
			
			RR = new Replay();
			if (RR->LoadPMV(it->path().string()))
			{
				
				PP = new PMV_to_SQL();
				PP->UseThisSQL(NN);
				
				if (PP->UseThisPMV(RR))
				{
					path dir(it->path());
					if (dir.parent_path().string() != "REPLAY_AUTO")PP->sEvent = dir.parent_path().filename().string();
					if(PP->Upload())MISD("DONE");										
				} else MISD("Error using Replay Object ");
					
				
				ssCMD.str("");
				ssCMD << "move \"" << it->path().string() << "\" \"" << Bro->L_getPMV_ARCH_PATH();
				//MISD(ssCMD.str());
				if (PP->sEvent != "" && PP->sEvent != "REPLAY_AUTO") ssCMD << "\\" << PP->sEvent;
				//MISD(ssCMD.str());
				ssCMD << "\\" << it->path().filename().string() << "\"";
				//MISD(ssCMD.str());
				system(ssCMD.str().c_str());
				
			}
			
			it++;
		}
		
		
		Sleep(1000);
		
	}	
	MISE;
}

