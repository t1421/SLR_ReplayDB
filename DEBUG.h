#ifndef DEBUG_H
#define DEBUG_H
#include "Broker.h"

class SQL_MIS_New;

#include <string>
#include <mutex> 
#include <vector>
#include <fstream>

class DEBUG
{
public:
	bool bGUI;
	bool bFile;
	bool bFilter;

	DEBUG(std::string sLogName, bool _bGUI, bool _bFile, bool _bFilter);
	
	void StatusE(std::string Modul, std::string Funktion, std::string Wert);
	void StatusNew(std::string Fun, std::string Wert);
	bool check_MFW(std::string Modul, std::string Funktion, std::string Wert);
	void Fill_DBArray(std::string Modul, std::string Funktion, std::string Wert, std::string Status);
	
	std::vector<std::vector<std::string>> DebugInfo;
	
    time_t t;
    struct tm ts ;

	std::ofstream ofB;
	std::ofstream ofE;

	std::mutex mtx;

	static broker* Bro;
	void teachB() { Bro->B = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }	

protected:

	
private:

};

#endif //DEBUG_H


