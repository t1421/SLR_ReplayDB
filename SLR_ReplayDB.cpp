// SLR_ReplayDB.cpp : Definiert den Einstiegspunkt f?r die Konsolenanwendung.
//

#include "prototypes.h"

#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "LOAD.h" 
#include "Manager.h" 
#include "Replay.h" 
#include "PMV_to_SQL.h" 
#include "Imager.h" 



bool Checker(string &check, string name);

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	int iArcCout = 1;
	string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayDB",true,true,false);
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
	Imager* I = new Imager();
	

	MISD("--> MAINSCHEIFE");
	
	while (Bro->bAktive)
	{
		if (argc > 1 && argc > iArcCout)
		{
			
			sbuf = argv[iArcCout];
			iArcCout++;
			std::cout << "ARG:" << sbuf << endl;
		}
		else
		{
			std::cin >> buf;
			sbuf = buf;
		}

		if (string(buf) == "x")Bro->bAktive = false;
		if (string(buf) == "1")Bro->C->WEBtoSQL(false);
		if (string(buf) == "2")Bro->C->WEBtoSQL(true);				
		if (string(buf) == "3")Bro->C->Imager(1394);
		if (string(buf) == "3")Bro->C->Imager(1395);
		if (string(buf) == "9")Bro->C->Imager(0);

		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");
			printf("C;full              | Updates all cards in MYSQL\n");
			printf("C;update            | Adds neu cards to MYSQL\n");
			printf("C;imager;0          | Loads all images from WIKI in MYSQL\n");
			printf("C;imager;[ID]       | Loads images for CARDID from WIKI in MYSQL\n");
			printf("C;download;[ID]     | Loads images for MYSQL\n");
			printf("####################|###########################################\n\n");
			printf("####################|###########################################\n");
			printf("R;new               | new Replay object\n");
			printf("R;open;[FILE]       | Opens FILE from Replay dir\n");
			printf("R;echo;head         | Outputs Headerdata\n");
			printf("R;echo;allied       | Outputs Allied Table\n");
			printf("R;echo;team         | Outputs Team Table\n");
			printf("R;echo;player       | Outputs Players\n");
			printf("R;echo;deck         | Outputs Deck of Replay recorder\n");
			printf("R;echo;action;*     | Outputs all Actions\n");
			printf("R;echo;action;[ID]  | Outputs Actions with ID\n");
			printf("####################|###########################################\n\n");
			printf("####################|###########################################\n");
			printf("P;new               | new MYSQL Uploard object\n");
			printf("P;open              | loads R into P\n");
			printf("P;upload            | save R into SQL\n");
			printf("P;download;[GameID] | loads R from SQL\n");
			printf("P;dublette          | Checks if Games is alreade in MYSQL\n");
			printf("####################|###########################################\n\n");
			printf("####################|###########################################\n");
			printf("I;new               | new Imager Object\n");
			printf("I;open              | Use the current P Pointer\n");
			printf("I;makeIMG           | Creates the Image\n");
			printf("I;makeMOV           | Creates Mov from image\n");
			printf("I;echo              | outputs paths\n");
			printf("####################|###########################################\n\n");
		}

		if (Checker(sbuf, "C"))
		{
			if (Checker(sbuf, "update"))C->WEBtoSQL(false);
			if (Checker(sbuf, "full"))C->WEBtoSQL(true);
			if (Checker(sbuf, "imager"))C->Imager(atoi(sbuf.c_str()));
			if (Checker(sbuf, "download"))C->DownloadPNG(atoi(sbuf.c_str()));
		}		

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

				if (Checker(sbuf, "action"))
				{
					R->EchoAction(sbuf);
				}
			}
		}

		if (Checker(sbuf, "P"))
		{
			if (Checker(sbuf, "new"))P = new PMV_to_SQL();

			if (Checker(sbuf, "open"))
			{				
				P->UseThisSQL(N);				
				P->UseThisPMV(R);
			}

			if (Checker(sbuf, "upload"))
			{
				P->Upload();
			}

			if (Checker(sbuf, "download"))
			{
				R = new Replay();
				P->UseThisSQL(N);
				P->UseThisPMV(R);
				P->Download(sbuf.c_str());
			}

			if (Checker(sbuf, "dublette"))
			{
				MISD("Return: " + P->DublettenCheck());
			}
		}

		if (Checker(sbuf, "I"))
		{
			if (Checker(sbuf, "new"))I = new Imager();
			if (Checker(sbuf, "open"))I->UseThisPMV(R);
			if (Checker(sbuf, "makeIMG"))I->MakeIMG();
			if (Checker(sbuf, "makeMOV"))I->MakeMOV();
			if (Checker(sbuf, "echo"))I->Echo();
		}

		if (Checker(sbuf, "exit"))Bro->bAktive = false;
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