#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"

class LOAD //: public Thread_MIS
{
public:

	void StartUp();
	    	
	string sSQL_Server;
	string sSQL_User;
	string sSQL_PW;
	string sSQL_DB;

	string sPMV_PATH;
	string sPMV_AUTO_PATH;
	string sPMV_ARCH_PATH;

	string sTMP_PATH;

	//BROKER
	static broker* Bro;
	void teachL() { Bro->L = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	
	void Load_Settings();
private:

	bool INI_Value_Check(string &check, string name);

};

#endif //LOAD_H

