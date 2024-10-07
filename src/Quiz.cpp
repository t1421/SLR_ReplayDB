#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Load.h" 
#include "..\incl\Quiz.h" 
#include "..\incl\Question.h" 
#include "..\incl\Utility.h" 
#include <iostream> 
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

broker *(Quiz::Bro) = NULL;
/*
Demon_Player::Demon_Player(Quiz* _QQ) : QQ(_QQ) {};
void Demon_Player::Thread_Function()
{
	std::time_t tLastCheck = 0;
	while (bRunning)
	{
		path p(Bro->L_getQuizPath() + "Name.txt");
		if (exists(p))
		{
			if (tLastCheck < last_write_time(p))
			{
				tLastCheck = last_write_time(p);
				Bro->Q->LoadPlayers("Name.txt");
			}
		}
		Sleep(1000);
	}
};
*/

Quiz::Quiz() :Thread_MIS("Quiz")
{
	MISS;
	ActivQuiz = 0;
	//DP = new Demon_Player(this);
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

	sTemp = "del .\\Twitch\\MES* /S /Q";
	system(sTemp.c_str());

	Load_Question();

	MISE;
}

Quiz::~Quiz()
{
	MISS;
	
	MISE;
}


void Quiz::LoadPlayers()
{
	LoadPlayers("Players.csv");
}

void Quiz::LoadPlayers(std::string sName)
{
	MISS;

	std::string line;
	std::ifstream ifFile;

	ifFile.open(Bro->L_getQuizPath() + sName, std::ios::binary);
	if (ifFile.good())while (getline(ifFile, line))
	{
		AddUpdatePlayers(entry(line, 0), entry(line, 1), entry(line, 2));
		ifFile.clear();
	}
	ifFile.close();

	UpdateHTML();

	MISE;
}

void Quiz::SavePlayers()
{
	MISS;
	std::ofstream ofFile;
	ofFile.open(Bro->L_getQuizPath() + "Players.csv", std::ios::binary);
	if (ofFile.good())
	{
		for (auto P : Players)ofFile << P->Twitch << ";" << P->Ingame << ";"<< P->WonID << ";" << std::endl;
		ofFile.close();
	}
	else MISEA("Error Saving Players");

	//UpdateHTML();
	MISE;
}

void Quiz::AddUpdatePlayers(std::string _Twitch, std::string _Ingame, std::string _WonID)
{
	MISS;
	for (auto P : Players)if (P->Twitch == _Twitch)
	{
		P->Ingame = _Ingame;
		SavePlayers();
		//UpdateHTML();
		MISEA("Update");
		return;
	}
	
	Players.push_back(new Player(_Twitch, _Ingame, _WonID));
	SavePlayers();
	MISEA("New");
}

void Quiz::Load_Question()
{
	MISS;
	std::string line;
	std::string sName = Bro->L_getQuizPath() + "Questions.csv";

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);

	if (ifFile.good())
	{
		MISD("good");

		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			vQuestion.push_back(new Question(
				entry(line, 0),
				entry(line, 1),
				entry(line, 2),
				atoi(entry(line, 3).c_str())
			));

			ifFile.clear();
		}
		ifFile.close();
	}
	else
	{
		MISEA("Questions.csv");
		return;
	}
	MISEA(+ std::to_string(vQuestion.size()));
}

void Quiz::Start(unsigned int iQuestion)
{
	MISS;

	if (iQuestion >= vQuestion.size())return;
	ActivQuiz = iQuestion;
	vQuestion[ActivQuiz]->Start();
	UpdateHTML();

	MISE;
}


void Quiz::Winner(unsigned int iQuestion)
{
	MISS;
	if (iQuestion >= vQuestion.size())return;
	vQuestion[iQuestion]->Winner() ;
	SavePlayers();
	UpdateHTML();
	MISE;
}

void Quiz::End(unsigned int iQuestion)
{
	MISS;
	if (iQuestion >= vQuestion.size())return;
	vQuestion[iQuestion]->bRunning = false;
	MISE;
}

void Quiz::ResetWinner()
{
	MISS;

	for (auto P : Players)P->WonID = "";
	SavePlayers();
	UpdateHTML();

	MISE;
}

Player* Quiz::GetPlayer(std::string sName)
{
	MISS;

	//In lists with name
	for (auto P : Players)if (P->Twitch == sName && P->Ingame != "")
	{
		MISEA("X1");
		return P;
	}

	//in list but no name
	for (auto P : Players)if (P->Twitch == sName && P->Ingame == "")
	{
		Twitch_Message(sName, "/w " + sName + " you still need to set you ingame name, use '!name [Your IG Name]'");
		MISEA("X2");
		return P;
	}
	MISD("#1");
	//New player
	AddUpdatePlayers(sName, "???", "");
	Twitch_Message(sName, "/w " + sName + " welcome to the quiz, dont forget to set your ingame name - use '!name [Your IG Name]'");
	
	MISEA("X3");
	return Players[Players.size() - 1];
}
/*
bool Quiz::CheckPlayerWon(std::string sName)
{
	MISS;
	bool OK = false;
	for (auto P : Players)if (P->Twitch == sName && P->WonID != "")return true;	
	MISE;
	return false;
}
*/

void Quiz::Thread_Function()
{
	MISS;
	/*
	DP->Start_Thread();
	while (bRunning)Sleep(1000);
	DP->Stop_Thread();
	*/
	
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

void Quiz::UpdateHTML()
{
	MISS;
	std::stringstream ssTable;
	std::ifstream ifFile;
	std::ofstream ofFile;
	std::string line;

	if (ActivQuiz == 0)return;
	MISD(ActivQuiz);
	MISD(vQuestion[ActivQuiz]->Answers.size());
	for (auto A : vQuestion[ActivQuiz]->Answers)
		ssTable << "<tr>"
		<< "<td>" << A->Pl->WonID << "</td>"
		<< "<td>" << A->Pl->Twitch << "</td>"
		<< "<td>" << A->Pl->Ingame << "</td>"
		<< "<td>" << A->iAnswer << "</td>"
		<< "<td>" << TimeToText(A->tTime) << "<td></td>\n";

	ifFile.open(Bro->L_getQuizPath() + "TEMPQuiz.HTML", std::ios::binary);
	ofFile.open(Bro->L_getQuizPath() + "Quiz.HTML", std::ios::binary);
	if (ifFile.good() && ofFile.good())while (getline(ifFile, line))
	{
		line = ReplaceString(line, "%TITEL%", vQuestion[ActivQuiz]->Titel);
		line = ReplaceString(line, "%QUESTION%", vQuestion[ActivQuiz]->Question_Twitch);
		line = ReplaceString(line, "%TABLE%", ssTable.str());
		
		ofFile << line;
		ifFile.clear();
	} 
	else MISEA("Error with HTML");

	ifFile.close();
	ofFile.close();

	MISE;
}

