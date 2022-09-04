#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"

struct CsvCard {
	unsigned short CardID;
	unsigned int   iFire;
	unsigned int   iFrost;
	unsigned int   iShadow;
	unsigned int   iNature;
	unsigned int   iNeutral;
	CsvCard(unsigned short _CardID,
		unsigned int   _iFire,
		unsigned int   _iFrost,
		unsigned int   _iShadow,
		unsigned int   _iNature,
		unsigned int   _iNeutral) :
		CardID(_CardID), iFire(_iFire), iFrost(_iFrost) , iShadow(_iShadow), iNature(_iNature), iNeutral(_iNeutral){}
};

class LOAD //: public Thread_MIS
{
public:

	void StartUp();

	void LoadCards();
	    	
	string sSQL_Server;
	string sSQL_User;
	string sSQL_PW;
	string sSQL_DB;

	string sPMV_PATH;
	string sPMV_AUTO_PATH;
	string sPMV_ARCH_PATH;

	string sTMP_PATH;
	string sFFMPEG;

	vector <CsvCard*> CsvAllCards;

	//BROKER
	static broker* Bro;
	void teachL() { Bro->L = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

protected:
	
	void Load_Settings();
private:

	bool INI_Value_Check(string &check, string name);
	string entry(string Liste, int pos);

};

#endif //LOAD_H

