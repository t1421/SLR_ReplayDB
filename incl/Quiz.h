#ifndef Quiz_H
#define Quiz_H

#include "Thread_MIS.h"

struct Player
{
	std::string Twitch;
	std::string Ingame;
	Player(std::string _Twitch, std::string _Ingame): Twitch(_Twitch), Ingame(_Ingame){};
};

class Quiz : public Thread_MIS
{
public:
	Quiz();
	~Quiz();

	void Init();

	//BROKER
	static broker* Bro;
	void teachQ() { Bro->Q = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:
	std::vector<Player*> Players;

	void LoadPlayers();
	void LoadPlayers(std::string sName);
	void SavePlayers();
	bool AddUpdatePlayers(std::string _Twitch, std::string _Ingame);

	void Thread_Function();

	
};

#endif //Quiz


