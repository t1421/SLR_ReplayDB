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
	bool Download(std::string sGameID);
	std::string DublettenCheck();
	
	std::string sEvent;
	
	static broker* Bro;
	//void teachP() { Bro->P = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	bool NewMasterData();
	std::string UploadHead();
	
	bool UploadActions(std::string iNewHeadID);
	bool UploadPlayers(std::string iNewHeadID);
	bool UploadPMVPlayerDeck(std::string iNewHeadID);
	bool PMVtoSQL(std::string iNewHeadID);

private:
	SQL_MIS_New * NN;
	Replay * RR;
};

#endif //PMV_to_SQL_H


