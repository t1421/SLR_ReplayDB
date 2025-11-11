//#define DF_Debug
#include "..\incl\Broker.h"

#include "..\incl\DEBUG.h"

#if defined BrokerQuiz
#include "..\incl\Thread_MIS.h" 
#include "..\incl\Quiz.h" 
#include "..\incl\Question.h" 
#endif

#if defined BrokerTome || defined BrokerNormal || defined BrokerWeb || defined BrokerLotto || defined BrokerPVP
#include "..\incl\Replay.h" 
#include "..\incl\Reader.h" 
#include "..\incl\Thread_MIS.h" 
#endif

#if defined BrokerTome || defined BrokerWeb || defined BrokerLotto
#include "..\incl\Utility.h"

#include "..\incl\WEB\WEB_Main.h"
#include "..\incl\WEB\WEB_Server.h"
#include "..\incl\WEB\WEB_Toolbar.h"

#include "..\incl\WEB_Analyser\WEB_Analyser.h"
#endif

#if defined BrokerWeb
#include "..\incl\WEB_Analyser\WEB_CONTAINER_Analyser.h"

#include "..\incl\WEB_Analyser\WEB_Event.h"
#include "..\incl\WEB_Analyser\WEB_Quest.h"
#include "..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\incl\MIS_Rank.h"

#include "..\incl\WEB_Analyser\WEB_Analyser_Head.h"
#include "..\incl\WEB_Analyser\WEB_Analyser_Deck.h"
#include "..\incl\WEB_Analyser\WEB_Analyser_Acti.h"
#endif

#if defined BrokerTome
#include "..\incl\WEB_Tome\WEB_CONTAINER_Tome.h"
#include "..\incl\WEB_Tome\WEB_Tome_Admin.h"
#include "..\incl\WEB_Tome\WEB_Tome_Login.h"
#include "..\incl\WEB_Tome\WEB_Tome_Debug.h"
#include "..\incl\WEB_Tome\WEB_Tome_Player.h"
#include "..\incl\WEB_Tome\WEB_Tome_Public.h"
#include "..\incl\WEB_Tome\WEB_Tome_PublicBoosters.h"
#include "..\incl\WEB_Tome\WEB_Tome_PublicPlayers.h"
#include "..\incl\WEB_Tome\WEB_Tome_PublicCards.h"
#include "..\incl\WEB_Tome\WEB_Tome_PublicPlayersBooster.h"
#include "..\incl\WEB_Tome\WEB_Tome_Leave.h"
#include "..\incl\WEB_Tome\Tome_Game.h"
#endif

#if defined  BrokerLotto
#include "..\incl\WEB_Lotto\WEB_Container_Lotto.h"
#include "..\incl\WEB_Lotto\LottoWeek.h"
#include "..\incl\WEB_Lotto\WEB_Lotto_Admin.h"
#include "..\incl\WEB_Lotto\WEB_Lotto_Admin_Main.h"
#include "..\incl\WEB_Lotto\WEB_Lotto_Admin_Pull.h"
#include "..\incl\WEB_Lotto\WEB_Lotto_Week.h"
#endif

#if defined  BrokerChallonge
#include "..\incl\Challonge.h"
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

#ifndef noLoad
#include "..\incl\LOAD.h"
#endif

broker::broker()
{
	bAktive = true;
	Bro = this;

	DEBUG::learnBro(this);
	B = NULL;	

#if defined BrokerNormal || defined BrokerWeb || defined BrokerTome || defined BrokerLotto  || defined BrokerPVP
	Replay::learnBro(this);
	Reader::learnBro(this);
	Thread_MIS::learnBro(this);
#endif

#if defined BrokerTome || defined BrokerWeb || defined BrokerLotto
	WEB_Main::learnBro(this);
	WEB_Server::learnBro(this);
	WEB_Toolbar::learnBro(this);	
	WEB_Analyser::learnBro(this);

	W = NULL;
#endif

#if defined BrokerWeb
	WEB_Container::learnBro(this);

	WEB_Event::learnBro(this);
	WEB_Quest::learnBro(this);
	WEB_Rank::learnBro(this);	
	MIS_Rank::learnBro(this);
	
	WEB_Analyser_Head::learnBro(this);
	WEB_Analyser_Deck::learnBro(this);
	WEB_Analyser_Acti::learnBro(this);
#endif

#if defined BrokerTome
	WEB_Container_Tome::learnBro(this);
	WEB_Tome_Admin::learnBro(this);
	WEB_Tome_Login::learnBro(this);
	WEB_Tome_Debug::learnBro(this);
	WEB_Tome_Player::learnBro(this);
	WEB_Tome_Public::learnBro(this);
	WEB_Tome_PublicBoosters::learnBro(this);
	WEB_Tome_PublicPlayers::learnBro(this);
	WEB_Tome_PublicCards::learnBro(this);
	WEB_Tome_PublicPlayersBooster::learnBro(this);
	WEB_Tome_Leave::learnBro(this);
	
	Tome_Game::learnBro(this);

	
#endif

#ifdef BrokerNormal || defined BrokerPVP || defined BrokerQuiz
	Thread_MIS::learnBro(this);
#endif

#if defined BrokerLotto
	WEB_Container_Lotto::learnBro(this);
	LottoWeek::learnBro(this);	
	WEB_Lotto_Admin::learnBro(this);
	WEB_Lotto_Admin_Main::learnBro(this);
	WEB_Lotto_Admin_Pull::learnBro(this);
	WEB_Lotto_Week::learnBro(this);	
#endif

#if defined BrokerChallonge
	Challonge::learnBro(this);
	C = NULL;
#endif

#if defined BrokerQuiz
	Quiz::learnBro(this);
	Question::learnBro(this);
	Q = NULL;
#endif

#ifndef noSMJ
	CardBaseSMJ::learnBro(this);
	J = NULL;
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
	
#ifndef noLoad
	LOAD::learnBro(this);
	L = NULL;
#endif
	

}

#if defined BrokerWeb
void broker::INIT()
{	
	for (int i = 0; i < EventsMax; i++)A[i] = new MIS_Rank(i);

	std::ifstream ifFile;
	std::string line;
	
	ifFile.open(L->sRANK_PATH + "Names.csv", std::ios::binary);
	if (!ifFile.good())
	{
		return;
	}
	
	std::copy(std::istream_iterator<std::string>(ifFile),
		std::istream_iterator<std::string>(),
		std::back_inserter(FreeNames));
	
	ifFile.close();


	ifFile.open(L->sRANK_PATH + "Teams.csv", std::ios::binary);
	if (ifFile.good())
	{
		while (getline(ifFile, line))		
			TeamNames.push_back(std::make_pair(entry(line, 0), entry(line, 1)));;
		
		ifFile.close();
	}


	///Load Quest Players
	ifFile.open(L->sRANK_PATH + "QPlayer.csv", std::ios::binary);
	if (ifFile.good())
	{
		while (getline(ifFile, line))
		{
			if (INI_Value_Check(line, "P"))
				QPlayer.push_back(new QuestPlayer(entry(line, 0), entry(line, 1)));
			if (INI_Value_Check(line, "PQ"))
				QPlayer[QPlayer.size() - 1]->Stamps.push_back(std::make_pair(entry(line, 0), atoi(entry(line, 1).c_str())));
		}
		ifFile.close();
	}
	
}

int broker::A_AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps])
{
	return A[iRANK]->AddPlayer(_ID, _ReplayID, _Stamps);
}
int broker::A_AddPlayer(unsigned int iRANK, std::string _ID, unsigned long _ReplayID, unsigned long _Stamps[RankRowStamps], unsigned long BestRunStamps[RankRowStamps])
{
	return A[iRANK]->AddPlayer(_ID, _ReplayID, _Stamps, BestRunStamps);
}

int broker::A_getRankMode(unsigned int iRANK)
{
	return A[iRANK]->RankMode;
}

std::vector<ROW> broker::A_getRankeROW(unsigned int iRANK)
{
	return A[iRANK]->getRankeROW("");
}

std::vector<ROW> broker::A_getRankeROW(unsigned int iRANK, std::string _ID)
{
	return A[iRANK]->getRankeROW(_ID);
}

void broker::A_UpdateRankMode(unsigned int iRANK)
{
	A[iRANK]->RankMode = L_getEventRankMode(iRANK);
}

unsigned int broker::A_GetTotalPlayers(unsigned int iRANK)
{
	return A[iRANK]->getRankeROW("").size();
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
	ofFile.open(L->sRANK_PATH + "Names.csv", std::ios::binary);
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
	ofFile.open(L->sRANK_PATH + "Teams.csv", std::ios::binary);
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

void broker::saveQPlayer()
{
	printf("saveQPlayer\n");
	std::ofstream ofFile;
	ofFile.open(L->sRANK_PATH + "QPlayer.csv", std::ios::binary);
	if (ofFile.good())
	{
		printf("FILE OK\n");
		for (auto P : QPlayer)
		{
			ofFile << "P="<< P->PlayerID<< ";"<< P->PlayerName<< ";" << std::endl;
			for (auto Q : P->Stamps)
				ofFile << "PQ=" << Q.first<< ";" << Q.second << ";" << std::endl;
		}		
		ofFile.close();
	}
	else printf("XXX\n");
}

#endif

broker::~broker()
{
	//MISS;
	//tFadeThread.join();
	//MISE;
}


#ifndef noLoad
unsigned long int broker::L_getEEE_Now()
{
	const auto UNIX = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::seconds>(UNIX.time_since_epoch()).count();
}

unsigned long int broker::L_StringToUNIXTime(const std::string &date)
{
	std::tm timeStruct = {};
	std::istringstream dateStream(date);

	// Parsen des Datums
	dateStream >> std::get_time(&timeStruct, "%d.%m.%Y");
	if (dateStream.fail()) return 0;
	
	// Zeit in Sekunden seit der Epoche umwandeln
	timeStruct.tm_hour = 0;  // Stunde auf Mitternacht setzen
	timeStruct.tm_min = 0;   // Minute auf 0 setzen
	timeStruct.tm_sec = 0;   // Sekunde auf 0 setzen
	timeStruct.tm_isdst = -1; // Sommerzeit automatisch bestimmen

	std::time_t epochTime = std::mktime(&timeStruct);
	if (epochTime == -1) return 0;	

	return static_cast<unsigned long int>(epochTime);
}

unsigned long int broker::L_getEventRankMode(unsigned int iEvent)
{
	if (iEvent >= EventsMax) return 98;

	unsigned long int now = L_getEEE_Now();

	// Not Started / Dont show
	if (now < L->Events[iEvent].Start)return 10;

	// Hide Aktive / Dont show
	if (now > L->Events[iEvent].Hide)return 11;

	// Has Ended / Show + dont add
	if (now > L->Events[iEvent].End)return 1;

	// is running // Only show +/- 1Players  + add
	if (now > L->Events[iEvent].Start && L->Events[iEvent].RankType == 5)return 5;
	// SPecial ranking view
	if (now > L->Events[iEvent].Start && L->Events[iEvent].RankType == 6)return 6;

	// is running // show + add
	if (now > L->Events[iEvent].Start)return 2;

	//ERROR
	return 99;
}

std::string broker::L_getEventName(unsigned int iEvent)
{
	return L->Events[iEvent].Name;
}
unsigned long int broker::L_getEventStart(unsigned int iEvent)
{
	return L->Events[iEvent].Start;
}
unsigned long int broker::L_getEventEnd(unsigned int iEvent)
{
	return L->Events[iEvent].End;
}
unsigned long int broker::L_getEventHide(unsigned int iEvent)
{
	return L->Events[iEvent].Hide;
}
#endif

void broker::B_StatusNew(std::string Fun, std::string Wert)
{
	B->StatusNew(Fun, Wert);
}

void broker::B_StatusNew(std::string Fun, int Wert)
{
	B->StatusNew(Fun, std::to_string(Wert));
}

void broker::B_StatusE(std::string Modul, std::string Funktion, std::string Wert)
{
	B->StatusE(Modul, Funktion, Wert);
}

#if defined BrokerTome
int broker::getTomeGame(std::string sGameID)
{
	if (sGameID == "") return -1;
	for (unsigned int iTemp = 0; iTemp < vTomeGames.size(); iTemp++)
		if (vTomeGames[iTemp]->sGameID == sGameID) return iTemp;
	Tome_Game* tg = new Tome_Game(sGameID);
	if (tg->sGameID == sGameID || sGameID == "NEW")
	{
		vTomeGames.push_back(tg);
		return vTomeGames.size() - 1;
	}

	return -2;
}
#endif

#if defined BrokerTome || defined BrokerLotto
void broker::postChatEventMIS(std::string Value1)
{
	MISS;
	postChatEventMIS(Value1, "", "", "");
	MISE;
}
void broker::postChatEventMIS(std::string Value1, std::string Value2)
{
	MISS;
	postChatEventMIS(Value1, Value2, "", "");
	MISE;
}
void broker::postChatEventMIS(std::string Value1, std::string Value2, std::string Value3)
{
	MISS;
	postChatEventMIS(Value1, Value2, Value3, "");
	MISE;
}
void broker::postChatEventMIS(std::string Value1, std::string Value2, std::string Value3, std::string Value4)
{
	MISS;
	MISD(Value1 + "-" + Value2 + "-" + Value3 + "-" + Value4);
	if (W != NULL)if (W->WW)W->WW->postChatEventMIS(Value1, Value2, Value3, Value4);
	MISE;
}
#endif

#if defined BrokerLotto
void broker::INIT()
{
	bool OK = true;
	for (unsigned int i = 0; i < 50 && OK; i++)
	{
		vWeek.push_back(new LottoWeek);
		OK = vWeek[vWeek.size() - 1]->bLoadGame(i);
	}
	vWeek.pop_back();

	//Wie viel przent vom Preis | Wie viele richtige
	LottoStages.push_back(std::make_pair(0.50, 20));
	LottoStages.push_back(std::make_pair(0.20, 19));
	LottoStages.push_back(std::make_pair(0.15, 17));
	LottoStages.push_back(std::make_pair(0.10, 15));
	LottoStages.push_back(std::make_pair(0.05, 10));
}

LottoWeek* broker::getPullWeek()
{
	for each(LottoWeek *W in vWeek)
		if (W->iStatus == 3)return W;
	return new LottoWeek();
}
#endif

#ifdef MIS_Count
void broker::L_ReplayPlus()
{
	L->ReplayPlus();
}
#endif
