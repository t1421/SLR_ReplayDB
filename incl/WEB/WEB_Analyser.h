#ifndef WEB_Analyser_H
#define WEB_Analyser_H

class WEB_Analyser_Head;
class WEB_Analyser_Deck;
class WEB_Analyser_Acti;
class Replay;
class Player;
class ActionSum;




class WEB_Analyser 
{
public:

	WEB_Analyser_Head *Head;
	WEB_Analyser_Deck *Deck;
	WEB_Analyser_Acti *Acti;

	std::vector <Player*> Players;
	std::vector <ActionSum*> ActionSums;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	bool NewReplay(std::string sFile);
	bool getData();
	Replay* R;

	WEB_Analyser();

	bool isOK();
};


#endif // WEB_Analyser
