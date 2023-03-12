#ifndef WEB_Analyser_H
#define WEB_Analyser_H

class WEB_Analyser_Head;
class WEB_Analyser_Deck;
class WEB_Analyser_Acti;
class Replay;
struct Player;
struct ActionSum;
struct ActionWeb;

#include <Wt/WTable.h>


class WEB_Analyser 
{
public:

	WEB_Analyser_Head *Head;
	WEB_Analyser_Deck *Deck;
	WEB_Analyser_Acti *Acti;

	unsigned long long getPMVPlayerID();

	std::vector <Player*> Players;
	std::vector <ActionSum*> ActionSums;
	std::vector <ActionWeb*> Actions;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	bool NewReplay(std::string sFile);
	bool getData();
	std::string GetPlayerName(unsigned long inPlayer);
	Replay* R;

	WEB_Analyser();

	bool isOK();

	std::string  Check_BOT3();
	unsigned int  Kalk_BOT3(Wt::WTable *wtTabelle);
};


#endif // WEB_Analyser
