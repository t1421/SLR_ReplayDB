#define DF_Debug
#include "..\incl\Broker.h"

#include "..\incl\DEBUG.h"

#include "..\incl\Replay.h" 
#include "..\incl\Reader.h" 

#if defined BrokerNormal || defined BrokerWeb
#include "..\incl\LOAD.h"
#include "..\incl\Thread_MIS.h" 
#endif


#ifdef BrokerWeb

#include "..\incl\WEB\WEB_Main.h"
#include "..\incl\WEB\WEB_CONTAINER.h"
#ifdef BOT1
#include "..\incl\WEB\WEB_MA.h"
#include "..\incl\WEB\WEB_MAA.h"
#endif
#ifdef BOT2
#include "..\incl\WEB\WEB_MB.h"
#include "..\incl\WEB\WEB_MBA.h"
#endif
#include "..\incl\WEB\WEB_MC.h"
#include "..\incl\WEB\WEB_MCA.h"
#include "..\incl\WEB\WEB_MD.h"
#include "..\incl\WEB\WEB_Rank.h"
#include "..\incl\WEB\WEB_Toolbar.h"
#include "..\incl\WEB\WEB_Replay.h"
#include "..\incl\MIS_Rank.h"

#include "..\incl\WEB\WEB_Analyser.h"
#include "..\incl\WEB\WEB_Analyser_Head.h"
#include "..\incl\WEB\WEB_Analyser_Deck.h"
#include "..\incl\WEB\WEB_Analyser_Acti.h"

#include "..\incl\CardBaseSMJ.h" 

#include <algorithm>
#include <iterator>
#endif

#ifdef BrokerNormal
#include "..\incl\CardBase.h" 
#endif

#ifndef noSQL
#include "..\incl\SQL_MIS_New.h" 
#include "..\incl\PMV_to_SQL.h"
#endif

#ifndef noManager
#include "..\incl\Manager.h"
#endif

#ifndef noImager
#include "..\incl\Imager.h"
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
#ifdef BOT1
	WEB_MA::learnBro(this);
	WEB_MAA::learnBro(this);
#endif
#ifdef BOT2
	WEB_MB::learnBro(this);
	WEB_MBA::learnBro(this);
#endif
	WEB_MC::learnBro(this);
	WEB_MCA::learnBro(this);
	WEB_MD::learnBro(this);
	WEB_Rank::learnBro(this);
	WEB_Toolbar::learnBro(this);
	WEB_Replay::learnBro(this);
	MIS_Rank::learnBro(this);

	WEB_Analyser::learnBro(this);
	WEB_Analyser_Head::learnBro(this);
	WEB_Analyser_Deck::learnBro(this);
	WEB_Analyser_Acti::learnBro(this);

	CardBaseSMJ::learnBro(this);
		
	W = NULL;
	J = NULL;
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

#ifdef BrokerWeb
unsigned char broker::C_GetActionOrbForCardID(unsigned short CardID)
{
	return J->GetActionOrbForCardID(CardID);
}
#endif

#if defined BrokerParser 
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
std::string broker::L_getSMJPIC_PATH()
{
	return L->sSMJPIC_PATH;
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

std::string broker::J_GetImage(unsigned short _CardID, unsigned char _Upgrade, unsigned char _Charges, unsigned long _Count)
{
	if (_Count>0)return J->GetImage(_CardID, _Upgrade, _Charges);
	else return J->GetSWImage(_CardID, _Upgrade, _Charges);
	
}
unsigned char broker::J_SwitchCharges(unsigned short _CardID, unsigned char _IstCharges)
{
	return J->SwitchCharges(_CardID,_IstCharges);
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