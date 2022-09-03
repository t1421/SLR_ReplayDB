#ifndef CardBase_H
#define CardBase_H

#ifdef BrokerNormal
	#include <curl/curl.h>
	#include <json/json.h>
#endif
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
	bool DownloadPNG(int iCardID);
	string DownloadImage(int iCardID, string sCardName, bool bPromo);

	
	unsigned char GetActionOrbForCardID(unsigned short CardID);

	vector<SQLCard*> SQLCardMatrix;

	bool bCardsLoaded;
	bool LoadCardsFromSQL();

	//BROKER
	static broker* Bro;
	void teachC() { Bro->C = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
protected:

private:
#ifdef BrokerNormal
	Json::Value GetJsonFromWeb();
	CURL *curl;
#endif
	

	
};

#endif //CardBase_H


