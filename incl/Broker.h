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
#include <iomanip>

//#define BOT6LIST 0
//#define BOTXLIST 1
#define RankRowStamps 20

#define EventsMax 17 + 1

class DEBUG;
class SQL_MIS_New;
class Replay;
class LOAD;
class Manager;
class Imager;
class WEB_Main;
class MIS_Rank;
class CardBaseSMJ;
class Tome_Game;
class LottoWeek;
class Challonge;
class Quiz;

struct Tome_Booster;
struct SMJCard;
struct ROW;

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
	MIS_Rank* A[EventsMax];
	Challonge* C;
	Quiz* Q;

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
	std::string L_getPMV_WEB_PATH();
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
	std::string L_getQuizPath();
	int L_getLivePvPRefreshRate();
	int L_getLivePvPActionLog();
	int L_getLivePvPLastPlayed();
	int L_getLivePvPActionPerSec();
	int L_getLivePvPActionPerSecNumSec();
	int L_getCountDown();
	int L_getCoolDown();
	
	unsigned long L_getSRFileVersion();
	unsigned long L_getSRGameVersion();

	std::string L_getWebAnalyser();
	std::string L_getWebTome();
	std::string L_getWebLotto();

	
	std::string L_getEventName(unsigned int iEvent);
	unsigned long int L_getEventRankMode(unsigned int iEvent);
	unsigned long int L_getEventStart(unsigned int iEvent);
	unsigned long int L_getEventEnd(unsigned int iEvent);	
	unsigned long int L_getEventHide(unsigned int iEvent);
	unsigned long int L_getEEE_Now();
	unsigned long int L_StringToUNIXTime(const std::string& date);
	

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
	std::vector <std::string> J_getSimpelCardPool();
	std::vector <std::string> J_getColorPool();
	std::vector <std::string> J_getUpgradeMaps();
	std::vector <std::string> J_getTiers();
	std::vector <std::string> J_getDifficulty();
	std::vector <std::string> J_getType();
	std::vector <std::string> J_getDirections();	
	unsigned int J_GetSMJPower(unsigned short iCard, unsigned short iUpgrade);
#endif
	


#if defined BrokerWeb
	void INIT();
	unsigned int A_GetTotalPlayers(unsigned int iRANK);
	int A_AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps]);
	int A_AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps], unsigned long BestRunStamps[RankRowStamps]);
	int A_getRankMode(unsigned int iRANK);
	void A_UpdateRankMode(unsigned int iRANK);
	std::vector<ROW> A_getRankeROW(unsigned int iRANK);
	std::vector<ROW> A_getRankeROW(unsigned int iRANK, std::string _ID);
	
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

#ifdef MIS_Count 
	void L_ReplayPlus();;
#endif
protected:
	

private:
	
};

#endif //BROKER_H



