//#define DF_Debug

#include "stdafx.h"

#include "DEBUG.h"
#include "SQL_MIS_New.h" 
#include "CardBase.h" 
#include "Replay.h" 
#include "Reader.h" 
#include "PMV_to_SQL.h"
#include "Broker.h"

broker::broker()
{
	bAktive = true;

	DEBUG::learnBro(this);
	SQL_MIS_New::learnBro(this);
	CardBase::learnBro(this);
	Replay::learnBro(this);
	Reader::learnBro(this);
	PMV_to_SQL::learnBro(this);
	
	Bro = this;

	B = NULL;
	N = NULL;
	C = NULL;	
	R = NULL;
	//P = NULL;
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
