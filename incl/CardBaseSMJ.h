#ifndef CardBaseSMJ_H
#define CardBaseSMJ_H

#include <fstream>
#include <vector>


#include <curl/curl.h>
#ifdef __linux__
	#include <jsoncpp/json/json.h>
#else
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

class CardBaseSMJ
{
public:
	CardBaseSMJ();
	~CardBaseSMJ();


	std::string DownloadImage(int iCardID, std::string sCardName, bool bPromo);
	
private:
	Json::Value GetJsonFromWeb();
	CURL *curl;


	public:
	unsigned char GetActionOrbForCardID(unsigned short CardID);

	std::vector<SQLCard*> SQLCardMatrix;

	bool bCardsLoaded;

	//BROKER
	static broker* Bro;
	void teachJ() { Bro->J = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
protected:
	
};

#endif //CardBase_H


