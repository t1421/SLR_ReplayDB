#ifndef BROKER_H
#define BROKER_H
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

#define BOT1LIST 0
#define BOT2LIST 1
#define BOT3LIST 2
#define BOTXLIST 2

class DEBUG;
class SQL_MIS_New;
class CardBase;
class Replay;
class LOAD;
class Manager;
class Imager;
class WEB_Main;
class MIS_Rank;

class broker
{
public:
	broker();
	~broker();

	DEBUG* B;
	SQL_MIS_New* N;
	CardBase* C;
	LOAD* L;
	Manager* M;
	Imager* I;
	WEB_Main *W;
	MIS_Rank* A[BOTXLIST + 1];

	broker* Bro;

	bool bAktive;

//#if defined BrokerParser || defined BrokerWeb
	unsigned char C_GetActionOrbForCardID(unsigned short CardID);
//#endif

#ifdef BrokerNormal
	//unsigned char C_GetActionOrbForCardID(unsigned short CardID);
	bool C_DownloadPNG(unsigned short CardID);
#endif

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
	int L_getBOTRankMode(int _BOT);
	
#endif	

#ifdef BrokerWeb
	void INIT();
	int AddRankPlayer(unsigned int iRANK, unsigned long long PMVPlayerID, unsigned long Playtime, std::string &sRankName);
	std::vector<std::string> FreeNames;
	std::string getName();
	void saveName();
	std::mutex mtx;
#endif

	void B_StatusNew(std::string Fun, std::string Wert);
	void B_StatusE(std::string Modul, std::string Funktion, std::string Wert);


protected:
	

private:
	
};

#endif //BROKER_H

