//#define DF_Debug

#include "prototypes.h"

#include "DEBUG.h"
#include "Thread_MIS.h" 
#include "Replay.h" 
#include "Reader.h" 
#include "Broker.h"

#ifdef BrokerParser

#endif

#ifdef BrokerWeb
#include "WEB_Main.h"
#include "WEB_CONTAINER.h"
#include "WEB_MA.h"
#endif

#ifdef BrokerNormal
#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "Imager.h"
#include "PMV_to_SQL.h"
#include "LOAD.h"
#include "Manager.h"
#endif


broker::broker()
{
	bAktive = true;

	DEBUG::learnBro(this);
	Replay::learnBro(this);
	Reader::learnBro(this);

#ifdef BrokerWeb
	WEB_Main::learnBro(this);
	MISCONTAINER::learnBro(this);
	WEB_MA::learnBro(this);
#endif
#ifdef BrokerParser

#endif
#ifdef BrokerNormal
	SQL_MIS_New::learnBro(this);
	CardBase::learnBro(this);
	PMV_to_SQL::learnBro(this);
	Imager::learnBro(this);
	LOAD::learnBro(this);
	Manager::learnBro(this);	
	Thread_MIS::learnBro(this);
#endif
	
	
	
	Bro = this;

	B = NULL;
	N = NULL;
	C = NULL;	
	M = NULL;
	L = NULL;
	I = NULL;
	W = NULL;

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

bool broker::C_DownloadPNG(unsigned short CardID)
{
	return C->DownloadPNG(CardID);
}

string broker::L_getSQL_Server()
{
	return L->sSQL_Server;
}
string broker::L_getSQL_User()
{
	return L->sSQL_User;
}
string broker::L_getSQL_PW()
{
	return L->sSQL_PW;
}
string broker::L_getSQL_DB()
{
	return L->sSQL_DB;
}

string broker::L_getPMV_PATH()
{
	return L->sPMV_PATH;
}
string broker::L_getPMV_AUTO_PATH()
{
	return L->sPMV_AUTO_PATH;
}
string broker::L_getPMV_ARCH_PATH()
{
	return L->sPMV_ARCH_PATH;
}
string broker::L_getTMP_PATH()
{
	return L->sTMP_PATH;
}

string broker::L_getFFMPEG()
{
	return L->sFFMPEG;
}

#endif