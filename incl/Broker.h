#ifndef BROKER_H
#define BROKER_H

//#define DF_Debug

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


#include <string>
#include <mutex> 
#include <vector>

#define BOT6LIST 0
#define BOTXLIST 1
#define RankRowStamps 10

#define WebAnalyser "https://t1421.de/"
#define WebTome "https://tome.t1421.de/"
#define WebLotto "https://lotto.t1421.de/"

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
class Tome_Game;
struct Tome_Booster;
class LottoWeek;

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

#ifndef noLoad
	std::string L_getSQL_Server();
	std::string L_getSQL_User();
	std::string L_getSQL_PW();
	std::string L_getSQL_DB();
	std::string L_getAdminKey();
	std::string L_getPMV_PATH();
	std::string L_getPMV_AUTO_PATH();
	std::string L_getPMV_ARCH_PATH();
	std::string L_getTMP_PATH();
	std::string L_getFFMPEG();
	std::string L_getRANK_PATH();
	std::string L_getTOME_SAVE_PATH();
	std::string L_getSMJPIC_PATH();
	std::string L_getSMJIMG_PATH();
	std::string L_getSMJPICSMALL_PATH();
	std::string L_getBOOSTER_PATH();
	std::string L_getLOTTOPIC_PATH();
	std::string L_getLOTTO_SAVE_PATH();
	std::string L_getMAPPIC_PATH();
	std::string L_getLivePvPPMV();
	std::string L_getLivePvP_OBS_Export();
	std::string L_getLivePvP_Pics();

	

	int L_getBOTRankMode(int _BOT);
#endif	

#ifndef noSMJ
	std::string J_GetImageSmall(unsigned short _CardID);
	std::string J_GetImage(unsigned short _CardID, unsigned char _Upgrade, unsigned char _Charges, unsigned long _Count, bool bSmall);
	unsigned char J_GetActionOrbForCardID(unsigned short CardID);
	unsigned char J_SwitchCharges(unsigned short _CardID, unsigned char _IstCharges);
	SMJCard* J_GetSMJCard(unsigned short _CardID);
	std::string J_GetImgOnly(unsigned short CardID);
	std::vector<std::pair<std::string, std::string>> J_GetEnum(std::string sEnumName);
	//Tome_Booster* J_OpenBooster(std::string iType);
	Tome_Booster* J_OpenBooster(std::string iType, bool bNoDouble, std::vector<Tome_Booster*> vOpendBooster);
	std::string J_GetLottoImg(std::string cardNameSimple, unsigned int iColor);
#endif
	


#if defined BrokerWeb
	void INIT();
	int AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	
	std::vector<std::string> FreeNames;
	std::string getName();
	void saveName();
	std::mutex mtx;

	std::string GetTeamName(std::string sTeamID);
	void saveTeams();
	std::vector<std::pair<std::string, std::string>> TeamNames;
#endif

	void B_StatusNew(std::string Fun, std::string Wert);
	void B_StatusNew(std::string Fun, int Wert);
	void B_StatusE(std::string Modul, std::string Funktion, std::string Wert);

#if defined BrokerTome || defined BrokerLotto
	void postChatEventMIS(std::string Value1);
	void postChatEventMIS(std::string Value1, std::string Value2);
	void postChatEventMIS(std::string Value1, std::string Value2, std::string Value3);
	void postChatEventMIS(std::string Value1, std::string Value2, std::string Value3, std::string Value4);
#endif

#if defined BrokerTome
	std::vector <Tome_Game*> vTomeGames;
	int getTomeGame(std::string sGameID);	
#endif

#if defined BrokerLotto
	void INIT();
	LottoWeek* getPullWeek();
	std::vector <LottoWeek*> vWeek;
	std::vector<std::pair<float,unsigned int>> LottoStages;
#endif

protected:
	

private:
	
};

#endif //BROKER_H


