#ifndef CardBaseSMJ_H
#define CardBaseSMJ_H

#include <fstream>
#include <vector>


#include <curl/curl.h>
#include <json/json.h>

#include "DataTypes.h" 



class CardBaseSMJ
{
public:
	CardBaseSMJ();
	~CardBaseSMJ();
	bool Init();
	
	std::vector<std::pair<std::string, std::string>> EnumColor;
	std::vector<std::pair<std::string, std::string>> EnumRarity;
	std::vector<std::pair<std::string, std::string>> EnumAffinity;
	std::vector<std::pair<std::string, std::string>> EnumType;
	std::vector<std::pair<std::string, std::string>> EnumBoosters;
	std::vector<std::pair<std::string, std::string>> EnumUpgradeMaps;
	std::vector<std::pair<std::string, std::string>> EnumTier;
	std::vector<std::pair<std::string, std::string>> EnumDifficulty;
	std::vector<std::pair<std::string, std::string>> EnumDirections;
private:
	Json::Value WEBRequestToCHASH(std::string sURL);
	CURL *curl;
	std::mutex mutex_WEBRequest;
	
public:
	unsigned char GetActionOrbForCardID(unsigned short CardID);	

	unsigned char SwitchCharges(unsigned short CardID, unsigned char IstCharges);
	std::string SwitchAffinity(char _Affinity);
	std::string SwitchColor(char _Color);
	std::string SwitchRarity(char _Rarity);
	SMJCard* GetSMJCard(unsigned short _CardID);
	//Tome_Booster* OpenBooster(std::string iType);
	Tome_Booster* OpenBooster(std::string iType, bool bNoDouble, std::vector<Tome_Booster*> vOpendBooster);
	unsigned int J_GetSMJPower(unsigned short iCard, unsigned short iUpgrade);

	void EchoCard(std::string sCardID);
	std::vector<SMJCard*> SMJMatrix;

#ifndef noSMJImages
	void DownloadImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, SMJPicType _Type);

	std::string GetImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, SMJPicType _Type, bool bSW);
	void ConvertImage(std::string sFile);
	void AllIMGBig();
	void AllIMGBigSW();
	void AllIMGSmall();
	void AllIMGImgOnly();
	void AllIMGSimpel();
	
#endif
	
	

#ifndef noSQL
	bool SMJtoSQL(bool bUpdate);
	bool IMGtoQSL(int iCardID);
	bool Imager();
#endif

	//BROKER
	static broker* Bro;
	void teachJ() { Bro->J = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }



	
protected:
	
};

#endif //CardBase_H


