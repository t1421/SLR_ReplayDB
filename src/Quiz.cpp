#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Load.h" 
#include "..\incl\Quiz.h" 
#include "..\incl\Utility.h" 
#include <iostream> 
#include <fstream>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

broker *(Quiz::Bro) = NULL;

Quiz::Quiz() :Thread_MIS("Quiz")
{
	MISS;
	
	MISE;
}

void Quiz::Init()
{
	MISS;
	std::string sTemp;
	
	LoadPlayers();

	sTemp = Bro->L_getQuizPath() + "Name.txt";
	std::remove(sTemp.c_str());
	sTemp = Bro->L_getQuizPath() + "Q.txt";
	std::remove(sTemp.c_str());
	//sTemp = Bro->L_getQuizPath() + "MES*";
	//std::remove(sTemp.c_str());

	sTemp = "del " + Bro->L_getQuizPath() + "MES* /S /Q";
	system(sTemp.c_str());

	MISE;
}

Quiz::~Quiz()
{
	MISS;
	
	MISE;
}

/*
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

*/
void Quiz::LoadPlayers()
{
	LoadPlayers("Players");
}

void Quiz::LoadPlayers(std::string sName)
{
	MISS;

	std::string line;
	std::ifstream ifFile;

	ifFile.open(Bro->L_getQuizPath() + sName, std::ios::binary);
	if (!ifFile.good())
	{
		if (sName == "Players")
		{			
			Players.push_back(new Player("Twitch","Ingame"));
			SavePlayers();
		}
		MISEA("NoPlayers");
		return;
	}

	while (getline(ifFile, line))
	{
		if(sName == "Players" )Players.push_back(new Player(entry(line, 0), entry(line, 1)));
		else AddUpdatePlayers(entry(line, 0), entry(line, 1));
		ifFile.clear();
	}
	ifFile.close();

	MISE;
}

void Quiz::SavePlayers()
{
	MISS;
	std::ofstream ofFile;
	ofFile.open(Bro->L_getQuizPath() + "Players", std::ios::binary);
	if (ofFile.good())
	{
		for (auto P : Players)ofFile << P->Twitch << ";" << P->Ingame << ";" << std::endl;
		ofFile.close();
	}
	else MISEA("Error Saving Players");
	MISE;
}

bool Quiz::AddUpdatePlayers(std::string _Twitch, std::string _Ingame)
{
	MISS;
	Players.push_back(new Player(_Twitch, _Ingame));
	
	for (unsigned int i = Players.size() - 2; i > 0; i--)
		if (Players[i]->Twitch == _Twitch)
			Players.erase(Players.begin() + i);		

	SavePlayers();
	MISE;
}


void Quiz::Thread_Function()
{
	MISS;

	std::time_t tLastCheck = 0;

	while (bRunning)
	{
		path p(Bro->L_getQuizPath() + "Name.txt");
		if (exists(p)) 
		{
			if (tLastCheck < last_write_time(p))
			{
				tLastCheck = last_write_time(p);
				LoadPlayers("Name.txt");
			}			
		}
		Sleep(1000);
	}
	MISE;
}