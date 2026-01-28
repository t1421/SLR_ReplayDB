#define DF_Debug

#define NOMINMAX

#include "..\incl\Broker.h" 
#include "..\incl\Load.h" 
#include "..\incl\CardBaseSMJ.h" 
#include "..\incl\Stream.h" 
#include "..\incl\Utility.h" 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <algorithm>



#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <rapidfuzz/fuzz.hpp>

broker *(Stream::Bro) = NULL;

Stream::Stream() :Thread_MIS("Stream")
{
	MISS;

	MISE;
}

void Stream::Init()
{
	MISS;
	
	// Clear File
	std::ofstream ChatLog(Bro->L->sQuizPath + "ChatLog.log", std::ios::trunc);
	ChatLog << "";
	ChatLog.close();

	std::ofstream ChatCard(Bro->L->sQuizPath + "ChatCard.txt", std::ios::trunc);
	ChatCard << "";
	ChatCard.close();

	// Get Card Names in Vector
	for (auto* C : Bro->J->SMJMatrix)CardPool.push_back(std::make_pair(CleanCardNames(C->cardNameSimple),C->cardNameSimple));
		
	// Init Vars
	lastPosInFile = 0;

	//Skip this terms in Chat
	TwitchEmots.push_back("ultral34Spitfire2");
	TwitchEmots.push_back("ultral34HYPE");
	TwitchEmots.push_back("ultral34Booster");
	TwitchEmots.push_back("ultral34Graf");
	TwitchEmots.push_back("ultral34Spitfire");
	TwitchEmots.push_back("ultral34VIVI");
	TwitchEmots.push_back("ultral34Moon");
	TwitchEmots.push_back("ultral34FireDance");
	TwitchEmots.push_back("ultral34Knight");
	TwitchEmots.push_back("ultral34Rogan");
	TwitchEmots.push_back("ultral34Grinder");

	MISE;
}

Stream::~Stream()
{
	MISS;
	
	MISE;
}


void Stream::Thread_Function()
{
	MISS;
		
	std::time_t tLastCheck = 0;

	while (bRunning)
	{
		path p(Bro->L->sQuizPath + "ChatLog.log");
		if (exists(p)) 
		{
			if (tLastCheck < last_write_time(p))
			{
				tLastCheck = last_write_time(p);
				ProcessFile();
			}			
		}
		Sleep(1000);
	}
	MISE;
}



std::string Stream::CleanCardNames(std::string sIN)
{
	MISS;
	std::string sOUT;
	for (char c : sIN) if (std::isalpha(c)) sOUT += std::toupper(c);
	MISE;
	return sOUT;
}

std::string Stream::CleanChatMessage(std::string sIN)
{
	MISS;
	std::string sOUT;

	// Check Blocked Names
	std::string wort;
	
	//Clean Emost
	std::istringstream iss1(sIN);
	while (iss1 >> wort) 
		if (std::find(TwitchEmots.begin(), TwitchEmots.end(), wort) == TwitchEmots.end()) 
			sOUT += wort + ' ';

	// Only A-Z, everything es = ' '
	sIN = sOUT;
	sOUT.assign("");
	for (char c : sIN) if (std::isalpha(c)) sOUT += std::toupper(c); else sOUT += ' ';

	//Word for Word
	sIN = sOUT;
	sOUT.assign("");
	std::istringstream iss2(sIN);
	while (iss2 >> wort)sOUT += wort + ' ';

	MISE;
	return sOUT;
}

void Stream::MessageToVectors(std::string sIN, std::vector<std::string>& V1, std::vector<std::string>& V2, std::vector<std::string>& V3)
{
	MISS;
	std::string wort;

	V1.clear();
	V2.clear();
	V3.clear();

	std::istringstream iss(sIN);
	while (iss >> wort)V1.push_back(wort);

	for (unsigned int i = 0; i + 1 < V1.size(); ++i) V2.push_back(V1[i] + V1[i + 1]);
	for (unsigned int i = 0; i + 2 < V1.size(); ++i) V3.push_back(V1[i] + V1[i + 1] + V1[i + 2]);
	
	MISE;
}

void Stream::ProcessFile()
{
	MISS;
	std::string line;
	std::ifstream ifFile;
	std::vector<std::string> V1;
	std::vector<std::string> V2;
	std::vector<std::string> V3;
	std::vector<std::string> ALL;

	double highestScore;
	std::string closestMatch;

	ifFile.open(Bro->L->sQuizPath + "ChatLog.log", std::ios::binary);
	if (!ifFile.good())
	{
		MISEA("ChatLog.log ERROR ");
		return;
	}

	ifFile.seekg(lastPosInFile);

	while (getline(ifFile, line))
	{
		if (line.length() <= 1)continue;

		//Clear String and Spilt in Vectors
		MessageToVectors(CleanChatMessage(line), V1, V2, V3);
		ALL.clear();
		ALL.insert(ALL.end(), V1.begin(), V1.end());
		ALL.insert(ALL.end(), V2.begin(), V2.end());
		ALL.insert(ALL.end(), V3.begin(), V3.end());

		//Search
		closestMatch = "";
		highestScore = 0.0;

		for (auto W : ALL)
		{
			for (auto word : CardPool) {
				double score = rapidfuzz::fuzz::ratio(W, word.first);
				if (score > highestScore)
				{
					highestScore = score;
					closestMatch = word.second;
				}
			}
		}

		if (highestScore >= 90)
		{
			MISD(std::to_string(highestScore) + " " + closestMatch);
			std::ofstream ChatCard(Bro->L->sQuizPath + "ChatCard.txt", std::ios::trunc);
			ChatCard << closestMatch;
			ChatCard.close();
		}

		ifFile.clear();
	}

	ifFile.clear();
	ifFile.seekg(0, std::ios::end);
	lastPosInFile = ifFile.tellg();

	ifFile.close();

	MISE;
}