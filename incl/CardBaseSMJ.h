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

struct SMJCard {
	unsigned short cardId;
	std::string SMJid;
	std::string cardName;
	char color;
	unsigned char orbsTotal;
	unsigned char orbsNeutral;
	unsigned char orbsFire;
	unsigned char orbsShadow;
	unsigned char orbsNature;
	unsigned char orbsFrost;
	unsigned char orbsFireShadow;
	unsigned char orbsNatureFrost;
	unsigned char orbsFireNature;
	unsigned char orbsShadowFrost;
	unsigned char orbsShadowNature;
	unsigned char orbsFireFrost;
	unsigned char type;
	unsigned char maxCharges;
};

class CardBaseSMJ
{
public:
	CardBaseSMJ();
	~CardBaseSMJ();

	std::string DownloadImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges);
	
private:
	Json::Value SMJtoCHASH();
	CURL *curl;

public:
	unsigned char GetActionOrbForCardID(unsigned short CardID);

	unsigned char SwitchCharges(unsigned short CardID, unsigned char IstCharges);

	void EchoCard(std::string sCardID);
	std::vector<SMJCard*> SMJMatrix;
	std::string GetImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges);

	bool Init();

	//BROKER
	static broker* Bro;
	void teachJ() { Bro->J = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
protected:
	
};

#endif //CardBase_H


