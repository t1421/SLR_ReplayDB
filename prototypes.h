#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

///Globale Def
//#define DF_Debug

//#ifdef DF_Debug 
//#define MISD(___Mes___) Bro->B->StatusNew(__FUNCTION__, ___Mes___);
//#define MISERROR(___Mes___)Bro->B->StatusE("E", __FUNCTION__, ___Mes___);
//#define MISS MISD("-->");
//#define MISE MISD("<--");
//#define MISEA(___Mes___) MISD("<-- " ___Mes___);

#ifdef DF_Debug 
#define MISD(___Mes___) Bro->B_StatusNew(__FUNCTION__, ___Mes___);
#define MISERROR(___Mes___)Bro->B_StatusE("E", __FUNCTION__, ___Mes___);
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
//#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h> 
#include <thread>
#include <mutex> 

///Names Spaces
//using namespace std;

///Pfad Constanten
//static std::string Log_path			= "LOG\\";
//static std::string CardWebURL    	= "https://hub.backend.skylords.eu/api/auctions/cards?id=all";
//static std::string WikiPre           = "https://skylords-reborn.fandom.com/wiki/";
//static std::string WikiPos           = "_Card_Artwork.png";

#endif /* PROTOTYPES_H_ */

#ifndef noBroker
#include "Broker.h"
#endif

#ifndef noDebug
#include "DEBUG.h"
#endif