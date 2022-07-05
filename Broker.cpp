//#define DF_Debug

#include "prototypes.h"

#include "DEBUG.h"
#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "Replay.h" 
#include "Reader.h" 
#include "Imager.h"
#include "PMV_to_SQL.h"
#include "LOAD.h"
#include "Manager.h"
#include "Broker.h"
#include "Thread_MIS.h" 

broker::broker()
{
	bAktive = true;

	DEBUG::learnBro(this);
	SQL_MIS_New::learnBro(this);
	CardBase::learnBro(this);
	Replay::learnBro(this);
	Reader::learnBro(this);
	PMV_to_SQL::learnBro(this);
	Imager::learnBro(this);
	LOAD::learnBro(this);
	Manager::learnBro(this);
	Thread_MIS::learnBro(this);
	
	Bro = this;

	B = NULL;
	N = NULL;
	C = NULL;	
	M = NULL;
	L = NULL;
	I = NULL;

}

broker::~broker()
{
	MISS;
	//tFadeThread.join();
	MISE;
}

unsigned char broker::C_GetActionOrbForCardID(unsigned short CardID)
{
	return C->GetActionOrbForCardID(CardID);
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