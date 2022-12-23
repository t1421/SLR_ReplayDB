#ifndef LOAD_H
#define LOAD_H

#include "Thread_MIS.h"

#include <string>
#include <vector>

struct CsvCard {
	unsigned short CardID;
	unsigned int   iFire;
	unsigned int   iFrost;
	unsigned int   iShadow;
	unsigned int   iNature;
	unsigned int   iNeutral;
	bool		   bUnit;
	bool		   bSpell;
	bool		   bBuilding;
	CsvCard(unsigned short _CardID,
		unsigned int   _iFire,
		unsigned int   _iFrost,
		unsigned int   _iShadow,
		unsigned int   _iNature,
		unsigned int   _iNeutral,
		bool		   _bUnit,
		bool		   _bSpell,
		bool		   _bBuilding) :
		CardID(_CardID), iFire(_iFire), iFrost(_iFrost) , iShadow(_iShadow), iNature(_iNature), iNeutral(_iNeutral),bUnit(_bUnit),bSpell(_bSpell),bBuilding(_bBuilding) {}
};

class LOAD //: public Thread_MIS
{
public:

	void StartUp();

	void LoadCards();
	    	
	std::string sSQL_Server;
	std::string sSQL_User;
	std::string sSQL_PW;
	std::string sSQL_DB;

	std::string sPMV_PATH;
	std::string sPMV_AUTO_PATH;
	std::string sPMV_ARCH_PATH;

	std::string sRANK_PATH;

	std::string sTMP_PATH;
	std::string sFFMPEG;

	int BOTRankMode[BOTXLIST];

	std::vector <CsvCard*> CsvAllCards;

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

