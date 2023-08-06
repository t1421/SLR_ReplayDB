//#define DF_Debug
#include "..\incl\Broker.h"

#include "..\incl\DEBUG.h"

#if defined BrokerNormal || defined BrokerWeb  
#include "..\incl\Replay.h" 
#include "..\incl\Reader.h" 
#endif

#if defined BrokerTome || defined BrokerNormal || defined BrokerWeb
#include "..\incl\LOAD.h"
#include "..\incl\Thread_MIS.h" 
#endif


#if defined BrokerTome || defined BrokerWeb
#include "..\incl\Utility.h"

#include "..\incl\WEB\WEB_Main.h"
#include "..\incl\WEB\WEB_Server.h"
#include "..\incl\WEB\WEB_Toolbar.h"
#endif

#if defined BrokerWeb
#include "..\incl\WEB_Analyser\WEB_CONTAINER_Analyser.h"

#include "..\incl\WEB_Analyser\WEB_ME.h"
#include "..\incl\WEB_Analyser\WEB_MEA.h"
#include "..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\incl\MIS_Rank.h"

#include "..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\incl\WEB_Analyser\WEB_Analyser_Head.h"
#include "..\incl\WEB_Analyser\WEB_Analyser_Deck.h"
#include "..\incl\WEB_Analyser\WEB_Analyser_Acti.h"
#endif

#if defined BrokerTome
#include "..\incl\WEB_Tome\WEB_CONTAINER_Tome.h"
#include "..\incl\WEB_Tome\WEB_Tome_Admin.h"
#include "..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\incl\WEB_Tome\WEB_Tome_Logout.h"
#include "..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\incl\WEB_Tome\WEB_Tome_Public.h"
#endif

#ifndef noSMJ
#include "..\incl\CardBaseSMJ.h" 
#include <algorithm>
#include <iterator>
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
#if defined BrokerNormal || defined BrokerWeb
	Replay::learnBro(this);
	Reader::learnBro(this);
#endif

#if defined BrokerNormal || defined BrokerWeb || defined BrokerTome 
	Thread_MIS::learnBro(this);
	LOAD::learnBro(this);
	L = NULL;
#endif

#if defined BrokerTome || defined BrokerWeb
	WEB_Main::learnBro(this);
	WEB_Server::learnBro(this);
	WEB_Toolbar::learnBro(this);
	
	W = NULL;
#endif


#if defined BrokerWeb
	WEB_Container::learnBro(this);

	WEB_ME::learnBro(this);
	WEB_MEA::learnBro(this);
	WEB_Rank::learnBro(this);	
	MIS_Rank::learnBro(this);

	WEB_Analyser::learnBro(this);
	WEB_Analyser_Head::learnBro(this);
	WEB_Analyser_Deck::learnBro(this);
	WEB_Analyser_Acti::learnBro(this);
#endif

#if defined BrokerTome
	WEB_Container_Tome::learnBro(this);
	WEB_Tome_Admin::learnBro(this);
	WEB_Tome_Login::learnBro(this);
	WEB_Tome_Logout::learnBro(this);
	WEB_Tome_Player::learnBro(this);
	WEB_Tome_Public::learnBro(this);
#endif

#ifndef noSMJ
	CardBaseSMJ::learnBro(this);
	J = NULL;
#endif

#ifdef BrokerNormal	
	Thread_MIS::learnBro(this);
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

#if defined BrokerWeb
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


	ifFile.open(L_getRANK_PATH() + "Teams.csv", std::ios::binary);
	if (ifFile.good())
	{
		while (getline(ifFile, line))		
			TeamNames.push_back(std::make_pair(entry(line, 0), entry(line, 1)));;
		
		ifFile.close();
	}
}

int broker::AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps])
{
	return A[iRANK]->AddPlayer(_ID, _ReplayID, _Stamps);
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

void broker::saveTeams()
{
	printf("save Teams\n");
	std::ofstream ofFile;
	ofFile.open(L_getRANK_PATH() + "Teams.csv", std::ios::binary);
	if (ofFile.good())
	{
		printf("FILE OK\n");
		for (unsigned int i = 0; i < TeamNames.size(); i++)
		{
			ofFile << TeamNames[i].first << ";" << TeamNames[i].second << std::endl;
		}
		ofFile.close();
	}
	else printf("XXX\n");
}

std::string broker::GetTeamName(std::string sTeamID)
{
	std::string sName;

	for (unsigned int i = 0; i < TeamNames.size(); i++)
		if (TeamNames[i].first == sTeamID)return TeamNames[i].second;
	
	sName = Bro->getName();
	TeamNames.push_back(std::make_pair(sTeamID, sName));
	saveTeams();

	return sName;
}

#endif

broker::~broker()
{
	//MISS;
	//tFadeThread.join();
	//MISE;
}

#ifndef noSMJ
unsigned char broker::J_GetActionOrbForCardID(unsigned short CardID)
{
	return J->GetActionOrbForCardID(CardID);
}

std::string broker::J_GetImgOnly(unsigned short CardID)
{
	return J->GetImage(CardID,0,0, ImgOnly,false);
}
#endif


#if defined BrokerParser 
unsigned char broker::J_GetActionOrbForCardID(unsigned short CardID)
{
	return 0;
}
#endif

#if defined BrokerNormal || defined BrokerWeb || defined BrokerTome 
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
std::string broker::L_getSMJPICSMALL_PATH()
{
	return L->sSMJPICSMALL_PATH;
}
std::string broker::L_getSMJIMG_PATH()
{
	return L->sSMJIMG_PATH;
}

std::string broker::L_getFFMPEG()
{
	return L->sFFMPEG;
}

std::string broker::L_getRANK_PATH()
{
	return L->sRANK_PATH;	
}

std::string broker::L_getTOME_SAVE_PATH()
{
	return L->sTOME_SAVE_PATH;
}

int broker::L_getBOTRankMode(int _BOT)
{
	return L->BOTRankMode[_BOT];
}



#ifndef noSMJ
std::string broker::J_GetImage(unsigned short _CardID, unsigned char _Upgrade, unsigned char _Charges, unsigned long _Count, bool bSmall)
{
	return J->GetImage(_CardID, _Upgrade, _Charges, Big, _Count==0);
	
}
unsigned char broker::J_SwitchCharges(unsigned short _CardID, unsigned char _IstCharges)
{
	return J->SwitchCharges(_CardID,_IstCharges);
}

SMJCard* broker::J_GetSMJCard(unsigned short _CardID)
{
	return J->GetSMJCard(_CardID);
}
#endif
#endif

void broker::B_StatusNew(std::string Fun, std::string Wert)
{
	B->StatusNew(Fun, Wert);
}

void broker::B_StatusE(std::string Modul, std::string Funktion, std::string Wert)
{
	B->StatusE(Modul, Funktion, Wert);
}