#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"

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

	std::string sChallongeUser;
	std::string sChallongeAPIKEY;
	std::string sChallongeSaveDir;

	//int BOTRankMode[BOTXLIST + 1];
	int EEEStatus;
	unsigned long int EEE_Start[EEESize];
	unsigned long int EEE_End[EEESize];

	int EventStatus[SLR_Events];
	
	void Load_Settings(std::string sName);

	//BROKER
	static broker* Bro;
	void teachL() { Bro->L = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	
	
private:
	std::string entry(std::string Liste, int pos);

};

#endif //LOAD_H



