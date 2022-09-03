#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

///Globale Def
//#define DF_Debug

#ifdef DF_Debug 
#define MISD(___Mes___) Bro->B->StatusNew(__FUNCTION__, ___Mes___);
#define MISERROR(___Mes___)Bro->B->StatusE("E", __FUNCTION__, ___Mes___);
#define MISS MISD("-->");
#define MISE MISD("<--");
#define MISEA(___Mes___) MISD("<-- " ___Mes___);

#else
#define MISD(___Mes___); 
#define MISERROR(___Mes___)Bro->B->StatusE("E", __FUNCTION__, ___Mes___);
#define MISS
#define MISE
#define MISEA(___Mes___);
#endif

///Lib Includes
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h> 
#include <thread>
#include <mutex> 

///Names Spaces
using namespace std;

///Pfad Constanten
static string Log_path			= "LOG\\";
static string CardWebURL    	= "https://hub.backend.skylords.eu/api/auctions/cards?id=all";
static string WikiPre           = "https://skylords-reborn.fandom.com/wiki/";
static string WikiPos           = "_Card_Artwork.png";



//enum STATUS { eWait, eStart, eRunning };
//enum THREADTYP { eI, eW, eWS, eK, eO, eF, eL, eFB, eMAIN, THREADTYP_MAX };
//enum SETTINGTYP {eB_Gui, eB_File, eB_Filter,SETTINGTYP_MAX};


inline bool File_exists(const std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}

inline string ReplaceString(string subject, const string& search, const string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

#endif /* PROTOTYPES_H_ */

#ifndef noBroker
#include "Broker.h"
#endif

#ifndef noDebug
#include "DEBUG.h"
#endif