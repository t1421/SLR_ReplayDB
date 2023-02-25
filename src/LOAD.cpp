//#define DF_Debug

#include "..\incl\Broker.h"

#include "..\incl\LOAD.h"

#include <fstream>

broker *(LOAD::Bro) = NULL;

void LOAD::Load_Settings()
{
	MISS;
	std::string line;
	std::string sName = "Settings.ini";

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);

	if (ifFile.good())
	{
		MISD("good");
		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);
			//printf("%s\n",line.c_str());

			if (INI_Value_Check(line, "SQL_Server"))sSQL_Server = line.c_str();
			if (INI_Value_Check(line, "SQL_User"))sSQL_User = line.c_str();
			if (INI_Value_Check(line, "SQL_PW"))sSQL_PW = line.c_str();
			if (INI_Value_Check(line, "SQL_DB"))sSQL_DB = line.c_str();

			if (INI_Value_Check(line, "PMV_PATH"))sPMV_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_AUTO_PATH"))sPMV_AUTO_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_ARCH_PATH"))sPMV_ARCH_PATH = line.c_str();

			if (INI_Value_Check(line, "RANK_PATH"))sRANK_PATH = line.c_str();

			if (INI_Value_Check(line, "TMP_PATH"))sTMP_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPIC_PATH"))sSMJPIC_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPICSMALL_PATH"))sSMJPICSMALL_PATH = line.c_str();

			if (INI_Value_Check(line, "FFMPEG"))sFFMPEG = line.c_str();

			if (INI_Value_Check(line, "BOT1RankMode"))BOTRankMode[BOT1LIST] = atoi(line.c_str());
			if (INI_Value_Check(line, "BOT2RankMode"))BOTRankMode[BOT2LIST] = atoi(line.c_str());
			if (INI_Value_Check(line, "BOT3RankMode"))BOTRankMode[BOT3LIST] = atoi(line.c_str());
			if (INI_Value_Check(line, "BOT4RankMode"))BOTRankMode[BOT4LIST] = atoi(line.c_str());
			
			ifFile.clear();
		}
		
		ifFile.close();
	}
	MISE;
}

void LOAD::StartUp()
{
	MISS;
	Load_Settings();
	MISE;
}

bool LOAD::INI_Value_Check(std::string &check, std::string name)
{
	MISS;
	if (check.substr(0, check.find("=")) == name)
	{
		check.erase(0, check.find("=") + 1);
		MISEA(" true: " + check);
		return true;
	}
	else
	{
		MISEA(" false");
		return false;
	}
}

void LOAD::LoadCards()
{
	MISS;
	std::string line;
	#ifdef __linux__
	std::string sName = "./Release/cards.csv";
	#else
	std::string sName = "./cards.csv";
	#endif

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);

	if (ifFile.good())
	{
		MISD("good");

		while (getline(ifFile, line))
		{
			CsvAllCards.emplace_back(new CsvCard(
				atoi(entry(line, 0).c_str()),
				atoi(entry(line, 1).c_str()),
				atoi(entry(line, 2).c_str()),
				atoi(entry(line, 3).c_str()),
				atoi(entry(line, 4).c_str()),
				atoi(entry(line, 5).c_str()),
				atoi(entry(line, 6).c_str()),
				atoi(entry(line, 7).c_str()),
				atoi(entry(line, 8).c_str())
			));

			ifFile.clear();
		}

		ifFile.close();
	}
	else MISERROR("cant open .\\cards.csv");
	
	MISE;
}

std::string LOAD::entry(std::string Liste, int pos)
{
	if (pos == 0)return Liste.substr(0, Liste.find(";"));
	else
	{
		Liste.erase(0, Liste.find(";") + 1);
		return entry(Liste, pos - 1);
	}
}