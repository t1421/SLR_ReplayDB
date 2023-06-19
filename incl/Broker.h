#ifndef BROKER_H
#define BROKER_H

//#define DF_Debug

#ifdef __linux__
	#ifdef DF_Debug 
		#define MISD(___Mes___) Bro->B_StatusNew(__PRETTY_FUNCTION__, ___Mes___);
		#define MISERROR(___Mes___)Bro->B_StatusE("E", __PRETTY_FUNCTION__, ___Mes___);
		#define MISS MISD("-->");
		#define MISE MISD("<--");
		#define MISEA(___Mes___) MISD("<-- " ___Mes___);
	#else
		#define MISD(___Mes___); 
		#define MISERROR(___Mes___)Bro->B_StatusE("E", __PRETTY_FUNCTION__, ___Mes___);
		#define MISS
		#define MISE
		#define MISEA(___Mes___);
	#endif
#else
	#ifdef DF_Debug 
		#define MISD(___Mes___) Bro->B_StatusNew(__FUNCTION__, ___Mes___);
		#define MISERROR(___Mes___)Bro->B_StatusE("E", __FUNCTION__, ___Mes___);
		#define MISS MISD("-->");
		#define MISE MISD("<--");
		#define MISEA(___Mes___) MISD("<-- " ___Mes___);
	#else
		#define MISD(___Mes___); 
		#define MISERROR(___Mes___)Bro->B_StatusE("E", __FUNCTION__, ___Mes___);
		#define MISS
		#define MISE
		#define MISEA(___Mes___);
	#endif
#endif	

#include <string>
#include <mutex> 
#include <vector>

#define BOT4LIST 0
#define KOTGLIST1 1
#define KOTGLIST2 2
#define KOTGLIST3 3
#define KOTGLIST4 4
#define KOTGLISTX 5
#define BOTXLIST 5
#define RankRowStamps 5

class DEBUG;
class SQL_MIS_New;
class Replay;
class LOAD;
class Manager;
class Imager;
class WEB_Main;
class MIS_Rank;
class CardBaseSMJ;
struct SMJCard;

class broker
{
public:
	broker();
	~broker();

	DEBUG* B;
	SQL_MIS_New* N;
	LOAD* L;
	Manager* M;
	Imager* I;
	WEB_Main *W;
	CardBaseSMJ *J;
	MIS_Rank* A[BOTXLIST + 1];

	broker* Bro;

	bool bAktive;

	unsigned char J_GetActionOrbForCardID(unsigned short CardID);

#if defined BrokerNormal || defined BrokerWeb
	std::string L_getSQL_Server();
	std::string L_getSQL_User();
	std::string L_getSQL_PW();
	std::string L_getSQL_DB();
	std::string L_getPMV_PATH();
	std::string L_getPMV_AUTO_PATH();
	std::string L_getPMV_ARCH_PATH();
	std::string L_getTMP_PATH();
	std::string L_getFFMPEG();
	std::string L_getRANK_PATH();
	std::string L_getSMJPIC_PATH();
	std::string L_getSMJIMG_PATH();
	std::string L_getSMJPICSMALL_PATH();
	int L_getBOTRankMode(int _BOT);

#ifndef noSMJ
	std::string J_GetImage(unsigned short _CardID, unsigned char _Upgrade, unsigned char _Charges, unsigned long _Count, bool bSmall);
	unsigned char J_SwitchCharges(unsigned short _CardID, unsigned char _IstCharges);
	SMJCard* J_GetSMJCard(unsigned short _CardID);
	std::string J_GetImgOnly(unsigned short CardID);
#endif
	
#endif	

//#ifndef noWEB
	void INIT();
	//int AddRankPlayer(unsigned int iRANK, std::string PMVPlayerID, unsigned long Playtime, std::string &sRankName, unsigned long _Points, unsigned long _Time);
	int AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	
	std::vector<std::string> FreeNames;
	std::string getName();
	void saveName();
	std::mutex mtx;

	std::string GetTeamName(std::string sTeamID);
	void saveTeams();
	//void KOTGTotalRanking();
	std::vector<std::pair<std::string, std::string>> TeamNames;
	std::mutex muxKOTG;
//#endif
	

	void B_StatusNew(std::string Fun, std::string Wert);
	void B_StatusE(std::string Modul, std::string Funktion, std::string Wert);


protected:
	

private:
	
};

#endif //BROKER_H


