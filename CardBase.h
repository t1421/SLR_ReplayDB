#ifndef CardBase_H
#define CardBase_H

#include <curl/curl.h>
#include <json/json.h>

struct SQLCard {
	unsigned short cardId;
	unsigned char  fireOrbs;
	unsigned char  frostOrbs;
	unsigned char  natureOrbs;
	unsigned char  shadowOrbs;
	unsigned char  neutralOrbs;

};

class CardBase
{
public:
	CardBase();
	~CardBase();

	bool WEBtoSQL(bool bUpdate);
	bool IMGtoQSL(int iCardID, string sFile);
	bool Imager(int iCardID);
	string DownloadImage(int iCardID, string sCardName, bool bPromo);

	
	unsigned char GetActionOrbForCardID(unsigned short CardID);

	//BROKER
	static broker* Bro;
	void teachC() { Bro->C = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:

private:
	Json::Value GetJsonFromWeb();
	CURL *curl;
	bool bCardsLoaded;
	bool LoadCardsFromSQL();

	vector<SQLCard*> SQLCardMatrix;
};

#endif //CardBase_H


