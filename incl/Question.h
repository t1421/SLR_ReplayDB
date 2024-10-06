#ifndef Question_H
#define Question_H

#include "Thread_MIS.h"
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

#define CountDown 30

struct Answer
{
	Answer(std::string _Twitch, int _iAnswer, unsigned long int _tTime) :Twitch(_Twitch), iAnswer(_iAnswer), tTime(_tTime){};
	std::string Twitch;
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
	std::vector <Answer*> Answers;

	//Demon_Answers* DA;


};
#endif //Question_H


