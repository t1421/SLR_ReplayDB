#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"

#include <string>
#include <vector>

struct TomeStruct;

class LOAD //: public Thread_MIS
{
public:

	void StartUp();
	TomeStruct Load_TomeGameHead(std::string sGameID);

	std::string sSQL_Server;
	std::string sSQL_User;
	std::string sSQL_PW;
	std::string sSQL_DB;

	std::string sPMV_PATH;
	std::string sPMV_AUTO_PATH;
	std::string sPMV_ARCH_PATH;

	std::string sRANK_PATH;

	std::string sTOME_SAVE_PATH;

	std::string sTMP_PATH;
	std::string sSMJPIC_PATH;
	std::string sSMJIMG_PATH;
	std::string sSMJPICSMALL_PATH;
	std::string sFFMPEG;

	int BOTRankMode[BOTXLIST + 1];

	//BROKER
	static broker* Bro;
	void teachL() { Bro->L = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	
	void Load_Settings();
private:

	bool INI_Value_Check(std::string &check, std::string name);
	std::string entry(std::string Liste, int pos);

};

#endif //LOAD_H

