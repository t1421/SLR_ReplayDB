#ifndef CardBase_H
#define CardBase_H

#include <fstream>
#include <vector>

#ifdef CardBaseUpdater
	#include <curl/curl.h>
	#ifdef __linux__
		#include <jsoncpp/json/json.h>
	#else
		#include <json/json.h>
	#endif
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

#ifdef CardBaseUpdater
	bool WEBtoSQL(bool bUpdate);
	bool IMGtoQSL(int iCardID, std::string sFile);
	bool Imager(int iCardID);
	bool DownloadPNG(int iCardID);
	std::string DownloadImage(int iCardID, std::string sCardName, bool bPromo);
	void UploadFromTemp(unsigned short CardID);
private:
	Json::Value GetJsonFromWeb();
	CURL *curl;
#endif

	public:
	unsigned char GetActionOrbForCardID(unsigned short CardID);

	std::vector<SQLCard*> SQLCardMatrix;

	bool bCardsLoaded;
	#ifndef noSQL
	bool LoadCardsFromSQL();
	#endif

	//BROKER
	static broker* Bro;
	void teachC() { Bro->C = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
protected:
	
};

#endif //CardBase_H

