#ifndef Challonge_H
#define Challonge_H

#include "Thread_MIS.h"

#include <fstream>
#include <vector>

#include <chrono>
#include <ctime>
#include <iomanip>

#include <curl/curl.h>
#include <json/json.h>
#include <json/writer.h>

struct Match
{
	Match(std::string _sID,std::string _state, std::string _sPlayer1ID, std::string _sPlayer2ID, std::string _completed_at, std::string _scores_csv) :
		id(_sID), state(_state), player1_id(_sPlayer1ID), player2_id(_sPlayer2ID), completed_at(_completed_at), scores_csv(_scores_csv){};
	std::string id;
	std::string state;
	std::string player1_id;
	std::string player2_id;
	std::string completed_at;
	std::string scores_csv;
};

struct Player
{
	Player(std::string _sID, std::string _display_name, std::string _group_player_ids) :
		id(_sID), display_name(_display_name), group_player_ids(_group_player_ids){};
	std::string id;
	std::string display_name;
	std::string group_player_ids;
	//std::vector<std::string> group_player_ids;	
};

class Challonge : public Thread_MIS
{
public:
	Challonge();
	~Challonge();

	void Init();

	void setID(std::string _ID);
	bool getPlayers();
	bool getMatches();
	
	//BROKER
	static broker* Bro;
	void teachC() { Bro->C = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:

	void Thread_Function();

	Json::Value WEBRequestToCHASH(std::string sURL);
	CURL *curl;
	std::mutex mutex_WEBRequest;

	std::string sEventID;
	std::vector<Player> Players;
	void saveJson(Json::Value _JSON, std::string _NAME);

	//std::vector<Match> vLastMatches;
	void MakeMassage(Match M);
	std::chrono::system_clock::time_point lastUpdate;
	unsigned int iMaxGames;
	
};

#endif //CardBase_H


