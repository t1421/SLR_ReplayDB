//#define DF_Debug

#include "..\incl\Broker.h"

#include "..\incl\LOAD.h"
#include "..\incl\Utility.h"

#ifdef BrokerPVP
#include "..\incl\CLI11.hpp"
#endif
#include <fstream>

broker *(LOAD::Bro) = NULL;

void LOAD::Load_Settings(std::string sName)
{
	MISS;
	MISERROR(sName);
	std::string line;	

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
			if (INI_Value_Check(line, "AdminKey"))sAdminKey = line.c_str();

			if (INI_Value_Check(line, "PMV_PATH"))sPMV_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_AUTO_PATH"))sPMV_AUTO_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_ARCH_PATH"))sPMV_ARCH_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_WEB_PATH"))sPMV_WEB_PATH = line.c_str();

			if (INI_Value_Check(line, "RANK_PATH"))sRANK_PATH = line.c_str();
			if (INI_Value_Check(line, "TOME_SAVE_PATH"))sTOME_SAVE_PATH = line.c_str();
			if (INI_Value_Check(line, "LOTTO_SAVE_PATH"))sLOTTO_SAVE_PATH = line.c_str();
			

			if (INI_Value_Check(line, "TMP_PATH"))sTMP_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPIC_PATH"))sSMJPIC_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJIMG_PATH"))sSMJIMG_PATH = line.c_str();
			if (INI_Value_Check(line, "SMJPICSMALL_PATH"))sSMJPICSMALL_PATH = line.c_str();
			if (INI_Value_Check(line, "LOTTOPIC_PATH"))sLOTTOPIC_PATH = line.c_str();
			if (INI_Value_Check(line, "BOOSTER_PATH"))sBOOSTER_PATH = line.c_str();
			if (INI_Value_Check(line, "MAPPIC_PATH"))sMAPPIC_PATH = line.c_str();
			
			if (INI_Value_Check(line, "FFMPEG"))sFFMPEG = line.c_str();
			if (INI_Value_Check(line, "LivePvPPMV"))sLivePvPPMV = line.c_str();
			if (INI_Value_Check(line, "LivePvP_OBS_Export"))sLivePvP_OBS_Export = line.c_str();
			if (INI_Value_Check(line, "LivePvP_Pics"))sLivePvP_Pics = line.c_str();
			if (INI_Value_Check(line, "LivePvPRefreshRate"))iLivePvPRefreshRate = atoi(line.c_str());
			if (INI_Value_Check(line, "LivePvPActionLog"))iLivePvPActionLog = atoi(line.c_str());
			if (INI_Value_Check(line, "LivePvPActionPerSec"))iLivePvPActionPerSec = atoi(line.c_str());
			if (INI_Value_Check(line, "LivePvPActionPerSecNumSec"))iLivePvPActionPerSecNumSec = atoi(line.c_str());
			

			if (INI_Value_Check(line, "ChallongeUser"))sChallongeUser = line.c_str();
			if (INI_Value_Check(line, "ChallongeAPIKEY"))sChallongeAPIKEY = line.c_str();
			if (INI_Value_Check(line, "ChallongeSaveDir"))sChallongeSaveDir = line.c_str();

			if (INI_Value_Check(line, "QuizPath"))sQuizPath = line.c_str();
			if (INI_Value_Check(line, "QuizCountDown"))iCountDown = atoi(line.c_str());
			if (INI_Value_Check(line, "QuizCoolDown"))iCoolDown = atoi(line.c_str());

			if (INI_Value_Check(line, "SRFileVersion"))iSRFileVersion = atoi(line.c_str());
			if (INI_Value_Check(line, "SRGameVersion"))iSRGameVersion = atoi(line.c_str());

			if (INI_Value_Check(line, "WebAnalyser"))sWebAnalyser = line.c_str();
			if (INI_Value_Check(line, "WebTome"))sWebTome = line.c_str();
			if (INI_Value_Check(line, "WebLotto"))sWebLotto = line.c_str();


			for (unsigned int i = 0; i < EventsMax; i++)
				if (INI_Value_Check(line, "Event" + std::to_string(i)))
				{
					Events[i].Name = entry(line.c_str(), 0);					
					Events[i].Start = atoi(entry(line.c_str(), 1).c_str());
					Events[i].End = atoi(entry(line.c_str(), 2).c_str());
					Events[i].Hide = atoi(entry(line.c_str(), 3).c_str());
					Events[i].RankType = atoi(entry(line.c_str(), 4).c_str());
				}

			ifFile.clear();
		}
		
		ifFile.close();
	}
	MISE;
}

void LOAD::StartUp()
{
	MISS;
	Load_Settings("Settings.ini");
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

#ifdef BrokerPVP
int LOAD::ProcessArg(int argc, char** argv)
{
	MISS;
	CLI::App app{ "Live PVP" };

	app.add_option("--PMV", sLivePvPPMV, "PMV File to Oopen");
	app.add_option("--SETTING", sSetting, "SETTING");

	CLI11_PARSE(app, argc, argv);

	MISE;
	if (sLivePvPPMV != "")return 1;
	return 0;
}
#endif


#ifdef MIS_Count

void LOAD::Load_Count()
{
	MISS;

	mtxCount.lock();
	std::string line;
	std::string sName;
	std::ifstream ifFile;

	sName = "ReplayCount.ini";
	ifFile.open(sName.c_str(), std::ios::binary);
	if (ifFile.good())
	{
		getline(ifFile, line);
		iReplay = atoi(line.c_str());
		ifFile.clear();
		ifFile.close();
	}

	mtxCount.unlock();
	MISE;
}
void LOAD::Save_Count()
{
	MISS;
	mtxCount.lock();
	std::string sName;
	std::ofstream ofFile;

	sName = "ReplayCount.ini";
	ofFile.open(sName.c_str(), std::ios::binary);
	if (ofFile.good())
	{
		ofFile << iReplay;
		ofFile.close();
	}

	mtxCount.unlock();
	MISE;
}
#endif