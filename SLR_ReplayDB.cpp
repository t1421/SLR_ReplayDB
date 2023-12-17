// SLR_ReplayDB.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "incl\Broker.h" 
#include "incl\DEBUG.h" 
//#include "incl\CardBase.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\LOAD.h" 
#include "incl\Replay.h" 


#include "incl\Utility.h" 

#ifndef noImager
#include "incl\Imager.h" 
#endif
#ifndef noManager
#include "incl\Manager.h" 
#endif

#ifndef noSQL
#include "incl\SQL_MIS_New.h" 
#include "incl\PMV_to_SQL.h" 
#endif

#include <iostream>

int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	int iArcCout = 1;
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayDB",true,true,false);
	B->teachB();

	Replay* R = new Replay();	

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();

#ifndef noSQL
	PMV_to_SQL* P = new PMV_to_SQL();
	SQL_MIS_New* N = new SQL_MIS_New("MAIN");
	N->teachN();
#endif

	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();
	
#ifndef noManager
	Manager* M = new Manager();
	M->teachM();
	M->Start_Thread();
#endif	


	
#ifndef noImager
	Imager* I = new Imager();
#endif
	

	MISD("--> MAINSCHEIFE");
	
	while (Bro->bAktive)
	{
		if (argc > 1 && argc > iArcCout)
		{
			
			sbuf = argv[iArcCout];
			iArcCout++;
			std::cout << "ARG:" << sbuf << std::endl;
		}
		else
		{
			std::cin >> buf;
			sbuf = buf;
		}

		if (Checker(sbuf, "?"))
		{

			/*
			printf("####################|###########################################\n");
			printf("C;full              | Updates all cards in MYSQL\n");
			printf("C;update            | Adds neu cards to MYSQL\n");
			printf("C;imager;0          | Loads all images from WIKI in MYSQL\n");
			printf("C;IMGtoQSL;[ID]       | Loads images for CARDID from WIKI in MYSQL\n");
			printf("C;upload;[ID]       | Uploads images for CARDID from TempDir in MYSQL\n");
			printf("C;download;[ID]     | Loads images for MYSQL\n");
			printf("####################|###########################################\n\n");
			*/
			printf("####################|###########################################\n");
			printf("J;full              | Updates all cards in MYSQL\n");
			printf("J;update            | Adds neu cards to MYSQL\n");
			printf("J;IMGtoSQL;[ID]     | Loads images for CARDID from SMJ in MYSQL\n");
			printf("J;imager            | Loads all images from SMJ in MYSQL\n");
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
			#ifndef noSQL
			printf("####################|###########################################\n");
			printf("P;new               | new MYSQL Uploard object\n");
			printf("P;open              | loads R into P\n");
			printf("P;upload            | save R into SQL\n");
			printf("P;download;[GameID] | loads R from SQL\n");
			printf("P;dublette          | Checks if Games is alreade in MYSQL\n");
			printf("####################|###########################################\n\n");
			#endif
			#ifndef noImager
			printf("####################|###########################################\n");
			printf("I;new               | new Imager Object\n");
			printf("I;open              | Use the current P Pointer\n");
			printf("I;makeIMG           | Creates the Image\n");
			printf("I;makeMOV           | Creates Mov from image\n");
			printf("I;echo              | outputs paths\n");
			printf("####################|###########################################\n\n");
			#endif
		}
		
	
		if (Checker(sbuf, "J"))
		{
			if (Checker(sbuf, "update"))J->SMJtoSQL(false);
			if (Checker(sbuf, "full"))J->SMJtoSQL(true);
			if (Checker(sbuf, "IMGtoSQL"))J->IMGtoQSL(atoi(sbuf.c_str()));
			if (Checker(sbuf, "imager"))J->Imager();
			/*if (Checker(sbuf, "upload"))C->UploadFromTemp(atoi(sbuf.c_str()));
			if (Checker(sbuf, "download"))C->DownloadPNG(atoi(sbuf.c_str()));
			*/
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
#ifndef noSQL
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
				printf("%s\n", P->DublettenCheck().c_str());
				//MISD("Return: " + P->DublettenCheck());
			}
		}
#endif		
#ifndef noImager
		if (Checker(sbuf, "I"))
		{
			if (Checker(sbuf, "new"))I = new Imager();
			if (Checker(sbuf, "open"))I->UseThisPMV(R);
			if (Checker(sbuf, "makeIMG"))I->MakeIMG();
			if (Checker(sbuf, "makeMOV"))I->MakeMOV();
			if (Checker(sbuf, "echo"))I->Echo();
		}
#endif
		if (Checker(sbuf, "exit"))Bro->bAktive = false;
	}
#ifndef noManager
	M->Stop_Thread();
#endif

	MISD("<-- MAINSCHEIFE");
    return 0;
}


