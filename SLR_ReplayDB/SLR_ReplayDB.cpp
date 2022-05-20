// SLR_ReplayDB.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "LOAD.h" 
#include "Manager.h" 
#include "Replay.h" 
#include "PMV_to_SQL.h" 



bool Checker(string &check, string name);

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayDB");
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();

	SQL_MIS_New* N = new SQL_MIS_New("MAIN");
	N->teachN();

	CardBase* C = new CardBase();
	C->teachC();

	Manager* M = new Manager();
	M->teachM();
	M->Start_Thread();
	
	Replay* R = new Replay();	
	PMV_to_SQL* P = new PMV_to_SQL();
	

	MISD("--> MAINSCHEIFE");
	
	while (Bro->bAktive)
	{
//		std::cout << "Message: ";
		std::cin >> buf;
		
		sbuf = buf;

		if (string(buf) == "x")Bro->bAktive = false;
		if (string(buf) == "1")Bro->C->WEBtoSQL(false);
		if (string(buf) == "2")Bro->C->WEBtoSQL(true);				
		if (string(buf) == "3")Bro->C->Imager(1394);
		if (string(buf) == "3")Bro->C->Imager(1395);
		if (string(buf) == "9")Bro->C->Imager(0);
		
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

		if (Checker(sbuf, "R"))
		{
			if (Checker(sbuf, "new"))R = new Replay();
			
			if (Checker(sbuf, "open"))
			{
				if (R->LoadPMV(Bro->L_getPMV_PATH() + sbuf + ".pmv"))MISD("All fine");
			}

			if (Checker(sbuf, "echo"))
			{
				if (Checker(sbuf, "head"))R->EchoHead();
				if (Checker(sbuf, "allied"))R->EchoAllied();
				if (Checker(sbuf, "team"))R->EchoTeam();
				if (Checker(sbuf, "player"))R->EchoPlayer();
				if (Checker(sbuf, "deck"))R->EchoPlayerDecks();
			}
		}

		

		/*
		if (R->LoadPMV(string(buf) +  ".pmv"))
			if (P->UseThisPMV(R))
				//if (P->NewMasterData())
					MISD("DONE");
*/
		
	}

	M->Stop_Thread();

	MISD("<-- MAINSCHEIFE");
    return 0;
}



bool Checker(string &check, string name)
{
	if (check.substr(0, check.find(";")) == name)
	{
		check.erase(0, check.find(";") + 1);
		return true;
	}
	else
	{
		return false;
	}
}