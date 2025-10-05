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

#define EventsMax 19 + 1

class DEBUG;
class SQL_MIS_New;
class Replay;
class LOAD;
class Manager;
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
	WEB_Main *W;
	CardBaseSMJ *J;
	MIS_Rank* A[EventsMax];
	Challonge* C;
	Quiz* Q;

	broker* Bro;

	bool bAktive;

#ifndef noLoad
	unsigned long int L_getEEE_Now();
	unsigned long int L_StringToUNIXTime(const std::string& date);
	unsigned long int L_getEventRankMode(unsigned int iEvent);
	std::string L_getEventName(unsigned int iEvent);
	unsigned long int L_getEventStart(unsigned int iEvent);
	unsigned long int L_getEventEnd(unsigned int iEvent);
	unsigned long int L_getEventHide(unsigned int iEvent);
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



