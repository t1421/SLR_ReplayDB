#ifndef Question_H
#define Question_H

#include "Thread_MIS.h"
#include "Quiz.h"
/*
class Question;
class Demon_Answers : public Thread_MIS
{
public:
	Question* QQ;
	Demon_Answers(Question* _QQ);
	void Thread_Function();
};
*/

#define CountDown 60

struct Answer
{
	Answer(Player* _Pl, int _iAnswer, unsigned long int _tTime) :Pl(_Pl), iAnswer(_iAnswer), tTime(_tTime){};
	//std::string Twitch;
	Player* Pl;
	int iAnswer;
	unsigned long int tTime;
};

class Question : public Thread_MIS
{
public:
	Question(std::string _ID, std::string _Titel, std::string _Question_Twitch, int _iAnswer);
	~Question();

	std::string ID;
	std::string Titel;
	std::string Question_Twitch;
	int iAnswer;
	std::vector <Answer*> Answers;

	void echo();
	void Start();
	void Stop() { bRunning = false; };
	void Winner();

	void ResetAnswers();
	void LoadAnswers();
	void SaveAnswers();

	//BROKER
	static broker* Bro;
	static void learnBro(broker* _Bro) { Bro = _Bro; }

private:
	unsigned long int tStart;
	void Thread_Function();
	void SetCountDown(unsigned int iii);

	Answer* getWinningAnswer();
	

	//Demon_Answers* DA;


};
#endif //Question_H


