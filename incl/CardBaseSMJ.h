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

#include "DataTypes.h" 

class CardBaseSMJ
{
public:
	CardBaseSMJ();
	~CardBaseSMJ();

	void DownloadImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, bool bSmall);
	
private:
	Json::Value SMJtoCHASH();
	CURL *curl;

public:
	unsigned char GetActionOrbForCardID(unsigned short CardID);	

	unsigned char SwitchCharges(unsigned short CardID, unsigned char IstCharges);

	SMJCard* GetSMJCard(unsigned short _CardID);

	void EchoCard(std::string sCardID);
	std::vector<SMJCard*> SMJMatrix;
	std::string GetImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, bool bSmall, bool bSW);
	//std::string GetSWImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, bool bSmall);
	void ConvertImage(std::string sFile);
	void AllIMG();
	bool Init();

	//BROKER
	static broker* Bro;
	void teachJ() { Bro->J = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
protected:
	
};

#endif //CardBase_H


