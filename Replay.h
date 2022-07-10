#ifndef Replay_H
#define Replay_H

#include "Reader.h" 

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
	string Name;
	unsigned long GroupID;
	unsigned short Value;
};

struct Card {
	unsigned short DeckCardID;
	unsigned long  CardFull;
	unsigned short CardID;
	unsigned short Upgrade;
	unsigned char  Charges;
};

struct Player {
	string Name;
	unsigned long long PlayerID;
	unsigned long ActionPlayer;
	unsigned char GroupID;
	unsigned char IDinGroup;
	unsigned char Type;
	unsigned char Cards;
	unsigned char CardsTotal;
	vector <Card*> Deck;
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
	
	unsigned char Color;

	unsigned int Position;

	Action():Time(0), Type(0), Card(0), Upgrade(0), CardFull(0), ActionPlayer(0), PlayerID(0), Charges(0), Color(0)
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

	bool LoadPMV(string sFile);
	void EchoHead();
	void EchoAllied();
	void EchoTeam();
	void EchoPlayer();
	void EchoPlayerDecks();
	void EchoAction(string sAction);

	//BROKER
#ifndef noBroker
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }
#endif

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
	vector<Allied*> AlliedMatrix;
	vector<Team*> TeamMatrix;
	vector<Player*> PlayerMatrix;
	vector<Action*> ActionMatrix;
	string MapName;
	string FileName;
	string WinningTeam;

	stringstream ssPMVFile;
	string sSQLGameID;
protected:

private:
	bool ReadHeader();
	bool ReadActions();
	bool ConnectActionToPlayer();
	bool AddFirstOrb();
	bool SetMinLeaveTime();
	bool SetCharges();
	bool FillPlayerIDInAction();
	bool getPMVinSS(string sFile);
	string FindWinningTeam();
	string get_file_name(string pfad);
	string sTime(unsigned long ulTime);

};

#endif //Replay_H


