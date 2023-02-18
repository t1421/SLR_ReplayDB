#define DF_Debug
//#define BrokerNormal

#include "..\incl\Broker.h" 

#define SMJ_Cards "https://smj.cards/api/cards"
#define SMJ_S_IMG "https://smj.cards/api/images/basicCard/"
#define SMJ_B_IMG "https://smj.cards/api/images/fullCard/"

#include "..\incl\CardBaseSMJ.h" 

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
	Json::Value ID;

	SMJCard * SMJCard_TEMP;

	RawData = SMJtoCHASH();
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
		
		ID = Card["officialCardIds"];
		SMJCard_TEMP->cardId = ID[0].asInt();

		SMJMatrix.push_back(SMJCard_TEMP);
	}

	return true;
	MISE;
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
			printf("SMJid:             %s\n", SMJMatrix[i]->SMJid.c_str());
			printf("cardName:          %s\n", SMJMatrix[i]->cardName.c_str());
			printf("color:             %lu\n", SMJMatrix[i]->color);
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
			break;
		}
	}
	MISE;
}


Json::Value CardBaseSMJ::SMJtoCHASH()
{
	MISS;
	
	CURLcode res;
	long httpCode(0);

	Json::Value jsonData;
	Json::Reader jsonReader;

	std::string readBuffer = "";

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, SMJ_Cards);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)Bro->B_StatusE("E", "GetJsonFromWeb - curl_easy_perform", curl_easy_strerror(res));
		
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (httpCode == 200)
		{
			if (jsonReader.parse(readBuffer, jsonData))
			{
				MISD("Json Request - Sucess")
			}
			else Bro->B_StatusE("E", "GetJsonFromWeb - jsonReader.parse", "");
		}
		else Bro->B_StatusE("E", "GetJsonFromWeb - httpCode", std::to_string(httpCode));

		curl_easy_cleanup(curl);
	}
	MISE;

	return jsonData;
}

std::string CardBaseSMJ::DownloadImage(unsigned short CardID, unsigned char Upgrade, unsigned char Charges)
{
	MISS;

	std::ofstream OutFile;
	CURLcode res;
	long httpCode(0);
	std::string sURL;
	std::string SMJID;
	std::string sFile = std::to_string(CardID) + std::to_string(Upgrade) + std::to_string(Charges);

	
	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == CardID)
		{
			SMJID = SMJMatrix[i]->SMJid;
			break;
		}
	}

	sURL  = SMJ_B_IMG;
	sURL += SMJID;
	sURL += "?upgrades=";
	sURL += std::to_string(Upgrade);
	sURL += "&charges=";
	sURL += std::to_string(Charges);
		
	MISD(sURL);

	OutFile.open(Bro->L_getSMJPIC_PATH() + sFile + ".png", std::ostream::binary);

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
			MISEA("V5: Error curl_easy_perform Image");
			return "";
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		if (httpCode == 200 || httpCode == 201)
		{
			OutFile.close();
			MISE;
			return Bro->L_getSMJPIC_PATH() + sFile + ".png";
		}
		else
		{
			MISEA("V6: httpCode:" + std::to_string(httpCode));
			return "";
		}
	}

	OutFile.close();
	MISEA("V5");
	return "";
}





unsigned char CardBaseSMJ::GetActionOrbForCardID(unsigned short CardID)
{
	MISS;

	for (unsigned int i = 0; i < SMJMatrix.size(); i++)
	{
		if (SMJMatrix[i]->cardId == CardID)
		{
			MISE;
			return SMJMatrix[i]->color;
		}
	}

	MISEA("Canft Find Card");
	return 99;
}
