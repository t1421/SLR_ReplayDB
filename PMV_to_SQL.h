#ifndef PMV_to_SQL_H
#define PMV_to_SQL_H

class Replay;

class PMV_to_SQL
{
public:
	PMV_to_SQL();
	~PMV_to_SQL();

	bool UseThisPMV(Replay * inReplay);
	void UseThisSQL(SQL_MIS_New * inSQL);

	bool Upload();
	bool Download(string sGameID);
	string DublettenCheck();
	
	string sEvent;
	
	static broker* Bro;
	//void teachP() { Bro->P = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	bool NewMasterData();
	string UploadHead();
	
	bool UploadActions(string iNewHeadID);
	bool UploadPlayers(string iNewHeadID);
	bool UploadPMVPlayerDeck(string iNewHeadID);
	bool PMVtoSQL(string iNewHeadID);

private:
	SQL_MIS_New * NN;
	Replay * RR;
};

#endif //PMV_to_SQL_H


