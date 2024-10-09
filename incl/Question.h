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
#define CoolDown 30

struct Answer
{
	Answer(Player* _Pl, int _iAnswer, std::string _sAnswer, unsigned long int _tTime) :Pl(_Pl), iAnswer(_iAnswer), sAnswer(_sAnswer), tTime(_tTime) {};
	Player* Pl;
	int iAnswer;
	std::string sAnswer;
	unsigned long int tTime;
};

class Question : public Thread_MIS
{
public:
	Question(std::string _ID, std::string _Titel, std::string _Question_Twitch, int _iAnswer, std::string _sAnswer,	unsigned int _AnswerType,unsigned int _SpellCheck);
	~Question();

	std::string ID;
	std::string Titel;
	std::string Question_Twitch;
	int iAnswer;
	std::string sAnswer;
	unsigned int AnswerType;
	unsigned int SpellCheck;
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
	void splitString(const std::string& input, int& number, std::string& text);

	Answer* getWinningAnswer();
	

	//Demon_Answers* DA;


};
#endif //Question_H


