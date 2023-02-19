#ifndef Replay_H
#define Replay_H

#include "Reader.h" 
#ifdef __linux__
#include <tgmath.h> 
#endif

#include <sstream>

//unsigned char			/// 8
//unsigned short		///16
//unsigned long			///32
//unsigned long long	///64

struct Allied {
	unsigned char i;
	unsigned char j;
	unsigned char v;
};

struct Team {
	std::string Name;
	unsigned long GroupID;
	unsigned short Value;
};

struct Card {
	unsigned short DeckCardID;
	unsigned long  CardFull;
	unsigned short CardID;
	unsigned short Upgrade;
	unsigned char  Charges;
	unsigned long  count;
};

struct Player {
	std::string Name;
	unsigned long long PlayerID;
	unsigned long ActionPlayer;
	unsigned char GroupID;
	unsigned char IDinGroup;
	unsigned char Type;
	unsigned char Cards;
	unsigned char CardsTotal;
	std::vector <Card*> Deck;
};

struct Action {
	unsigned long Time;
	//unsigned long Size;

	unsigned long Type;
	unsigned long Card;
	unsigned long Upgrade;
	unsigned long CardFull;

	unsigned long ActionPlayer;
	unsigned long long PlayerID;
	unsigned char Charges;

	unsigned int Position;

	std::string AdditionalInfo;

	Action():Time(0), Type(0), Card(0), Upgrade(0), CardFull(0), ActionPlayer(0), PlayerID(0), Charges(0), AdditionalInfo()
	{}

	//unsigned long Unit;
	//unsigned short UnitCount;

	//unsigned short Cardx;
	//unsigned short Cardy;
	//unsigned short Cardz;

	//unsigned long X;
	//unsigned long Y;
	//unsigned long Zero;

	//unsigned char Unknow8;

};

class Replay : private Reader
{
public:
	Replay();
	~Replay();

	bool OK;	

	bool LoadPMV(std::string sFile);
	void EchoHead();
	void EchoAllied();
	void EchoTeam();
	void EchoPlayer();
	void EchoPlayerDecks();
	void EchoAction(std::string sAction);
	std::string SwitchType(unsigned long inType);
	int CountActions(std::string sAction);
	int CountActions() { return CountActions("*"); }

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	unsigned char GroupCount;
	unsigned char Unknow3;
	unsigned char Unknow4;
	unsigned char DifficultyID; // Std=1,Adv=2,Exp=3,PVR1=5 ...
	unsigned long FileVersion;
	unsigned long GameVersion;
	unsigned long Playtime;
	unsigned long Seed;
	unsigned long ActionBlock;
	unsigned long MapID; 
	unsigned short PlayModeID; // PvE = 1 / PvP = 2		
	unsigned short MatrixCount;
	unsigned short TeamCount;
	unsigned long long PMVPlayerID;
	unsigned long MinLeaveGame;
	std::vector<Allied*> AlliedMatrix;
	std::vector<Team*> TeamMatrix;
	std::vector<Player*> PlayerMatrix;
	std::vector<Action*> ActionMatrix;
	std::string MapName;
	std::string FileName;
	std::string WinningTeam;

	std::stringstream ssPMVFile;
	std::string sSQLGameID;
protected:

private:
	bool ReadHeader();
	bool ReadActions();
	bool ConnectActionToPlayer();
	bool AddFirstOrb();
	bool SetMinLeaveTime();
	bool SetCharges();
	bool FillPlayerIDInAction();
	bool getPMVinSS(std::string sFile);
	std::string FindWinningTeam();
	std::string get_file_name(std::string pfad);
	

};

#endif //Replay_H


