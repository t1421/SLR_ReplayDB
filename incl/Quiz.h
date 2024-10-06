#ifndef Quiz_H
#define Quiz_H

#include "Thread_MIS.h"

class Question;
/*
class Quiz;
class Demon_Player : public Thread_MIS
{
public:
	Quiz* QQ;
	Demon_Player(Quiz* _QQ);
	void Thread_Function();
};
*/

struct Player
{
	std::string Twitch;
	std::string Ingame;
	Player(std::string _Twitch, std::string _Ingame, std::string _WonID): Twitch(_Twitch), Ingame(_Ingame), WonID(_WonID){};
	std::string WonID;
};

class Quiz : public Thread_MIS
{
public:
	Quiz();
	~Quiz();

	void Init();
	void Start(unsigned int iQuestion);
	void Winner(unsigned int iQuestion);
	void Winner() { Winner(ActivQuiz); };

	//BROKER
	static broker* Bro;
	void teachQ() { Bro->Q = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }


	unsigned int ActivQuiz;
	std::vector <Question*> vQuestion;
	void LoadPlayers(std::string sName);
	bool CheckPlayerName(std::string sName);
	bool CheckPlayerWon(std::string sName);

private:
	std::vector<Player*> Players;
	

	void LoadPlayers();

	void SavePlayers();
	void AddUpdatePlayers(std::string _Twitch, std::string _Ingame, std::string _WonID);

	void Load_Question();

	void Thread_Function();

	//Demon_Player* DP;
	
};



#endif //Quiz



