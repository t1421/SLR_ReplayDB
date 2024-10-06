#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Question.h" 
#include "..\incl\Quiz.h"
#include "..\incl\Utility.h" 
#include "..\incl\Thread_MIS.h" 

#include <fstream>
#include <iostream> 
#include <sstream>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

bool compare_iAnswer(const Answer* a, const Answer* b) { return a->iAnswer < b->iAnswer; }

broker* (Question::Bro) = NULL;
/*
Demon_Answers::Demon_Answers(Question* _QQ) : QQ(_QQ) {};

void Demon_Answers::Thread_Function()
{
	std::time_t tLastCheck = 0;

	while (bRunning)
	{
		
		//if (Bro->Q->Running())
		//{
		//	path p(Bro->L_getQuizPath() + "Q.txt");
		//	if (exists(p))
		//	{
		//		if (tLastCheck < last_write_time(p))
		//		{
		//			tLastCheck = last_write_time(p);
		//			//Bro->Q->LoadPlayers("Q.txt");
		//		}
		//	}
		//}
		//Sleep(10);
	}
};
*/

Question::Question(std::string _ID, std::string _Titel, std::string _Question_Twitch, int _iAnswer) :
	ID(_ID), Titel(_Titel), Question_Twitch(_Question_Twitch), iAnswer(_iAnswer)
{
	//DA = new Demon_Answers(this);
};

Question::~Question()
{
	MISS;

	MISE;
}

void Question::echo()
{
	MISS;
	printf("########################################\n");
	printf("ID:       %s\n", ID.c_str());
	printf("Titel:    %s\n", Titel.c_str());
	printf("Question: %s\n", Question_Twitch.c_str());
	printf("Int:      %i\n", iAnswer);	
	printf("########################################\n");
	MISE;
}

void Question::Start()
{
	MISS;
	echo();

	tStart = Bro->L_getEEE_Now();

	ResetAnswers();
	Twitch_Message(ID,"ultral34Spitfire2 ultral34Spitfire2 ultral34Spitfire2 ", Titel, Question_Twitch, "ultral34Booster ultral34Booster ultral34Booster ");		
	//Answers.push_back(new Answer("Twitch", 0, Bro->L_getEEE_Now()));
	Start_Thread();

	MISE;
}

void Question::ResetAnswers()
{
	MISS;
	std::string sTemp = Bro->L_getQuizPath() + "Q.txt";
	std::remove(sTemp.c_str());

	Answers.clear();
	MISE;
}

void Question::Winner()
{
	MISS;
	std::string sTemp = "copy " + Bro->L_getQuizPath() + "Q.txt " + Bro->L_getQuizPath() + "Q" + ID + ".txt";
	system(sTemp.c_str());
	 sTemp = "copy " + Bro->L_getQuizPath() + "QQ.txt " + Bro->L_getQuizPath() + "QQ" + ID + ".txt";
	system(sTemp.c_str());
	
	Answer* Winner = getWinningAnswer();
	Bro->Q->CheckPlayerName(Winner->Twitch);

	Twitch_Message(ID, "ultral34Booster ultral34Booster ultral34Booster", "The winner is: @" + Winner->Twitch, "With " + std::to_string(Winner->iAnswer), "The correct answer was: " + std::to_string(iAnswer), "ultral34Booster ultral34Booster ultral34Booster");


	

	MISE;
}

Answer* Question::getWinningAnswer()
{
	MISS;

	Answer* result = nullptr;
	int minDistance = std::numeric_limits<int>::max();

	std::vector <Answer*> LocalAnswers = Answers;

	//Remove players who won befor
	for (std::vector<Answer*>::iterator it = LocalAnswers.begin(); it != LocalAnswers.end();)
	{		
		if (Bro->Q->CheckPlayerWon((*it)->Twitch))it = LocalAnswers.erase(it);
		else  ++it;
	}

	//sort by number
	//std::sort(LocalAnswers.begin(), LocalAnswers.end(), [](const Answer& a, const Answer& b) {return a.iAnswer < b.iAnswer; });
	std::sort(LocalAnswers.begin(), LocalAnswers.end(), compare_iAnswer);

	for (const auto& A : LocalAnswers) 
	{
		int distance = std::abs(int(A->tTime - iAnswer)); // Berechne den Abstand

		// Falls der Abstand kleiner ist oder gleich ist, aber mit höherem order
		if (distance < minDistance) {
			minDistance = distance; // Aktualisiere den minimalen Abstand
			result = A; // Setze das aktuelle Ergebnis
		}
		else if (distance == minDistance) {
			// Wenn die Abstände gleich sind, vergleiche die Order-Werte
			if (result != nullptr && A->tTime < result->tTime) {
				result = A; // Setze das Ergebnis, wenn der order kleiner ist
			}
		}
	}

	MISE;
	return result;
}

void Question::Thread_Function()
{
	MISS;
	
	std::time_t tLastCheck = 0;

	while (bRunning && tStart + CountDown > Bro->L_getEEE_Now())
	{
		path p(Bro->L_getQuizPath() + "Q.txt");
		if (exists(p))
		{
			if (tLastCheck < last_write_time(p))
			{
				tLastCheck = last_write_time(p);
				LoadAnswers();
			}
		}
		Sleep(10);

		SetCountDown(tStart + CountDown - Bro->L_getEEE_Now());
	}

	SetCountDown(0);
	Twitch_Message(ID, "ultral34Booster ultral34Booster ultral34Booster ", "TIME IS UP");
	Sleep(1000);
	LoadAnswers();	
	MISE;
}


void Question::LoadAnswers()
{
	MISS;
	std::string line;
	std::ifstream ifFile;

	ifFile.open(Bro->L_getQuizPath() + "Q.txt", std::ios::binary);
	if (!ifFile.good())
	{
		MISEA("Q.txt");
		return;
	}
	
	bool Update;
	while (getline(ifFile, line))
	{
		Update = false;
		for (auto A : Answers)if (A->Twitch == entry(line, 0))
		{
			A->iAnswer = atoi(entry(line, 1).c_str());
			A->tTime = Bro->L_getEEE_Now();
			Update = true;
		}

		if (Update == false)
		{
			Answers.push_back(new Answer(entry(line, 0), atoi(entry(line, 1).c_str()), Bro->L_getEEE_Now()));
			Bro->Q->CheckPlayerName(entry(line, 0));
		}

		ifFile.clear();
	}
	ifFile.close();

	SaveAnswers();

	MISE;
}

void Question::SaveAnswers()
{
	MISS;
	std::ofstream ofFile;
	ofFile.open(Bro->L_getQuizPath() + "QQ" + ID + ".txt", std::ios::binary);
	if (ofFile.good())
	{
		for (auto A : Answers)ofFile << A->Twitch << ";" << A->iAnswer << ";"  << A->tTime << ";" << std::endl;
		ofFile.close();
	}
	else MISEA("Error Saving QQ");
	MISE;
}

void Question::SetCountDown(unsigned int iii)
{
	MISS;	
	std::ofstream ofFile;
	ofFile.open(Bro->L_getQuizPath() + "CountDown.txt", std::ios::binary);
	if (ofFile.good())
	{
		ofFile << iii << std::endl;
		ofFile.close();
	}
	else MISEA("Error Saving CountDown");

	MISE;
}