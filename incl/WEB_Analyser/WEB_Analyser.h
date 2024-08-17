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
struct Lotto_Player;

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
	int TomeAnalyser(Wt::WTable *wtReplayResultCard, unsigned int iGameID);
#endif

#if defined BrokerLotto
	Lotto_Player *getLottoPlayer();
#endif

	unsigned long long getPMVPlayerID();

	std::vector <Player*> Players;
	std::vector <ActionSum*> ActionSums;
	std::vector <ActionWeb*> Actions;
	
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	bool SaveReplay(std::string sFile);
	bool NewReplay(std::string sFile);
	bool getData();
	std::string GetPlayerName(unsigned long inPlayer);
	unsigned long long getPlaytime();
	unsigned long getReplayHash();
	std::string getMapName();
	Replay* R;

	WEB_Analyser();
	void ReNewTaps();

	bool isOK();

	bool WA_Debug;
	bool WA_Admin;
	
	//std::string Kalk_BOT6(Wt::WTable *wtTabelle, unsigned long iTimes[RankRowStamps]);
	std::string Kalk_EEE0(unsigned long iTimes[RankRowStamps]);
	std::string Kalk_EEE_Def(unsigned long iTimes[RankRowStamps], std::string sMapName);
	std::string Kalk_EEE2(unsigned long iTimes[RankRowStamps]);
	std::string Kalk_EEE3(unsigned long iTimes[RankRowStamps]);
	std::string Kalk_EEE5(unsigned long iTimes[RankRowStamps]);
	std::string Kalk_EEE7(unsigned long iTimes[RankRowStamps]);

	std::string Kalk_Event0(unsigned long iTimes[RankRowStamps]);

	bool isEEEwin();
	unsigned long long usedPower();

	void AddIMG(Wt::WTableCell *wtCell, bool bValue);
	
	std::string GetTeamID();	

	private:
};


#endif // WEB_Analyser
