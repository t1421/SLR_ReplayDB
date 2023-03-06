#ifndef WEB_Analyser_H
#define WEB_Analyser_H

class WEB_Analyser_Head;
class WEB_Analyser_Deck;
class WEB_Analyser_Acti;
class Replay;
struct Player;
struct ActionSum;
struct ActionWeb;



class WEB_Analyser 
{
public:

	WEB_Analyser_Head *Head;
	WEB_Analyser_Deck *Deck;
	WEB_Analyser_Acti *Acti;

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
};


#endif // WEB_Analyser
