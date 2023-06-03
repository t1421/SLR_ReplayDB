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
	unsigned long long getPlaytime();
	Replay* R;

	WEB_Analyser();
	void ReNewTaps();

	bool isOK();

	bool WA_Debug;

	std::string  Check_BOT3();
	double Kalk_BOT3(Wt::WTable *wtTabelle);

	std::string Kalk_BOT4(Wt::WTable *wtTabelle);
	void AddIMG(Wt::WTableCell *wtCell, bool bValue);

	std::string Kalk_KOTG(Wt::WTable *wtTabelle[3], unsigned long iTimes[4]);
	std::string GetTeamID();

	private:
		double SwitchType(unsigned char ucType) 
		{
			switch (ucType)
			{
			case(0): return 2.00;
			case(1): return 1.50;
			case(2): return 1.00;
			}
		};
};


#endif // WEB_Analyser
