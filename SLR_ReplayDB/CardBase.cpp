//#define DF_Debug

#include "stdafx.h"

#include "SQL_MIS_New.h"
#include "CardBase.h" 

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


broker *(CardBase::Bro) = NULL;

CardBase::CardBase()
{
	MISS;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	bCardsLoaded = false;
	MISE;
}

CardBase::~CardBase()
{
	MISS;
	curl_global_cleanup();
	MISE;
}

Json::Value CardBase::GetJsonFromWeb()
{
	MISS;
	
	CURLcode res;
	long httpCode(0);

	Json::Value jsonData;
	Json::Reader jsonReader;

	string readBuffer = "";

	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, CardWebURL);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)Bro->B->StatusE("E", "GetJsonFromWeb - curl_easy_perform", curl_easy_strerror(res));
		
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		if (httpCode == 200)
		{
			if (jsonReader.parse(readBuffer, jsonData))
			{
				MISD("Json Request - Sucess")
			}
			else Bro->B->StatusE("E", "GetJsonFromWeb - jsonReader.parse", "");
		}
		else Bro->B->StatusE("E", "GetJsonFromWeb - httpCode", to_string(httpCode));

		curl_easy_cleanup(curl);
	}
	MISE;

	return jsonData;
}

bool CardBase::WEBtoSQL(bool bUpdate)
{
	MISS;

	Json::Value AllCards;
	Json::Value Card;

	bool bNewCard;

	AllCards = GetJsonFromWeb();
	MISD("CardCount:" + to_string(AllCards.size()));

	for (Json::ArrayIndex i = 0; i < AllCards.size(); i++)
	{		
		Card = AllCards[i];
		Bro->N->ssSQL << "SELECT ID FROM cards WHERE ID = " << Card["cardId"].asInt();

		// Nicht vorhanden also Anlegen
		if (Bro->N->send() <= 0)
		{
			MISD("New Card:" + Card["cardId"].asString() + "#" + Card["cardName"].asString());
			Bro->N->ssSQL << "INSERT INTO cards (	ID ) VALUES('" << Card["cardId"].asInt() << "')";
			Bro->N->send();
			bNewCard = true;
		}
		else bNewCard = false;

		//Bei neuanlage oder Update felder aktualisieren
		if (bNewCard || bUpdate)
		{
			//MISD("Update Card:" + Card["cardId"].asString() + "#" + Card["cardName"].asString());
			Bro->N->ssSQL << " UPDATE cards SET ";
			Bro->N->ssSQL << " cardName = '" << Bro->N->clearString(Card["cardName"].asString()) << "', ";
			Bro->N->ssSQL << " affinity = '" << Card["affinity"].asString() << "', ";
			Bro->N->ssSQL << " expansion = '" << Card["expansion"].asString() << "', ";
			Bro->N->ssSQL << " cardType = '" << Card["cardType"].asString() << "', ";
			Bro->N->ssSQL << " rarity = '" << Card["rarity"].asString() << "', ";

			Bro->N->ssSQL << " promo = " << (Card["promo"].asString() == "Yes") << ", ";
			Bro->N->ssSQL << " obtainable_in_pack = "<< (Card["obtainable"].asString() == "In packs")<< ", ";

			Bro->N->ssSQL << " fireOrbs = " << Card["fireOrbs"].asInt() << ", ";
			Bro->N->ssSQL << " frostOrbs = " << Card["frostOrbs"].asInt() << ", ";
			Bro->N->ssSQL << " natureOrbs = " << Card["natureOrbs"].asInt() << ", ";
			Bro->N->ssSQL << " shadowOrbs = " << Card["shadowOrbs"].asInt() << ", ";
			Bro->N->ssSQL << " neutralOrbs = " << Card["neutralOrbs"].asInt() << " ";

			Bro->N->ssSQL << " WHERE ID = " << Card["cardId"].asInt();

			Bro->N->send();
		}
		
	}
	
	MISE;
	return true;
}


string CardBase::DownloadImage(int iCardID, string sCardName, bool bPromo)
{
	MISS;

	ofstream OutFile;
	CURLcode res;
	long httpCode(0);
	int start_pos = 0;
	string sURL;
	
	string readBuffer = "";
	
	start_pos = 0;
	while ((start_pos = sCardName.find(" ", start_pos)) != sCardName.npos)sCardName.replace(start_pos, 1, "_");
	start_pos = 0;
	while ((start_pos = sCardName.find("'", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%27");	
	start_pos = 0;
	while ((start_pos = sCardName.find("(", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%28");
	start_pos = 0;
	while ((start_pos = sCardName.find(")", start_pos))  != sCardName.npos)sCardName.replace(start_pos, 1, "%29");
			
	sURL = WikiPre + sCardName;

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
			Bro->B->StatusE("E", "DownloadImage #1 - curl_easy_perform", curl_easy_strerror(res));
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
				if (bPromo && sURL.find(sCardName + "_%28Promo%29" + WikiPos) != sURL.npos)break;
				else if (sURL.find(sCardName + WikiPos) != sURL.npos)break;				
			}	

		}
		else 
		{
			MISEA("V3: httpCode #1:" + to_string(httpCode));			
			return "";
		}
	}

	if (sURL == "")
	{
		MISEA("V4: NO URL FOUND");
		return "";
	}


	MISD(sURL);

	OutFile.open(Tmp_path + to_string(iCardID) + ".png", std::ostream::binary);

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
			Bro->B->StatusE("E", "DownloadImage #2 - curl_easy_perform", curl_easy_strerror(res));
			MISEA("V5: Error curl_easy_perform Image");
			return "";
		}

		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
		curl_easy_cleanup(curl);
		if (httpCode == 200 || httpCode == 201)
		{
			OutFile.close();
			MISE;
			return Tmp_path + to_string(iCardID) + ".png";
		}
		else
		{
			MISEA("V6: httpCode:" + to_string(httpCode));
			return "";
		}
	}

	OutFile.close();
	MISEA("V5");
	return "";
}



bool CardBase::IMGtoQSL(int iCardID, string sFile)
{
	MISS;
	
	ifstream ifs;
	stringstream ss;
	
	ifs.open(sFile, std::ifstream::binary | std::ifstream::in);
	if (ifs)
	{
		ss<< ifs.rdbuf();
		ifs.close();
	}
	else Bro->B->StatusE("E", "IMGtoQSL", "Error opening File");
	
	Bro->N->ssSQL << " UPDATE cards SET IMG = ?";
	Bro->N->ssSQL << " WHERE cardId = " << iCardID;
	Bro->N->SendBLOB(ss.str());
	
	
	MISE;
	return true;
}

bool CardBase::Imager(int iCardID)
{
	MISS;

	string sCardName;
	string sPath;

	Bro->N->ssSQL << "SELECT CardName, ID, promo FROM cards ";
	if(iCardID!=0)Bro->N->ssSQL << " WHERE ID = " << iCardID;
	
	if (Bro->N->send() <= 0)
	{
		MISEA("V1: " + to_string(iCardID) + " not found");
		return false;
	}

	while (Bro->N->res->next())
	{
		//MISD(Bro->N->res->getString(1) + "#" + Bro->N->res->getString(2));
		sCardName = Bro->N->res->getString(1);				
		sPath = DownloadImage(Bro->N->res->getInt(2), sCardName, Bro->N->res->getBoolean(3));
		//MISD(sPath);
		IMGtoQSL(Bro->N->res->getInt(2), sPath);
	}
	
	MISE;
	return true;
}

bool CardBase::LoadCardsFromSQL()
{
	MISS;
	SQLCard * SQLCard_TEMP;

	if (bCardsLoaded)
	{
		MISEA("V1 Already Loaded");
		return true;
	}

	Bro->N->ssSQL << "SELECT ID, fireOrbs, frostOrbs, natureOrbs, shadowOrbs, neutralOrbs FROM cards ";
	if (Bro->N->send() <= 0)
	{
		MISEA("V2 No Cards in DB?");
		return false;
	}

	while (Bro->N->res->next())
	{
		SQLCard_TEMP = new SQLCard;
		SQLCard_TEMP->cardId = Bro->N->res->getInt(1);
		SQLCard_TEMP->fireOrbs = Bro->N->res->getInt(2);
		SQLCard_TEMP->frostOrbs = Bro->N->res->getInt(3);
		SQLCard_TEMP->natureOrbs = Bro->N->res->getInt(4);
		SQLCard_TEMP->shadowOrbs = Bro->N->res->getInt(5);
		SQLCard_TEMP->neutralOrbs = Bro->N->res->getInt(6);
		
		SQLCardMatrix.push_back(SQLCard_TEMP);
	}

	MISE;
	return true;
}

unsigned char CardBase::GetActionOrbForCardID(unsigned short CardID)
{
	MISS;

	unsigned char doubbelSet = 0;
	unsigned int i;
	unsigned char iReturn = 0;

	//MISD("CardID " + to_string(CardID));

	if (!LoadCardsFromSQL())
	{
		MISEA("V1 Error while Loading von DB")
		return 255;
	}

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