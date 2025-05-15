//#define DF_Debug

#include "..\incl\Broker.h" 

#define SMJ_Cards "https://smj.cards/api/cards"
#define SMJ_I_BOOSTER "https://smj.cards/api/random/booster"
#define SMJ_S_IMG "https://smj.cards/api/images/basicCard/"
#define SMJ_B_IMG "https://smj.cards/api/images/fullCard/"
#define SMJ_I_IMG "https://smj.cards/api/images/cardArtwork/"


#include "..\incl\CardBaseSMJ.h" 
#include "..\incl\Utility.h" 
#ifndef noSQL
#include "..\incl\SQL_MIS_New.h"
#endif

#ifndef noSMJImages
#include <opencv2/opencv.hpp>
#endif
#include <random>
#include <boost/algorithm/string.hpp>

broker *(CardBaseSMJ::Bro) = NULL;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

static size_t FileCallback(void* buf, size_t size, size_t nmemb, void* userp)
{
	if (userp)
	{
		std::ostream& os = *static_cast<std::ostream*>(userp);
		std::streamsize len = size * nmemb;
		if (os.write(static_cast<char*>(buf), len))	return len;
	}
	return 0;
}


CardBaseSMJ::CardBaseSMJ()
{
	MISS;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	MISE;
}

CardBaseSMJ::~CardBaseSMJ()
{
	MISS;
	curl_global_cleanup();
	MISE;
}

bool CardBaseSMJ::Init()
{
	
	MISS;
	Json::Value RawData;
	Json::Value AllCards;
	Json::Value Card;
	Json::Value jTEMP;

	Json::Value Enum;

	SMJCard * SMJCard_TEMP;

	RawData = WEBRequestToCHASH(SMJ_Cards);
	AllCards = RawData["data"];
	
	MISD("AllCards:" + std::to_string(AllCards.size()));
	for (Json::ArrayIndex i = 0; i < AllCards.size(); i++)
	{
		Card = AllCards[i];
		SMJCard_TEMP = new SMJCard();		
		SMJCard_TEMP->SMJid = Card["_id"].asString();
		SMJCard_TEMP->cardName = Card["cardName"].asString();
		SMJCard_TEMP->color = Card["color"].asInt();
		SMJCard_TEMP->orbsTotal = Card["orbsTotal"].asInt();
		SMJCard_TEMP->orbsNeutral = Card["orbsNeutral"].asInt();
		SMJCard_TEMP->orbsFire = Card["orbsFire"].asInt();
		SMJCard_TEMP->orbsShadow = Card["orbsShadow"].asInt();
		SMJCard_TEMP->orbsNature = Card["orbsNature"].asInt();
		SMJCard_TEMP->orbsFrost = Card["orbsFrost"].asInt();
		SMJCard_TEMP->orbsFireShadow = Card["orbsFireShadow"].asInt();
		SMJCard_TEMP->orbsNatureFrost = Card["orbsNatureFrost"].asInt();
		SMJCard_TEMP->orbsFireNature = Card["orbsFireNature"].asInt();
		SMJCard_TEMP->orbsShadowFrost = Card["orbsShadowFrost"].asInt();
		SMJCard_TEMP->orbsShadowNature = Card["orbsShadowNature"].asInt();
		SMJCard_TEMP->orbsFireFrost = Card["orbsFireFrost"].asInt();
		SMJCard_TEMP->type = Card["type"].asInt();
		SMJCard_TEMP->maxCharges = Card["maxCharges"].asInt();
		SMJCard_TEMP->affinity = Card["affinity"].asInt();
		SMJCard_TEMP->cardNameSimple = Card["cardNameSimple"].asString();
		SMJCard_TEMP->rarity = Card["rarity"].asInt();
		SMJCard_TEMP->promo = Card["promo"].asInt();
		
		
		
		
		jTEMP = Card["officialCardIds"];
		//IDs i = 0; i < AllCards.size(); i++)
		SMJCard_TEMP->cardId = jTEMP[jTEMP.size() - 1].asInt();

		jTEMP = Card["powerCost"];
		for (unsigned int iPower = 0; iPower < jTEMP.size(); iPower++ )
			SMJCard_TEMP->powerCost[iPower] = jTEMP[iPower].asInt();	

		jTEMP = Card["boosters"];
		for (unsigned int iBoosters = 0; iBoosters < jTEMP.size(); iBoosters++)
			SMJCard_TEMP->vBoosters.push_back(jTEMP[iBoosters].asInt());

		SMJMatrix.push_back(SMJCard_TEMP);
	}
	for (SMJCard* CC : SMJMatrix)if (CC->cardNameSimple == "Kobold Inc.")CC->cardNameSimple = "Kobold Inc"; 
	for (SMJCard* CC : SMJMatrix)if (CC->cardId == 529)CC->maxCharges = 16;
	
	AllCards = RawData["enums"];
	
	Enum = AllCards["color"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumColor.push_back(std::make_pair(
			id, Enum[id].asString()));
	}

	Enum = AllCards["rarity"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumRarity.push_back(std::make_pair(
			id, Enum[id].asString()));
	}

	Enum = AllCards["affinity"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumAffinity.push_back(std::make_pair(
			id, Enum[id].asString()));
	}

	Enum = AllCards["type"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumType.push_back(std::make_pair(
			id, Enum[id].asString()));
	}

	Enum = AllCards["boosters"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumBoosters.push_back(std::make_pair(
			id, Enum[id].asString()));
	}

	Enum = AllCards["upgradeMaps"];
	for (auto const& id : Enum.getMemberNames())
	{
		EnumUpgradeMaps.push_back(std::make_pair(
			id, Enum[id].asString()));
	}
	EnumUpgradeMaps.push_back(std::make_pair(
		"XXX", "Passage to Darkness"));
	EnumUpgradeMaps.push_back(std::make_pair(
		"YYY", "Ascension"));

	EnumTier.push_back(std::make_pair(
		"1", "TierOne"));
	EnumTier.push_back(std::make_pair(
		"2", "TierTwo"));
	EnumTier.push_back(std::make_pair(
		"3", "TierThree "));
	EnumTier.push_back(std::make_pair(
		"4", "TierFour"));
	
	EnumDifficulty.push_back(std::make_pair(
		"1", "Standard"));
	EnumDifficulty.push_back(std::make_pair(
		"2", "Advanced"));
	EnumDifficulty.push_back(std::make_pair(
		"3", "Expert "));	

	MISE;
	
	return true;	
}


void CardBaseSMJ::EchoCard(std::string sCardID)
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		//MISD(std::to_string(SMJMatrix[i]->cardId));
		if (SMJMatrix[i]->cardId == atoi(sCardID.c_str()))
		{
			printf("cardId:            %lu\n", SMJMatrix[i]->cardId);
			printf("SMJid:             %s\n",  SMJMatrix[i]->SMJid.c_str());
			printf("cardName:          %s\n",  SMJMatrix[i]->cardName.c_str());
			printf("color:             %i\n",  SMJMatrix[i]->color);
			printf("orbsTotal:         %lu\n", SMJMatrix[i]->orbsTotal);
			printf("orbsNeutral:       %lu\n", SMJMatrix[i]->orbsNeutral);
			printf("orbsFire:          %lu\n", SMJMatrix[i]->orbsFire);
			printf("orbsShadow:        %lu\n", SMJMatrix[i]->orbsShadow);
			printf("orbsNature:        %lu\n", SMJMatrix[i]->orbsNature);
			printf("orbsFrost:         %lu\n", SMJMatrix[i]->orbsFrost);
			printf("orbsFireShadow:    %lu\n", SMJMatrix[i]->orbsFireShadow);
			printf("orbsNatureFrost:   %lu\n", SMJMatrix[i]->orbsNatureFrost);
			printf("orbsFireNature:    %lu\n", SMJMatrix[i]->orbsFireNature);
			printf("orbsShadowFrost:   %lu\n", SMJMatrix[i]->orbsShadowFrost);
			printf("orbsShadowNature:  %lu\n", SMJMatrix[i]->orbsShadowNature);
			printf("orbsFireFrost:     %lu\n", SMJMatrix[i]->orbsFireFrost);
			printf("type:              %lu\n", SMJMatrix[i]->type);
			printf("maxCharges:        %lu\n", SMJMatrix[i]->maxCharges);
			
			break;
		}
	}
	MISE;
}


Json::Value CardBaseSMJ::WEBRequestToCHASH(std::string sURL)
{
	MISS;
	
	mutex_WEBRequest.lock();
	CURLcode res;
	long httpCode(0);

	Json::Value jsonData;
	Json::Reader jsonReader;

	std::string readBuffer = "";

	MISD("#1");
	curl = curl_easy_init();
	if (curl)
	{
		MISD("#2");
		curl_easy_setopt(curl, CURLOPT_URL, sURL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)Bro->B_StatusE("E", "GetJsonFromWeb - curl_easy_perform", curl_easy_strerror(res));
		
		MISD("#2");
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (httpCode == 200)
		{
			MISD("#3");
			if (jsonReader.parse(readBuffer, jsonData))
			{
				MISD("Json Request - Sucess")
			}
			else Bro->B_StatusE("E", "GetJsonFromWeb - jsonReader.parse", "");
		}
		else Bro->B_StatusE("E", "GetJsonFromWeb - httpCode", std::to_string(httpCode));

		curl_easy_cleanup(curl);
	}
	MISD("#4");
	mutex_WEBRequest.unlock();

	MISE;
	return jsonData;
}

unsigned char CardBaseSMJ::GetActionOrbForCardID(unsigned short CardID)
{
	MISS;

	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == CardID)
		{
			MISE;
			if (SMJMatrix[i]->color == 0) return 4;
			else return SMJMatrix[i]->color;
		}
	}

	MISEA("Canft Find Card");
	return 99;
}


unsigned char CardBaseSMJ::SwitchCharges(unsigned short CardID, unsigned char IstCharges)
{
	MISS;

	unsigned char MaxChages = 0;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == CardID)
		{
			MaxChages = SMJMatrix[i]->maxCharges;
			break;
		}
	}
	//MISERROR(std::to_string(MaxChages));
	switch (MaxChages)
	{
	case 4: switch (IstCharges)
	{
	case 1: return 0;
	case 2: return 1;
	case 3: return 2;
	case 4: return 3;
	}
	case 8: switch (IstCharges)
	{
	case 4: return 0;
	case 6: return 1;
	case 7: return 2;
	case 8: return 3;
	}
	case 12: switch (IstCharges)
	{
	case 6: return 0;
	case 8: return 1;
	case 10: return 2;
	case 12: return 3;
	}
	case 16: switch (IstCharges)
	{
	case 8: return 0;
	case 11: return 1;
	case 14: return 2;
	case 16: return 3;
	}
	case 20: switch (IstCharges)
	{
	case 10: return 0;
	case 14: return 1;
	case 17: return 2;
	case 20: return 3;
	}
	case 24: switch (IstCharges)
	{
	case 12: return 0;
	case 16: return 1;
	case 20: return 2;
	case 24: return 3;
	}
	}

	MISE;
	return 99;
}


std::string CardBaseSMJ::SwitchAffinity(char _Affinity)
{
	for (unsigned int i = 0; i < EnumAffinity.size(); i++)
		if (EnumAffinity[i].first == std::to_string(_Affinity))return EnumAffinity[i].second;
	
	return "???";
}
std::string CardBaseSMJ::SwitchColor(char _Color)
{
	for (unsigned int i = 0; i < EnumColor.size(); i++)
		if (EnumColor[i].first == std::to_string(_Color))return EnumColor[i].second;

	return "???";
}
std::string CardBaseSMJ::SwitchRarity(char _Rarity)
{
	for (unsigned int i = 0; i < EnumRarity.size(); i++)
		if (EnumRarity[i].first == std::to_string(_Rarity))return EnumRarity[i].second;

	return "???";
}

SMJCard* CardBaseSMJ::GetSMJCard(unsigned short _CardID)
{
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == _CardID)return SMJMatrix[i];
	}

	return new SMJCard();
}

#ifndef noSMJImages
void CardBaseSMJ::DownloadImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, SMJPicType _Type)
{
	MISS;

	std::ofstream OutFile;
	CURLcode res;
	long httpCode(0);
	std::string sURL;
	std::string SMJID;
	std::string SMJColor;
	std::string SMJName;
	std::string sFile = std::to_string(CardID) + "_" + std::to_string(Upgrade) + std::to_string(Charges);


	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == CardID)
		{
			SMJID = SMJMatrix[i]->SMJid;
			SMJColor = std::to_string(SMJMatrix[i]->color);
			SMJName = SMJMatrix[i]->cardNameSimple;
			break;
		}
	}


#ifndef noLoad
	switch (_Type)
	{
	case ImgOnly:
		sURL = SMJ_I_IMG;
		sURL += std::to_string(CardID);
		OutFile.open(Bro->L_getSMJIMG_PATH() + sFile + ".webp", std::ostream::binary);
		break;
	case Small:
		sURL = SMJ_S_IMG;
		sURL += SMJID;
		OutFile.open(Bro->L_getSMJPICSMALL_PATH() + sFile + ".webp", std::ostream::binary);
		break;
	case Big:
		sURL = SMJ_B_IMG;
		sURL += SMJID;
		OutFile.open(Bro->L_getSMJPIC_PATH() + sFile + ".webp", std::ostream::binary);
		break;
	case Lotto:
		sFile = SMJName;
		sURL = SMJ_B_IMG;
		sURL += SMJID;
		sURL += "?simple";
		OutFile.open(Bro->L_getLOTTOPIC_PATH() + sFile + ".webp", std::ostream::binary);
		break;
	}
#endif
	if (_Type != Lotto)
	{
		boost::erase_all(SMJName, " ");
		sURL += "?upgrades=";
		sURL += std::to_string(Upgrade);
		sURL += "&charges=";
		sURL += std::to_string(Charges);
	}
	MISD(sURL);

	mutex_WEBRequest.lock();
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, sURL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileCallback);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_FILE, &OutFile);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			Bro->B_StatusE("E", "DownloadImage #2 - curl_easy_perform", curl_easy_strerror(res));
			OutFile.close();
			mutex_WEBRequest.unlock();
			MISEA("V5: Error curl_easy_perform Image");
			return;
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		if (httpCode == 200 || httpCode == 201)
		{
			OutFile.close();
			mutex_WEBRequest.unlock();
			MISE;
			return;
		}
		else
		{
			MISEA("V6: httpCode:" + std::to_string(httpCode));
			OutFile.close();
			mutex_WEBRequest.unlock();
			return;
		}
	}

	OutFile.close();
	mutex_WEBRequest.unlock();
	MISEA("V5");
	return;
}

std::string CardBaseSMJ::GetImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges, SMJPicType _Type, bool bSW)
{
	MISS;
	std::string sFile;

#ifndef noLoad
	switch (_Type)
	{
	case Small:
		sFile = Bro->L_getSMJPICSMALL_PATH();
		Upgrade = 0;
		Charges = 0;
		break;
	case Big:
		sFile = Bro->L_getSMJPIC_PATH();
		break;
	case ImgOnly:
		sFile = Bro->L_getSMJIMG_PATH();
		Upgrade = 0;
		Charges = 0;
		break;
	case Lotto:
		sFile = Bro->L_getLOTTOPIC_PATH();
		break;
	}
#endif

	if (_Type != Lotto)sFile += std::to_string(CardID) + "_" + std::to_string(Upgrade) + std::to_string(Charges);
	else sFile += GetSMJCard(CardID)->cardNameSimple;

	if (bSW)sFile += "SW";

	sFile += ".webp";
	MISD(sFile);
	if (!File_exists(sFile))
	{
		MISD("Download: " + sFile);
		DownloadImage(CardID, Upgrade, Charges, _Type);
		if (bSW)ConvertImage(sFile);
	}
	MISE;
	return sFile;
}

void CardBaseSMJ::ConvertImage(std::string sFile)
{
	MISS;
	std::string sFileIn = sFile;
	sFileIn.replace(sFileIn.find("SW.webp"), 7, ".webp");
	MISD(sFile);
	//MISD(sFileIn);

	cv::Mat image = cv::imread(sFileIn, cv::IMREAD_COLOR);
	if (image.empty()) {
		MISEA("Cant open " + sFileIn);
		return;
	}
	cv::Mat grayImage;
	cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
	cv::imwrite(sFile, grayImage);

	MISE;
}

void CardBaseSMJ::AllIMGBig()
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)	
		for (unsigned int j = 0; j <= 3; j++)
			for (unsigned int k = 0; k <= j; k++)
				GetImage(SMJMatrix[i]->cardId, j, k, Big, false);
	
	MISE;
}

void CardBaseSMJ::AllIMGBigSW()
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
		for (unsigned int j = 0; j <= 3; j++)
			for (unsigned int k = 0; k <= j; k++)
				GetImage(SMJMatrix[i]->cardId, j, k, Big, true);

	MISE;
}

void CardBaseSMJ::AllIMGSmall()
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
		for (unsigned int j = 0; j <= 3; j++)
			for (unsigned int k = 0; k <= j; k++)
				GetImage(SMJMatrix[i]->cardId, j, k, Small, false);

	MISE;
}

void CardBaseSMJ::AllIMGImgOnly()
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
				GetImage(SMJMatrix[i]->cardId, 0, 0, ImgOnly, false);

	MISE;
}

void CardBaseSMJ::AllIMGSimpel()
{
	MISS;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		GetImage(SMJMatrix[i]->cardId, 0, 0, Lotto, false);
		GetImage(SMJMatrix[i]->cardId, 0, 0, Lotto, true);
	}

	MISE;
}
#endif

#ifndef noSQL
bool CardBaseSMJ::SMJtoSQL(bool bUpdate)
{
	MISS;
	bool bNewCard;

	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		Bro->N->ssSQL << "SELECT ID FROM cards WHERE ID = " << SMJMatrix[i]->cardId;

		// Nicht vorhanden also Anlegen
		if (Bro->N->send() <= 0)
		{
			MISD("New Card:" + std::to_string(SMJMatrix[i]->cardId));
			Bro->N->ssSQL << "INSERT INTO cards (	ID ) VALUES('" << SMJMatrix[i]->cardId << "')";
			Bro->N->send();
			bNewCard = true;
		}
		else bNewCard = false;

		//Bei neuanlage oder Update felder aktualisieren
		if (bNewCard || bUpdate)
		{
			//MISD("Update Card:" + Card["cardId"].asString() + "#" + Card["cardName"].asString());
			Bro->N->ssSQL << " UPDATE cards SET ";
			Bro->N->ssSQL << " cardName = '" << Bro->N->clearString(SMJMatrix[i]->cardNameSimple) << "', ";
			Bro->N->ssSQL << " affinity = '" << SwitchAffinity(SMJMatrix[i]->affinity) << "', ";
			//Bro->N->ssSQL << " expansion = '" << Card["expansion"].asString() << "', ";
			Bro->N->ssSQL << " cardType = '" << SwitchColor(SMJMatrix[i]->color) << "', ";
			Bro->N->ssSQL << " rarity = '" << SwitchRarity(SMJMatrix[i]->rarity) << "', ";
			Bro->N->ssSQL << " promo = " << std::to_string(SMJMatrix[i]->promo) << ", ";
			//Bro->N->ssSQL << " obtainable_in_pack = " << (Card["obtainable"].asString() == "In packs") << ", ";

			Bro->N->ssSQL << " fireOrbs = " << std::to_string(SMJMatrix[i]->orbsFire) << ", ";
			Bro->N->ssSQL << " frostOrbs = " << std::to_string(SMJMatrix[i]->orbsFrost) << ", ";
			Bro->N->ssSQL << " natureOrbs = " << std::to_string(SMJMatrix[i]->orbsNature) << ", ";
			Bro->N->ssSQL << " shadowOrbs = " << std::to_string(SMJMatrix[i]->orbsShadow) << ", ";
			Bro->N->ssSQL << " neutralOrbs = " << std::to_string(SMJMatrix[i]->orbsNeutral
				+ SMJMatrix[i]->orbsFireFrost + SMJMatrix[i]->orbsFireNature + SMJMatrix[i]->orbsFireShadow
				+ SMJMatrix[i]->orbsNatureFrost + SMJMatrix[i]->orbsShadowFrost + SMJMatrix[i]->orbsShadowNature)
				<< " ";

			Bro->N->ssSQL << " WHERE ID = " << SMJMatrix[i]->cardId;

			Bro->N->send();
		}

	}

	MISE;
	return true;
}

bool CardBaseSMJ::IMGtoQSL(int iCardID)
{
	MISS;
	std::vector<uchar> buffer;
	std::stringstream ss;

	std::string sFile = GetImage(iCardID, 0, 0, ImgOnly, false); //WEBP
	cv::Mat image = cv::imread(sFile, cv::IMREAD_UNCHANGED);

	if (image.empty()) 
	{
		MISEA("Error Opening: " + sFile);
		return false;
	}

	if (!cv::imencode(".png", image, buffer)) {
		MISEA("Error Converting: " + sFile);
		return false;
	}

	ss.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
	
	Bro->N->ssSQL << " UPDATE cards SET IMG = ?";
	Bro->N->ssSQL << " WHERE ID = " << iCardID;
	Bro->N->SendBLOB(ss.str());

	MISE;
	return true;
}

bool CardBaseSMJ::Imager()
{
	MISS;

	Bro->N->ssSQL << "SELECT ID FROM cards ";

	if (Bro->N->send() <= 0)
	{
		MISEA("V1: SQL ERROR");
		return false;
	}

	while (Bro->N->res->next())	
		IMGtoQSL(Bro->N->res->getInt(1));
	

	MISE;
	return true;
}

#endif


Tome_Booster* CardBaseSMJ::OpenBooster(std::string iType, bool bNoDouble, std::vector<Tome_Booster*> vOpendBooster)
{
	MISS;

	//Card 1: 0.5% Promo, 19.5% Ultra Rare, 80 % Rare
	//Card 2 : 15 % Rare, 85 % Uncommon
	//Card 3 : 20 % Uncommon, 80 % Common
	//Card 4 : 100 % Uncommon
	//Cards 5, 6, 7 and 8 : 100 % Common

	Tome_Booster* Booster = new Tome_Booster(iType);

	std::vector <SMJCard*> vPromo;
	std::vector <SMJCard*> vUR;
	std::vector <SMJCard*> vR;
	std::vector <SMJCard*> vUC;
	std::vector <SMJCard*> vC;

	unsigned int iPromos = 0;
	unsigned int iUR = 0;
	unsigned int iR = 0;
	unsigned int iUC = 0;
	unsigned int iC = 0;

	int iRandome = 0;

	bool bCheck;
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		bCheck = false;
		for (unsigned int j = 0; j < SMJMatrix[i]->vBoosters.size() && bCheck == false; j++)
			if (std::to_string(SMJMatrix[i]->vBoosters[j]) == iType) bCheck = true;
		if (bCheck == false)continue;

		if (bNoDouble)
		{
			for (Tome_Booster* B : vOpendBooster)
			{
				for (SMJCard* C : B->vCards)
				{
					if (C->cardId == SMJMatrix[i]->cardId)goto SkipCard;
				}
			}
		}

		if (SMJMatrix[i]->promo == 1)
		{
			vPromo.push_back(SMJMatrix[i]);
			continue;
		}

		switch (SMJMatrix[i]->rarity)
		{
		case 0:
			vC.push_back(SMJMatrix[i]);
			break;
		case 1:
			vUC.push_back(SMJMatrix[i]);
			break;
		case 2:
			vR.push_back(SMJMatrix[i]);
			break;
		case 3:
			vUR.push_back(SMJMatrix[i]);
			break;
		}
	SkipCard:;
	}



	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(0, 1000 - 1);

	//MINI Booster
	if (iType == "-2")
	{
		//Card1		
		iRandome = distr(gen);
		if (iRandome < 195) iR++;
		else iUC++;

		//Card2	
		iUC++;

		//Card3
		iRandome = distr(gen);
		if (iRandome < 150) iUC++;
		else iC++;

		//Card4
		iC++;

		//Card5
		iC++;
	}
	else if (iType == "10")
	{
		//Card1		
		iRandome = distr(gen);
		if (iRandome < 400) iUR++;
		else iR++;

		//Card2	
		iRandome = distr(gen);
		if (iRandome < 400) iR++;
		else iUC++;

		//Card3
		iUC++;
	}
	//Normal Booster
	else
	{
		//Card1		
		iRandome = distr(gen);
		if (iRandome < 5) iPromos++;
		else if (iRandome < 200) iUR++;
		else iR++;

		//Card2	
		iRandome = distr(gen);
		if (iRandome < 150) iR++;
		else iUC++;

		//Card3
		iRandome = distr(gen);
		if (iRandome < 200) iUC++;
		else iC++;

		//Card4
		iUC++;

		//Card5
		iC++;

		//Card6
		iC++;

		//Card7
		iC++;

		//Card8
		iC++;
	}
	

	MISD("iPromos:" + std::to_string(iPromos));
	MISD("iUR:" + std::to_string(iUR));
	MISD("iR:" + std::to_string(iR));
	MISD("iUC:" + std::to_string(iUC));
	MISD("iC:" + std::to_string(iC));

	MISD("vPromo:" + std::to_string(vPromo.size()));
	MISD("vUR:" + std::to_string(vUR.size()));
	MISD("vR:" + std::to_string(vR.size()));
	MISD("vUC:" + std::to_string(vUC.size()));
	MISD("vC:" + std::to_string(vC.size()));


	distr = std::uniform_int_distribution<int>(0, vPromo.size() - 1);
	for (unsigned int i = 0; i < iPromos && i < vPromo.size(); i++)
	{
		iRandome = distr(gen);
		MISD("vPromo:" + std::to_string(iRandome) + "/" + std::to_string(vPromo.size()));
		bCheck = false;
		for (unsigned int j = 0; j < Booster->vCards.size(); j++)
			if (Booster->vCards[j]->cardId == vPromo[iRandome]->cardId)bCheck = true;
		if (bCheck)
		{
			i--;
			continue;
		}
		Booster->vCards.push_back(vPromo[iRandome]);
	}

	distr = std::uniform_int_distribution<int>(0, vUR.size() - 1);
	for (unsigned int i = 0; i < iUR && i < vUR.size(); i++)
	{
		iRandome = distr(gen);
		MISD("vUR:" + std::to_string(iRandome) + "/" + std::to_string(vUR.size()));
		bCheck = false;
		for (unsigned int j = 0; j < Booster->vCards.size(); j++)
			if (Booster->vCards[j]->cardId == vUR[iRandome]->cardId)bCheck = true;
		if (bCheck)
		{
			i--;
			continue;
		}
		Booster->vCards.push_back(vUR[iRandome]);
	}

	distr = std::uniform_int_distribution<int>(0, vR.size() - 1);
	for (unsigned int i = 0; i < iR && i < vR.size(); i++)
	{
		iRandome = distr(gen);
		MISD("vR:" + std::to_string(iRandome) + "/" + std::to_string(vR.size()));
		bCheck = false;
		for (unsigned int j = 0; j < Booster->vCards.size(); j++)
			if (Booster->vCards[j]->cardId == vR[iRandome]->cardId)bCheck = true;
		if (bCheck)
		{
			i--;
			continue;
		}
		Booster->vCards.push_back(vR[iRandome]);
	}

	distr = std::uniform_int_distribution<int>(0, vUC.size() - 1);
	for (unsigned int i = 0; i < iUC && i < vUC.size(); i++)
	{
		iRandome = distr(gen);
		MISD("vUC:" + std::to_string(iRandome) + "/" + std::to_string(vUC.size()));
		bCheck = false;
		for (unsigned int j = 0; j < Booster->vCards.size(); j++)
			if (Booster->vCards[j]->cardId == vUC[iRandome]->cardId)bCheck = true;
		if (bCheck)
		{
			i--;
			continue;
		}
		Booster->vCards.push_back(vUC[iRandome]);
	}

	distr = std::uniform_int_distribution<int>(0, vC.size() - 1);
	for (unsigned int i = 0; i < iC && i < vC.size(); i++)
	{
		iRandome = distr(gen);
		MISD("vC:" + std::to_string(iRandome) + "/" + std::to_string(vC.size()));
		bCheck = false;
		for (unsigned int j = 0; j < Booster->vCards.size(); j++)
			if (Booster->vCards[j]->cardId == vC[iRandome]->cardId)bCheck = true;
		if (bCheck)
		{
			i--;
			continue;
		}
		Booster->vCards.push_back(vC[iRandome]);
	}

	MISD("Booster:" + std::to_string(Booster->vCards.size()));
	MISE;
	return Booster;
}

