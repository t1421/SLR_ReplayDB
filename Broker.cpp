//#define DF_Debug
#include "Broker.h"

#include "DEBUG.h"
#include "Thread_MIS.h" 
#include "Replay.h" 
#include "Reader.h" 

#if defined BrokerNormal || defined BrokerWeb
#include "LOAD.h"
#endif

#ifdef BrokerParser

#endif

#ifdef BrokerWeb

#include "WEB_Main.h"
#include "WEB_CONTAINER.h"
#include "WEB_MA.h"
#include "WEB_MB.h"
#include "WEB_MBA.h"
#include "WEB_MC.h"
#include "WEB_MCA.h"
#include "WEB_MCB.h"
#include "WEB_Toolbar.h"
#include "WEB_Replay.h"
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
	LOAD::learnBro(this);
	L = NULL;
#endif

#ifdef BrokerWeb
	WEB_Main::learnBro(this);
	MISCONTAINER::learnBro(this);
	WEB_MA::learnBro(this);
	WEB_MB::learnBro(this);
	WEB_MBA::learnBro(this);
	WEB_MC::learnBro(this);
	WEB_MCA::learnBro(this);
	WEB_MCB::learnBro(this);
	WEB_Toolbar::learnBro(this);
	WEB_Replay::learnBro(this);
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

#endif

void broker::B_StatusNew(std::string Fun, std::string Wert)
{
	B->StatusNew(Fun, Wert);
}

void broker::B_StatusE(std::string Modul, std::string Funktion, std::string Wert)
{
	B->StatusE(Modul, Funktion, Wert);
}