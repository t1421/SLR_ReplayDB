#define DF_Debug
#include "Broker.h"

#include "DEBUG.h"

#include "Replay.h" 
#include "Reader.h" 

#if defined BrokerNormal || defined BrokerWeb
#include "LOAD.h"
#include "Thread_MIS.h" 
#endif


#ifdef BrokerWeb

#include "WEB_Main.h"
#include "WEB_CONTAINER.h"
#include "WEB_MA.h"
#include "WEB_MAA.h"
#include "WEB_MB.h"
#include "WEB_MBA.h"
#include "WEB_MC.h"
#include "WEB_MCA.h"
#include "WEB_Rank.h"
#include "WEB_Toolbar.h"
#include "WEB_Replay.h"
#include "MIS_Rank.h"

#include <algorithm>
#include <iterator>
#endif

#ifdef BrokerNormal
#include "CardBase.h" 
#endif

#ifndef noSQL
#include "SQL_MIS_New.h" 
#include "PMV_to_SQL.h"
#endif

#ifndef noManager
#include "Manager.h"
#endif

#ifndef noImager
#include "Imager.h"
#endif
broker::broker()
{
	bAktive = true;
	Bro = this;

	DEBUG::learnBro(this);
	B = NULL;	
	Replay::learnBro(this);
	Reader::learnBro(this);

#if defined BrokerNormal || defined BrokerWeb
	Thread_MIS::learnBro(this);
	LOAD::learnBro(this);
	L = NULL;
#endif

#ifdef BrokerWeb
	WEB_Main::learnBro(this);
	MISCONTAINER::learnBro(this);
	WEB_MA::learnBro(this);
	WEB_MAA::learnBro(this);
	WEB_MB::learnBro(this);
	WEB_MBA::learnBro(this);
	WEB_MC::learnBro(this);
	WEB_MCA::learnBro(this);
	WEB_Rank::learnBro(this);
	WEB_Toolbar::learnBro(this);
	WEB_Replay::learnBro(this);
	MIS_Rank::learnBro(this);
	
	W = NULL;
#endif


#ifdef BrokerNormal	
	CardBase::learnBro(this);	
	Thread_MIS::learnBro(this);
	C = NULL;
#endif

#ifndef noSQL
SQL_MIS_New::learnBro(this);
PMV_to_SQL::learnBro(this);
N = NULL;
#endif

#ifndef noManager
	Manager::learnBro(this);	
	M = NULL;
#endif
	
#ifndef noImager	
Imager::learnBro(this);	
	I = NULL;
#endif	
	

	

}

#ifdef BrokerWeb
void broker::INIT()
{	
	for (int i = 0; i <= BOTXLIST; i++)A[i] = new MIS_Rank(i,L->BOTRankMode[i]);

	std::ifstream ifFile;
	std::string line;
	
	ifFile.open(L_getRANK_PATH() + "Names.csv", std::ios::binary);	
	if (!ifFile.good())
	{
		return;
	}
	
	std::copy(std::istream_iterator<std::string>(ifFile),
		std::istream_iterator<std::string>(),
		std::back_inserter(FreeNames));
	
	ifFile.close();
	
}

int broker::AddRankPlayer(unsigned int iRANK, unsigned long long PMVPlayerID, unsigned long Playtime, std::string &sRankName)
{
	return A[iRANK]->AddPlayer(PMVPlayerID, Playtime, sRankName);
}

std::string broker::getName()
{
	if (FreeNames.size() == 0)
	{
		return "ERROR###1";
	}
	mtx.lock();
	std::string sTemp = FreeNames.at(0);
	FreeNames.erase(FreeNames.begin());
	saveName();
	mtx.unlock();

	return sTemp;
}

void broker::saveName()
{
	printf("save Name\n");
	std::ofstream ofFile;	
	ofFile.open(L_getRANK_PATH() + "Names.csv", std::ios::binary);
	if (ofFile.good())
	{
		printf("FILE OK\n");
		for (unsigned int i = 0; i < FreeNames.size(); i++)
		{
	 //printf("%i\n",i);
			ofFile << FreeNames[i] << std::endl;
		}
		ofFile.close();
	}
	else printf("XXX\n");
	
}
#endif

broker::~broker()
{
	MISS;
	//tFadeThread.join();
	MISE;
}


#if defined BrokerParser || defined BrokerWeb
unsigned char broker::C_GetActionOrbForCardID(unsigned short CardID)
{
	return 0;
}
#endif

#ifdef BrokerNormal
unsigned char broker::C_GetActionOrbForCardID(unsigned short CardID)
{
	return C->GetActionOrbForCardID(CardID);
}
#endif
#ifdef CardBaseUpdater
bool broker::C_DownloadPNG(unsigned short CardID)
{
	return C->DownloadPNG(CardID);
}
#endif

#if defined BrokerNormal || defined BrokerWeb
std::string broker::L_getSQL_Server()
{
	return L->sSQL_Server;
}
std::string broker::L_getSQL_User()
{
	return L->sSQL_User;
}
std::string broker::L_getSQL_PW()
{
	return L->sSQL_PW;
}
std::string broker::L_getSQL_DB()
{
	return L->sSQL_DB;
}

std::string broker::L_getPMV_PATH()
{
	return L->sPMV_PATH;
}
std::string broker::L_getPMV_AUTO_PATH()
{
	return L->sPMV_AUTO_PATH;
}
std::string broker::L_getPMV_ARCH_PATH()
{
	return L->sPMV_ARCH_PATH;
}
std::string broker::L_getTMP_PATH()
{
	return L->sTMP_PATH;
}

std::string broker::L_getFFMPEG()
{
	return L->sFFMPEG;
}

std::string broker::L_getRANK_PATH()
{
	return L->sRANK_PATH;	
}

int broker::L_getBOTRankMode(int _BOT)
{
	return L->BOTRankMode[_BOT];
}



#endif

void broker::B_StatusNew(std::string Fun, std::string Wert)
{
	B->StatusNew(Fun, Wert);
}

void broker::B_StatusE(std::string Modul, std::string Funktion, std::string Wert)
{
	B->StatusE(Modul, Funktion, Wert);
}