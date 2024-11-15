#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Question.h" 
#include "..\incl\Quiz.h"
#include "..\incl\Utility.h" 
#include "..\incl\Thread_MIS.h" 

#include <fstream>
#include <iostream> 
#include <sstream>
#include <cctype>
#include <algorithm>
#include <regex>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <rapidfuzz/fuzz.hpp>

bool compare_iAnswer(const Answer* a, const Answer* b) { return a->iAnswer < b->iAnswer; }
bool compare_tTime(const Answer* a, const Answer* b) { return a->tTime < b->tTime; }

broker* (Question::Bro) = NULL;

Question::Question(std::string _ID, std::string _Titel, std::string _Question_Twitch, int _iAnswer, std::string _sAnswer, unsigned int _AnswerType, unsigned int _SpellCheckType) :
	ID(_ID), Titel(_Titel), Question_Twitch(_Question_Twitch), iAnswer(_iAnswer), sAnswer(CleanString(_sAnswer)), AnswerType(_AnswerType), SpellCheckType(_SpellCheckType)
{
	MISS;
	
	MISE;
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
	printf("String:   %s\n", sAnswer.c_str());
	printf("Type:     %i\n", AnswerType);
	printf("Spell:    %i\n", SpellCheckType);
	printf("########################################\n");
	MISE;
}

void Question::Start()
{
	MISS;
	echo();

	tStart = Bro->L_getEEE_Now();
	lastQPos = 0;
	CheckPool.clear();
	switch (SpellCheckType)
	{
	case 1: //Card Names
		for (auto S : Bro->J_getSimpelCardPool())CheckPool.push_back(CleanString(S));
		break;
	case 2: //Color / Faction
		for (auto S : Bro->J_getColorPool())CheckPool.push_back(CleanString(S));
		break;
	case 3: //Maps
		for (auto S : Bro->J_getUpgradeMaps())CheckPool.push_back(CleanString(S));
		break;
	case 4: //Tier
		for (auto S : Bro->J_getTiers())CheckPool.push_back(CleanString(S));
		break;
	}

	ResetAnswers();
	Twitch_Message(ID,"ultral34Spitfire2 ultral34Spitfire2 ultral34Spitfire2 ", Titel, Question_Twitch, "ultral34Booster ultral34Booster ultral34Booster ");
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
	if (Winner != nullptr)
	{
		Winner->Pl->WonID = ID;
		if( AnswerType == 1)Twitch_Message(ID, "The winner is: @" + Winner->Pl->Twitch +  " With " + std::to_string(Winner->iAnswer), "The correct answer was: " + std::to_string(iAnswer));
		if (AnswerType == 2 || AnswerType == 4)Twitch_Message(ID, "The winner is: @" + Winner->Pl->Twitch + " With " + Winner->sAnswer, "The correct answer was: " + sAnswer);
		if (AnswerType == 3)Twitch_Message(ID, "The winner is: @" + Winner->Pl->Twitch + " With " +  Winner->sAnswer + " " + std::to_string(Winner->iAnswer), "The correct answer was: " + sAnswer + " " + std::to_string(iAnswer));
		if (Winner->Pl->Ingame == "") Twitch_Message(Winner->Pl->Twitch, "/w " + Winner->Pl->Twitch + " still need '!name [Your IG Name]'");
	}
	else Twitch_Message(ID, "No winner :-|");


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
		//if (Bro->Q->CheckPlayerWon((*it)->Pl->Twitch))it = LocalAnswers.erase(it);
		if ((*it)->Pl->WonID != "") it = LocalAnswers.erase(it);
		else  ++it;
	}

	//sort by number
	switch (AnswerType)
	{
	case 3:
		//Remove All Wrong
		for (std::vector<Answer*>::iterator it = LocalAnswers.begin(); it != LocalAnswers.end();)
		{
			if ((*it)->sAnswer != sAnswer) it = LocalAnswers.erase(it);
			else  ++it;
		}
		// Then default Int Logic

	case 1: //INT VALUE
		std::sort(LocalAnswers.begin(), LocalAnswers.end(), compare_iAnswer);

		for (const auto& A : LocalAnswers)
		{
			int distance = std::abs(int(A->iAnswer - iAnswer)); // Berechne den Abstand

			// Falls der Abstand kleiner ist oder gleich ist, aber mit h�herem order
			if (distance < minDistance) {
				minDistance = distance; // Aktualisiere den minimalen Abstand
				result = A; // Setze das aktuelle Ergebnis
			}
			else if (distance == minDistance) {
				// Wenn die Abst�nde gleich sind, vergleiche die Order-Werte
				if (result != nullptr && A->tTime < result->tTime) {
					result = A; // Setze das Ergebnis, wenn der order kleiner ist
				}
			}
		}
		break;
	case 2:
	case 4:
		//Sort Time
		std::sort(LocalAnswers.begin(), LocalAnswers.end(), compare_tTime);
		//First with correct answer
		for (const auto& A : LocalAnswers)if (result == nullptr && A->sAnswer == sAnswer)result = A; 
		
		break;
	}

	

	MISE;
	return result;
}

void Question::Thread_Function()
{
	MISS;
	
	std::time_t tLastCheck = 0;
	Answer* Winner = nullptr;

	while (bRunning && (AnswerType != 4 && tStart + CountDown > Bro->L_getEEE_Now() || AnswerType == 4 && Winner == nullptr))
	{
		path p(Bro->L_getQuizPath() + "Q.txt");
		if (exists(p))
		{
			if (tLastCheck < last_write_time(p))
			{
				tLastCheck = last_write_time(p);
				LoadAnswers();
				Winner = getWinningAnswer();
			}
		}
		Sleep(10);

		if(AnswerType != 4)SetCountDown(tStart + CountDown - Bro->L_getEEE_Now());  //Count Down
		else SetCountDown(Bro->L_getEEE_Now() - tStart); //Count Up
	}

	if (AnswerType != 4)
	{
		SetCountDown(0);
		Twitch_Message(ID, "ultral34Booster ultral34Booster ultral34Booster ", "TIME IS UP");
		Sleep(1000);
		LoadAnswers();
	}
	else Twitch_Message(ID, "ultral34Booster ultral34Booster ultral34Booster ", "We have a winner");

	MISE;
}


void Question::LoadAnswers()
{
	MISS;
	std::string line;
	std::ifstream ifFile;

	std::string localsAnswer;
	int localiAnswer;

	ifFile.open(Bro->L_getQuizPath() + "Q.txt", std::ios::binary);
	if (!ifFile.good())
	{
		MISEA("Q.txt");
		return;
	}
	
	ifFile.seekg(lastQPos);
	
	bool Update;
	while (getline(ifFile, line))
	{
		if (line.length() <= 1)continue;

		Update = false;
		for (auto A : Answers)if (A->Pl->Twitch == entry(line, 0))
		{
			splitString(entry(line, 1).c_str(), localiAnswer, localsAnswer);

			if (   (AnswerType == 1 || AnswerType == 3) && A->iAnswer != localiAnswer
				|| (AnswerType == 2 || AnswerType == 3) && A->sAnswer != localsAnswer
				|| AnswerType == 4 && (A->iAnswer != localiAnswer || A->sAnswer != localsAnswer) && A->tTime + CoolDown < Bro->L_getEEE_Now())
			{
				if (SpellCheck(localsAnswer) == false)
				{
					Twitch_Message(entry(line, 0), "/w " + entry(line, 0) + " did you mean " + localsAnswer + "?");
				}
				else
				{
					A->iAnswer = localiAnswer;
					A->sAnswer = localsAnswer;
					A->tTime = Bro->L_getEEE_Now();
					Bro->Q->UpdateHTML();
				}
			}
			Update = true;
		}

		if (Update == false)
		{
			splitString(entry(line, 1).c_str(), localiAnswer, localsAnswer);
			if (SpellCheck(localsAnswer) == false)
			{
				Twitch_Message(entry(line, 0), "/w " + entry(line, 0) + " did you mean " + localsAnswer + "?");
			}
			else
			{
				Answers.push_back(new Answer(Bro->Q->GetPlayer(entry(line, 0)), localiAnswer, localsAnswer, Bro->L_getEEE_Now()));
				Bro->Q->UpdateHTML();
			}
		}

		ifFile.clear();
	}

	ifFile.clear();
	ifFile.seekg(0, std::ios::end);
	lastQPos = ifFile.tellg();
	
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
		for (auto A : Answers)ofFile << A->Pl->Twitch << ";" << A->iAnswer << ";" << A->sAnswer << ";" << A->tTime << ";" << std::endl;
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

std::string Question::CleanString(std::string text)
{
	MISS;
	std::string sReturn;
	int iTemp;
	splitString(text, iTemp, sReturn);
	MISE;
	return sReturn;
}

/*
void Question::splitString(const std::string& input, int& number, std::string& text) 
{
	MISS;
	std::stringstream ss(input);
	std::string temp;
	text.clear();
	number = 0;

	while (ss >> temp) 
	{
		
		bool isNumber = true;
		for (char c : temp) if (!std::isdigit(c)) 
		{
				isNumber = false;
				break;
		}

		if (isNumber) number = std::stoi(temp);		
		else for (char c : temp) if (std::isalpha(c)) text += std::toupper(c);
	}

	MISE;
}
*/
void Question::splitString(const std::string& input, int& number, std::string& text)
{
	MISS;

	text.clear();
	number = 0;

	// Regul�rer Ausdruck, um die erste durchgehende Zahlenfolge zu finden
	std::regex numberRegex("(\\d+)");
	std::smatch match;

	// Die erste Zahl im String suchen
	if (std::regex_search(input, match, numberRegex)) number = std::stoi(match.str());  // Die gefundene Zahl konvertieren
	
	// Nur die Buchstaben in Gro�buchstaben zum Text hinzuf�gen
	for (char c : input) if (std::isalpha(c)) text += std::toupper(c);

	MISE;
}


bool Question::SpellCheck(std::string& input)
{
	MISS;

	if(SpellCheckType==0)return true;
	std::string Orginput = input;

	
	switch (SpellCheckType)
	{

	case 2:
		if (input == "LS")input = "LOSTSOULS";
		else if (input == "TW")input = "TWILIGHT";
		else if (input == "SK")input = "STONEKIN";
		else if (input == "BD")input = "BANDITS";
		else if (input == "FF")input = "FIREFROST";
		else if (input == "NONE")input = "NEUTRAL";
		break;
	case 3:
		if (input == "SOULTREE")input = "THESOULTREE";
		else if (input == "TREASUREFLEET")input = "THETREASUREFLEET";
		else if (input == "TF")input = "THETREASUREFLEET";
		else if (input == "SOH")input = "SIEGEOFHOPE";
		else if (input == "DH")input = "DEFENDINGHOPE";
		else if (input == "SHARD")input = "NIGHTMARESHARD";
		else if (input == "INSANEGOD")input = "THEINSANEGOD";
		else if (input == "UV")input = "UNEXPECTEDVISITORS";
		else if (input == "ITJ")input = "INTOTHEJUNGLE";
		else if (input == "IJ")input = "INTOTHEJUNGLE";
		else if (input == "BH")input = "BADHARVEST";
		else if (input == "KOTG")input = "KINGOFTHEGIANTS";
		else if (input == "KOG")input = "KINGOFTHEGIANTS";
		else if (input == "DWARVENRIDDLE")input = "THEDWARVENRIDDLE";
		else if (input == "GOL")input = "THEGUNSOFLYR";
		else if (input == "GUNSOFLYR")input = "THEGUNSOFLYR";
		else if (input == "PTD")input = "PASSAGETODARKNESS";
		break;
	case 4:
		if (input == "ONE")input = "TIERONE";
		else if (input == "TWO")input = "TIERTWO";
		else if (input == "THREE")input = "TIERTHREE";
		else if (input == "FOUR")input = "TIERFOUR";
		break;

	}



	MISD("#2");
	std::string closestMatch;
	double highestScore = 0.0;

	for (const auto& word : CheckPool) {
		double score = rapidfuzz::fuzz::ratio(input, word);
		if (score > highestScore) 
		{
			highestScore = score;
			closestMatch = word;
		}
	}

	MISD("#3");
	if (closestMatch != input)
	{
		input = closestMatch;
		MISEA("no Match");
		return false;
	}

	MISEA("MATCH");
	return true;
}