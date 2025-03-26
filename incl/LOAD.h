#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"
#include "DataTypes.h"

#include <string>
#include <vector>

class LOAD //: public Thread_MIS
{
public:

	void StartUp();

	std::string sSQL_Server;
	std::string sSQL_User;
	std::string sSQL_PW;
	std::string sSQL_DB;
	std::string sAdminKey;

	std::string sWebAnalyser;
	std::string sWebTome;
	std::string sWebLotto;

	std::string sPMV_PATH;
	std::string sPMV_AUTO_PATH;
	std::string sPMV_ARCH_PATH;
	std::string sPMV_WEB_PATH;
	
	std::string sRANK_PATH;
	std::string sTOME_SAVE_PATH;
	std::string sLOTTO_SAVE_PATH;

	std::string sTMP_PATH;
	std::string sSMJPIC_PATH;
	std::string sSMJIMG_PATH;
	std::string sSMJPICSMALL_PATH;
	std::string sLOTTOPIC_PATH;
	std::string sBOOSTER_PATH;
	std::string sMAPPIC_PATH;
	std::string sFFMPEG;

	std::string sLivePvPPMV;
	std::string sLivePvP_OBS_Export;
	std::string sLivePvP_Pics;
	int iLivePvPRefreshRate;
	int iLivePvPActionLog;

	std::string sChallongeUser;
	std::string sChallongeAPIKEY;
	std::string sChallongeSaveDir;

	std::string sQuizPath;
	int iCountDown;
	int iCoolDown;

	unsigned long iSRFileVersion;
	unsigned long iSRGameVersion;

	std::string sSetting;

	EventData Events[EventsMax];
	
	void Load_Settings(std::string sName);

#ifdef BrokerPVP
	int LOAD::ProcessArg(int argc, char** argv);
#endif

#ifdef MIS_Count
	unsigned int iReplay;
	std::mutex mtxCount;
	void Load_Count();
	void Save_Count();
	void ReplayPlus() { mtxCount.lock(); iReplay++; mtxCount.unlock(); Save_Count(); };
#endif

	//BROKER
	static broker* Bro;
	void teachL() { Bro->L = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }




protected:
	
	
private:
	std::string entry(std::string Liste, int pos);

};

#endif //LOAD_H



