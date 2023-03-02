#ifndef Replay_H
#define Replay_H

#include "Reader.h" 
#include "DataTypes.h" 
#ifdef __linux__
#include <tgmath.h> 
#endif


//#include <sstream>


//unsigned char			/// 8
//unsigned short		///16
//unsigned long			///32
//unsigned long long	///64

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


