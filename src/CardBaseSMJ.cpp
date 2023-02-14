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
	bCardsLoaded = false;
	MISE;
}

CardBaseSMJ::~CardBaseSMJ()
{
	MISS;
	curl_global_cleanup();
	MISE;
}

Json::Value CardBaseSMJ::GetJsonFromWeb()
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
		//curl_easy_setopt(curl, CURLOPT_URL, CardWebURL);
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

std::string CardBaseSMJ::DownloadImage(int iCardID, std::string sCardName, bool bPromo)
{
	MISS;

	std::ofstream OutFile;
	CURLcode res;
	long httpCode(0);
	int start_pos = 0;
	std::string sURL;
	
	std::string readBuffer = "";
	
	start_pos = 0;
	while ((start_pos = sCardName.find(" ", start_pos)) != sCardName.npos)sCardName.replace(start_pos, 1, "_");
	start_pos = 0;
	while ((start_pos = sCardName.find("'", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%27");	
	start_pos = 0;
	while ((start_pos = sCardName.find("(", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%28");
	start_pos = 0;
	while ((start_pos = sCardName.find(")", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%29");
			
	//sURL = WikiPre + sCardName;

	MISD(sURL);

	// Get Wiki Page
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, sURL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);		

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
		{
			Bro->B_StatusE("E", "DownloadImage #1 - curl_easy_perform", curl_easy_strerror(res));
			MISEA("V2");
			return "";
		}
			
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		if (httpCode == 200 || httpCode == 201)
		{
			start_pos = 0;
			while ((start_pos = readBuffer.find("data-src=", start_pos)) != readBuffer.npos)
			{
				start_pos = start_pos + 10;

				sURL = readBuffer.substr(start_pos, readBuffer.find(char(34), start_pos) - start_pos);
				//if (bPromo && sURL.find(sCardName + "_%28Promo%29" + WikiPos) != sURL.npos)break;
				//else if (sURL.find(sCardName + WikiPos) != sURL.npos)break;				
			}	

		}
		else 
		{
			MISEA("V3: httpCode #1:" + std::to_string(httpCode));
			return "";
		}
	}

	if (sURL == "")
	{
		MISEA("V4: NO URL FOUND");
		return "";
	}


	MISD(sURL);

	OutFile.open(Bro->L_getTMP_PATH() + std::to_string(iCardID) + ".png", std::ostream::binary);

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
			return Bro->L_getTMP_PATH() + std::to_string(iCardID) + ".png";
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

	unsigned char doubbelSet = 0;
	unsigned int i;
	unsigned char iReturn = 0;

	//MISD("CardID " + to_string(CardID));

	for (i = 0; i < SQLCardMatrix.size(); i++)
	{
		if (SQLCardMatrix[i]->cardId == CardID)break;
	}

	if (i == SQLCardMatrix.size())
	{
		MISEA("V2 Cant Find in Matrix")
		return 255;
	}

	if (SQLCardMatrix[i]->shadowOrbs != 0)
	{
		iReturn += 1;
		doubbelSet++;
	}
	if (SQLCardMatrix[i]->natureOrbs != 0)
	{
		iReturn += 2;
		doubbelSet++;
	}
	if (SQLCardMatrix[i]->frostOrbs != 0)
	{
		iReturn += 3;
		doubbelSet++;
	}
	if (SQLCardMatrix[i]->fireOrbs != 0)
	{
		iReturn += 4;
		doubbelSet++;
	}
	if (SQLCardMatrix[i]->neutralOrbs != 0)
	{
		iReturn += 100;
		doubbelSet++;
	}

	if (doubbelSet != 1)
	{
		MISEA("V3 Multi Set")
		return 255;
	}

	MISE;
	return iReturn;
}
