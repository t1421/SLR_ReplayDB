//#define DF_Debug

#include "stdafx.h"

#include "Manager.h"
#include "Replay.h" 
#include "PMV_to_SQL.h" 
#include "SQL_MIS_New.h" 

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

broker *(Manager::Bro) = NULL;

Manager::Manager() :Thread_MIS("M")
{
	MISS;
	NN = new SQL_MIS_New("Manager");	
	MISE;
}

void Manager::Thread_Function()
{
	MISS;

	stringstream ssCMD;

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
					MISD("DONE");
				
				ssCMD.str("");
				ssCMD << "move \"" << it->path().string() << "\" \"" << Bro->L_getPMV_ARCH_PATH() << "\\" << it->path().filename().string() << "\"";
				system(ssCMD.str().c_str());
				
			}
			
			it++;
		}
		
		
		Sleep(1000);
	}	
	MISE;
}

