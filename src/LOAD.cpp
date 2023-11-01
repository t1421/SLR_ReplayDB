#define DF_Debug

#include "..\incl\Broker.h"

#include "..\incl\LOAD.h"
#include "..\incl\Utility.h"

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
			if (INI_Value_Check(line, "TOME_SAVE_PATH"))sTOME_SAVE_PATH = line.c_str();

			if (INI_Value_Check(line, "TMP_PATH"))sTMP_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPIC_PATH"))sSMJPIC_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJIMG_PATH"))sSMJIMG_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPICSMALL_PATH"))sSMJPICSMALL_PATH = line.c_str();
			if (INI_Value_Check(line, "BOOSTER_PATH"))sBOOSTER_PATH = line.c_str();
			
			if (INI_Value_Check(line, "FFMPEG"))sFFMPEG = line.c_str();

			if (INI_Value_Check(line, "BOT4RankMode"))BOTRankMode[BOT4LIST] = atoi(line.c_str());
			if (INI_Value_Check(line, "BOT6RankMode"))BOTRankMode[BOT6LIST] = atoi(line.c_str());			
			
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

std::string LOAD::entry(std::string Liste, int pos)
{
	if (pos == 0)return Liste.substr(0, Liste.find(";"));
	else
	{
		Liste.erase(0, Liste.find(";") + 1);
		return entry(Liste, pos - 1);
	}
}
