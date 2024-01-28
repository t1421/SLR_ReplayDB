#ifndef WEB_Analyser_H
#define WEB_Analyser_H

#if defined BrokerWeb
class WEB_Analyser_Head;
class WEB_Analyser_Deck;
class WEB_Analyser_Acti;
#endif
class Replay;
struct Player;
struct ActionSum;
struct ActionWeb;

#include <Wt/WTable.h>



class WEB_Analyser 
{
public:

#if defined BrokerWeb
	WEB_Analyser_Head *Head;
	WEB_Analyser_Deck *Deck;
	WEB_Analyser_Acti *Acti;
#endif

#if defined BrokerTome
	//bool TomeAnalyser(Wt::WTable *wtReplayResultCard, unsigned int iGameID);
#endif

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
	unsigned long getReplayHash();
	Replay* R;

	WEB_Analyser();
	void ReNewTaps();

	bool isOK();

	bool WA_Debug;

	//std::string Kalk_BOT4(Wt::WTable *wtTabelle, Wt::WTable *wtInfos, unsigned long iTimes[RankRowStamps]);
	std::string Kalk_BOT6(Wt::WTable *wtTabelle, unsigned long iTimes[RankRowStamps]);
	void AddIMG(Wt::WTableCell *wtCell, bool bValue);
	
	std::string GetTeamID();	

	private:
		/*
		double SwitchType(unsigned char ucType) 
		{
			switch (ucType)
			{
			case(0): return 2.00;
			case(1): return 1.50;
			case(2): return 1.00;
			}
		};*/
};


#endif // WEB_Analyser
