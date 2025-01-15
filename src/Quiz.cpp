#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Load.h" 
#include "..\incl\Quiz.h" 
#include "..\incl\Question.h" 
#include "..\incl\Utility.h" 
#include <iostream> 
#include <fstream>
#include <sstream>
#include <algorithm>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

broker *(Quiz::Bro) = NULL;

bool compare_sAnswer_iAnswer_tTime(const Answer* a, const Answer* b)
{
	if (a->sAnswer == b->sAnswer)
	{
		if (a->iAnswer == b->iAnswer)return a->tTime < b->tTime;
		else return a->iAnswer < b->iAnswer;
	}
	else return a->sAnswer < b->sAnswer;
}

Quiz::Quiz() :Thread_MIS("Quiz")
{
	MISS;
	ActivQuiz = 0;

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

	sTemp = "copy " + Bro->L_getQuizPath() + "TEMPQuiz.HTML " + Bro->L_getQuizPath() + "Quiz.HTML";
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
		AddUpdatePlayers(entry(line, 0), entry(line, 1), std::atoi(entry(line, 2).c_str()), entry(line, 3));
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
		for (auto P : Players)ofFile << P->Twitch << ";" << P->Ingame << ";"<< P->Points << ";" << P->WonID << ";" << std::endl;
		ofFile.close();
	}
	else MISEA("Error Saving Players");

	//UpdateHTML();
	MISE;
}

void Quiz::AddUpdatePlayers(std::string _Twitch, std::string _Ingame, unsigned int _Points, std::string _WonID)
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
	
	Players.push_back(new QuizPlayer(_Twitch, _Ingame, _Points, _WonID));
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
				atoi(entry(line, 3).c_str()),
				entry(line, 4), 
				atoi(entry(line, 5).c_str()),
				atoi(entry(line, 6).c_str())
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

void Quiz::ResetPoints()
{
	MISS;

	for (auto P : Players)P->Points = 0;
	SavePlayers();
	UpdateHTML();

	MISE;
}

QuizPlayer* Quiz::GetPlayer(std::string sName)
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
	AddUpdatePlayers(sName, "???", 0, "");
	Twitch_Message(sName, "/w " + sName + " welcome to the quiz, dont forget to set your ingame name - use '!name [Your IG Name]'");
	
	MISEA("X3");
	return Players[Players.size() - 1];
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


void Quiz::UpdateHTML()
{
	MISS;
	std::stringstream ssTable;
	std::ifstream ifFile;
	std::ofstream ofFile;
	std::string line;

	if (ActivQuiz == 0)return;
	
	// QUIZ HTML
	ssTable << "<thead>" << "<tr>" << "<td style = 'width: 100; '>QUIZ WON</td>" << "<td >Twitch</td>" << "<td >Ingame</td>";
	if (vQuestion[ActivQuiz]->AnswerType == 1 || vQuestion[ActivQuiz]->AnswerType == 3 || vQuestion[ActivQuiz]->AnswerType == 5) ssTable << "<td >Guess N</td>";
	if (vQuestion[ActivQuiz]->AnswerType == 2 || vQuestion[ActivQuiz]->AnswerType == 3 || vQuestion[ActivQuiz]->AnswerType == 4) ssTable << "<td >Guess T</td>";
	ssTable << "<td >Time</td>"	<< "</tr>"<< "</thead><tbody>";
	
	std::sort(vQuestion[ActivQuiz]->Answers.begin(), vQuestion[ActivQuiz]->Answers.end(), compare_sAnswer_iAnswer_tTime);
	
	for (auto A : vQuestion[ActivQuiz]->Answers)
	{
		ssTable << "<tr>";
		if (A->Pl->WonID == vQuestion[ActivQuiz]->ID)ssTable << "<td style='background-color: #8B6914;'>" << A->Pl->WonID << "</td>";
		else if (A->Pl->WonID != "")ssTable << "<td style='background-color: #333333;'>" << A->Pl->WonID << "</td>";
		else ssTable << "<td>" << A->Pl->WonID << "</td>";
		ssTable << "<td>" << A->Pl->Twitch << "</td>";
		ssTable << "<td>" << A->Pl->Ingame << "</td>";

		if (vQuestion[ActivQuiz]->AnswerType == 1 || vQuestion[ActivQuiz]->AnswerType == 3)ssTable << "<td>" << A->iAnswer << "</td>";
		if (vQuestion[ActivQuiz]->AnswerType == 5)ssTable << "<td>" << TimeToDate(A->iAnswer) << "</td>";
		if (vQuestion[ActivQuiz]->AnswerType == 2 || vQuestion[ActivQuiz]->AnswerType == 3 || vQuestion[ActivQuiz]->AnswerType == 4) ssTable << "<td>" << A->sAnswer << "</td>";
		ssTable << "<td>" << TimeToText(A->tTime) << "<td></td>\n";
	}
	ssTable << "</tbody>";

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

	//Player HTML
	ssTable.str("");

	ssTable << "<thead>" << "<tr>" << "<td style = 'width: 100; '>QUIZ WON</td>" << "<td >Twitch</td>" << "<td >Ingame</td>" << "<td >Points</td>" << "</tr>" << "</thead><tbody>";

	auto localPlayers = Players;
	std::sort(localPlayers.begin(), localPlayers.end(), [](const QuizPlayer* a, const QuizPlayer* b) {return a->Points > b->Points;});

	for (auto P : localPlayers)
	{
		if (P->Points == 0)continue;

		ssTable << "<tr>";
		if (P->WonID != "")ssTable << "<td style='background-color: #333333;'>" << P->WonID << "</td>";
		else ssTable << "<td> </td>";
		ssTable << "<td>" << P->Twitch << "</td>";
		ssTable << "<td>" << P->Ingame << "</td>";
		ssTable << "<td>" << P->Points << "</td>";		
	}
	ssTable << "</tbody>";

	ifFile.open(Bro->L_getQuizPath() + "TEMPPlayer.HTML", std::ios::binary);
	ofFile.open(Bro->L_getQuizPath() + "Player.HTML", std::ios::binary);
	if (ifFile.good() && ofFile.good())while (getline(ifFile, line))
	{		
		line = ReplaceString(line, "%TABLE%", ssTable.str());

		ofFile << line;
		ifFile.clear();
	}
	else MISEA("Error with HTML");

	ifFile.close();
	ofFile.close();

	MISE;
}

