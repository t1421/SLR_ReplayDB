// SLR_ReplayParserWeb.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\WEB\WEB_Main.h"
#include "incl\LOAD.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Utility.h" 


int main(int argc, char **argv)
{
	char buf[1024] = { '0' };
	std::string sbuf;

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayParserWeb",true,true,false);
	B->teachB();

	LOAD* L = new LOAD();
	L->teachL();
	L->StartUp();

	MISD(Bro->L_getRANK_PATH());
	
	CardBaseSMJ* J = new CardBaseSMJ();
	J->teachJ();
	J->Init();

	WEB_Main* W = new WEB_Main();
	W->teachW();
	W->Init_W();
	W->Start_Thread();

	Bro->INIT();

#ifdef MIS_Count
	L->Load_Count();
#endif

	while (Bro->bAktive)
	{
		std::cin >> buf;
		sbuf = buf;		
		if (Checker(sbuf, "exit"))Bro->bAktive = false;
		if (Checker(sbuf, "x"))Bro->bAktive = false;

		if (Checker(sbuf, "?"))
		{
			printf("####################|###########################################\n");
			printf("J;new               | New Istance\n");
			printf("J;init              | calls init\n");
			printf("J;echo;[ID]         | print Card data\n");
			printf("J;BC                | Big Color\n");
			printf("J;BS                | Big SW\n");
			printf("J;SC                | small Color\n");
			printf("J;SS                | small SW\n");
			printf("J;IC                | ImgOnly Color\n");
			printf("J;IS                | ImgOnly SW\n");
			printf("J;ALL_Big           | Downloads all Cards BIG \n");
			printf("J;ALL_BigSW         | Downloads all Cards BIG in SW \n");
			printf("J;ALL_Small         | Downloads all Cards SMALL \n");
			printf("J;ALL_ImgOnly       | Downloads all Cards IMG ONLY \n");
			printf("####################|###########################################\n\n");
		}
		if (Checker(sbuf, "J"))
		{
			if (Checker(sbuf, "new")) J = new CardBaseSMJ();
			if (Checker(sbuf, "init")) J->Init();
			if (Checker(sbuf, "echo"))J->EchoCard(sbuf);
			//if (Checker(sbuf, "imager"))J->DownloadImage(1348,1,1,true);
			if (Checker(sbuf, "BC"))J->GetImage(1348, 2, 1, Big ,false);
			if (Checker(sbuf, "BS"))J->GetImage(290, 2, 1, Big, true);
			if (Checker(sbuf, "SC"))J->GetImage(1348, 2, 1, Small, false);
			if (Checker(sbuf, "SS"))J->GetImage(290, 2, 1, Small, true);
			if (Checker(sbuf, "IC"))J->GetImage(1348, 2, 1, ImgOnly, false);
			if (Checker(sbuf, "IS"))J->GetImage(290, 2, 1, ImgOnly, true);
			if (Checker(sbuf, "ALL_Big"))J->AllIMGBig();
			if (Checker(sbuf, "ALL_BigSW"))J->AllIMGBigSW();
			if (Checker(sbuf, "ALL_Small"))J->AllIMGSmall();
			if (Checker(sbuf, "ALL_ImgOnly"))J->AllIMGImgOnly();
			

		}

	}

	W->Stop_Thread();
    return 0;
}

