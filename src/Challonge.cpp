//#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Load.h" 
#include "..\incl\Challonge.h" 
#include "..\incl\Utility.h" 
#include <iostream> 
#include <algorithm>

#define API_URL "api.challonge.com/v1/tournaments/"

broker *(Challonge::Bro) = NULL;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::chrono::system_clock::time_point parseISO8601(const std::string& iso8601) 
{
	if (iso8601 == "")return std::chrono::system_clock::from_time_t(0);
	// Splitte den ISO-8601-String in Datum, Zeit und Offset
	std::string date_str = iso8601.substr(0, 10);
	std::string time_str = iso8601.substr(11, 8);	

	std::tm tm = {};
	std::istringstream date_stream(date_str + " " + time_str);
	date_stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
	
	int offset_hour = std::stoi(iso8601.substr(23, 3));
	offset_hour -= 1;
	offset_hour *= -1 * 60 * 60;
	std::time_t time = std::mktime(&tm) + offset_hour;

	return std::chrono::system_clock::from_time_t(time);
}

bool compareLastUpdate(Match a, Match b)
{
	return parseISO8601(a.completed_at) > parseISO8601(b.completed_at);
}

Challonge::Challonge() :Thread_MIS("Challonge")
{
	MISS;
	curl_global_init(CURL_GLOBAL_DEFAULT);	
	MISE;
}

void Challonge::Init()
{
	MISS;
	sEventID = "";
	lastUpdate = std::chrono::system_clock::now();
	iMaxGames = 0;
	MISE;
}

Challonge::~Challonge()
{
	MISS;
	curl_global_cleanup();
	MISE;
}

void Challonge::setID(std::string _ID)
{
	MISS;
	sEventID = _ID;
	std::string sCMD = "del " + Bro->L->sChallongeSaveDir + " /S /Q";
	system(sCMD.c_str());
	if (!getPlayers())
	{
		Init();
		MISEA("We dont have players?");
		return;
	}

	MISE;
}

bool Challonge::getPlayers()
{
	MISS;
	if (sEventID == "")
	{
		MISEA("No ID")
		return false;
	}
	
	Players.clear();
	std::string sURL = 
		"https://" + Bro->L->sChallongeUser + 
		":" + Bro->L->sChallongeAPIKEY +
		"@" + API_URL + sEventID + "/participants.json";
	Json::Value JsonReturn = WEBRequestToCHASH(sURL);
	
	saveJson(JsonReturn, "participants.json");	

	for (auto J : JsonReturn)
	{
		Players.push_back(Challonge_Player(
			J["participant"]["id"].asString(),
			J["participant"]["display_name"].asString(),
			J["participant"]["group_player_ids"][0].asString()
			)
		);
	}

	//MISD(Players.size());
	MISE;
	return Players.size() > 0;
}

bool Challonge::getMatches()
{
	MISS;
	if (sEventID == "")
	{
		MISEA("No ID");
		return false;
	}

	std::vector<Match> vNewMatches;

	std::string sURL =
		"https://" + Bro->L->sChallongeUser +
		":" + Bro->L->sChallongeAPIKEY +
		"@" + API_URL + sEventID + "/matches.json";
	Json::Value JsonReturn = WEBRequestToCHASH(sURL);

	saveJson(JsonReturn, "matches.json");

	for (auto J : JsonReturn)
		vNewMatches.push_back(Match(
			J["match"]["id"].asString(),
			J["match"]["state"].asString(),
			J["match"]["player1_id"].asString(),
			J["match"]["player2_id"].asString(),
			J["match"]["completed_at"].asString(),
			J["match"]["scores_csv"].asString()));
	
	std::sort(vNewMatches.begin(), vNewMatches.end(), compareLastUpdate);

	unsigned int iMatchesDone = 0;	
	for (auto M : vNewMatches)	
		if (M.state == "complete")iMatchesDone++;
	

	std::stringstream ssUpdates;
	unsigned int iCount = 0;
	for (auto M : vNewMatches)
	{
		if (M.scores_csv == "")continue;
		
		for (auto P : Players)if (P.group_player_ids == M.player1_id || P.id == M.player1_id)ssUpdates << formatString(P.display_name, 10) << " vs ";
		for (auto P : Players)if (P.group_player_ids == M.player2_id || P.id == M.player2_id)ssUpdates << formatString(P.display_name, 10) << ": ";
		ssUpdates << M.scores_csv << "\n";
		
		if (++iCount >= 5)break;
	}
	std::ofstream Stream(Bro->L->sChallongeSaveDir + "Stream", std::ios::trunc);
	Stream << "Matches: " << iMatchesDone << " / " << vNewMatches.size() << "\n";
	Stream << "______________________________\n";
	Stream << ssUpdates.str() << "\n";
	Stream.close();
	
	char buffer[80];
	for (auto M : vNewMatches)
	{				
		if (parseISO8601(M.completed_at) > lastUpdate)
			MakeMassage(M);
	}
		
	lastUpdate = std::chrono::system_clock::now();
	/*
	if (iMaxGames != vNewMatches.size())
	{
		MISD("Refresh Players");
		getPlayers();
		iMaxGames = vNewMatches.size();
	}*/
	
	MISE;
	return vNewMatches.size() > 0;
}


void Challonge::saveJson(Json::Value _JSON,std::string _NAME)
{
	MISS;
	Json::StyledStreamWriter writer;
	std::ofstream SaveJson(Bro->L->sChallongeSaveDir + _NAME);
	writer.write(SaveJson, _JSON);
	SaveJson.close();
	MISE;
}

void Challonge::MakeMassage(Match M)
{
	MISS;
	std::stringstream ssMessage;
	ssMessage << "Update: ";
	for (auto P : Players) if (P.group_player_ids == M.player1_id || P.id == M.player1_id) ssMessage << P.display_name << " ";
	ssMessage << M.scores_csv << " ";
	for (auto P : Players)if (P.group_player_ids == M.player2_id || P.id == M.player2_id)ssMessage << P.display_name << " ";

	std::ofstream Massage(Bro->L->sChallongeSaveDir + "MES" + M.id, std::ios::trunc);
	Massage << ssMessage.str() << "\n";
	Massage.close();
	MISE;
}


Json::Value Challonge::WEBRequestToCHASH(std::string sURL)
{
	MISS;
	
	mutex_WEBRequest.lock();
	CURLcode res;
	long httpCode(0);

	Json::Value jsonData;
	Json::Reader jsonReader;

	std::string readBuffer = "";

	MISD("#1");
	curl = curl_easy_init();
	if (curl)
	{
		MISD("#2");
		curl_easy_setopt(curl, CURLOPT_URL, sURL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)Bro->B_StatusE("E", "GetJsonFromWeb - curl_easy_perform", curl_easy_strerror(res));
		
		MISD("#2");
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (httpCode == 200)
		{
			MISD("#3");
			if (jsonReader.parse(readBuffer, jsonData))
			{
				MISD("Json Request - Sucess")
			}
			else Bro->B_StatusE("E", "GetJsonFromWeb - jsonReader.parse", "");
		}
		else Bro->B_StatusE("E", "GetJsonFromWeb - httpCode", std::to_string(httpCode));

		curl_easy_cleanup(curl);
	}
	MISD("#4");
	mutex_WEBRequest.unlock();

	MISE;
	return jsonData;
}


void Challonge::Thread_Function()
{
	MISS;

	while (bRunning)
	{
		
		if (sEventID != "")
		{
			getMatches();
		}
		
		Sleep(10000);
	}
	MISE;
}