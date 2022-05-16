// SLR_ReplayDB.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "Replay.h" 
#include "PMV_to_SQL.h" 

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayDB");
	B->teachB();

	SQL_MIS_New* N = new SQL_MIS_New("MAIN");
	N->teachN();

	CardBase* C = new CardBase();
	C->teachC();

	Replay* R = new Replay();
	R->teachR();

	PMV_to_SQL* P = new PMV_to_SQL();
	//P->teachP();

	MISD("--> MAINSCHEIFE");
	
	while (Bro->bAktive)
	{
//		std::cout << "Message: ";
		std::cin >> buf;
		
		if (string(buf) == "x")Bro->bAktive = false;
		if (string(buf) == "1")Bro->C->WEBtoSQL(false);
		if (string(buf) == "2")Bro->C->WEBtoSQL(true);				
		if (string(buf) == "3")Bro->C->Imager(1394);
		if (string(buf) == "3")Bro->C->Imager(1395);
		if (string(buf) == "9")Bro->C->Imager(0);

		if (string(buf) == "BULK")
		{
			stringstream ssCMD;
			path p = PMV_path;
			recursive_directory_iterator it = recursive_directory_iterator(p);

			while (it != recursive_directory_iterator{})
			{
				//MISD(it->path().filename().string());
				
				if (!(it->path().extension() == ".pmv" ||it->path().extension() == ".PMV"))
				{
					it++;
					continue;
				}

				R = new Replay();
				if (R->LoadPMV(it->path().filename().string()))
				{
					if (P->UseThisPMV(R))
						//if (P->NewMasterData())
							MISD("DONE");

					ssCMD.str("");
					ssCMD << "move \"" << PMV_path << it->path().filename().string() << "\" \"" << PMV_Arch << it->path().filename().string() << "\"";
					system(ssCMD.str().c_str());
				}
				
				it++;				
			}
			break;
		}
		/*
		Bro->C->Imager(1033);
		Bro->C->Imager(1585);
		Bro->C->Imager(1034);
		Bro->C->Imager(1021);
		Bro->C->Imager(1607);
		Bro->C->Imager(1035);
		Bro->C->Imager(1029);
		Bro->C->Imager(1032);
		Bro->C->Imager(1274);
		Bro->C->Imager(1277);
		Bro->C->Imager(1030);
		Bro->C->Imager(1276);
		Bro->C->Imager(1639);
		Bro->C->Imager(1642);
		Bro->C->Imager(1031);
		Bro->C->Imager(1275);
		*/
		R = new Replay();
		if (R->LoadPMV(string(buf) +  ".pmv"))
			if (P->UseThisPMV(R))
				//if (P->NewMasterData())
					MISD("DONE");

		//P->ECHO();

		

		/*
		R = new Replay();
		R->LoadPMV("CC.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("CCC.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("HIKO.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("X.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("Y.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("Z.pmv");
		R->ECHO();
		*/

		//Bro->C->IMGtoQSL(1670,Tmp_path + "TMP.png");
		/*
		R->LoadPMV("20220423_204949_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220425_213012_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220428_193017_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220428_193923_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220428_195616_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220501_181348_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220510_220726_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220510_222428_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220512_191011_GeneratedMap.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220512_233431_GeneratedMap.pmv");
		R->ECHO();
		*/
		/*
		R = new Replay();
		R->LoadPMV("20220212_233331_11304_PvE_04p_Titans.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220311_215616_11304_PvE_04p_Titans.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220413_201806_11304_PvE_04p_Titans.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("20220417_215809_11304_PvE_04p_Titans.pmv");
		R->ECHO();
		*/
		/*
		R->LoadPMV("1P_D1_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D2_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D3_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D4_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D5_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D6_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D7_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D8_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D9_MM1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D0_MM1.pmv");
		R->ECHO();
		*/

		/*

		R = new Replay();
		R->LoadPMV("1P_D1_1.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D1_2.pmv");
		R->ECHO();
		R = new Replay();
		R->LoadPMV("1P_D1_3.pmv");
		R->ECHO();
		*/


		//R->LoadPMV("y.pmv");
		//R->LoadPMV("X.pmv");
		//R->LoadPMV("C.pmv");
		//R->LoadPMV("HIKO.pmv");


		
	}

	MISD("<-- MAINSCHEIFE");
    return 0;
}

