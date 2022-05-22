#ifndef DEBUG_H
#define DEBUG_H

class SQL_MIS_New;

class DEBUG
{
public:
	bool bGUI;
	bool bFile;
	bool bFilter;

	DEBUG(string sLogName);
	
	void StatusE(string Modul, string Funktion, string Wert);
	void StatusNew(string Fun, string Wert);
	bool check_MFW(string Modul, string Funktion, string Wert);
	void Fill_DBArray(string Modul, string Funktion, string Wert, string Status);
	
	vector<vector<string>> DebugInfo;
	
    time_t t;
    struct tm ts;

	ofstream ofB;
	ofstream ofE;

	mutex mtx;

	static broker* Bro;
	void teachB() { Bro->B = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }	

protected:

	
private:

};

#endif //DEBUG_H


