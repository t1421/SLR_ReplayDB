#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

///Globale Def
#define DF_Debug

#ifdef DF_Debug 
#define MISD(___Mes___) Bro->B->StatusNew(__FUNCTION__, ___Mes___);
#define MISERROR(___Mes___)Bro->B->StatusE("E", __FUNCTION__, ___Mes___);
#define MISS MISD("-->");
#define MISE MISD("<--");
#define MISEA(___Mes___) MISD("<-- " ___Mes___);

#else
#define MISD(___Mes___); 
//#define MISERROR(___Mes___); 
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

///Settings für Speek
#define talk_Port      6666
#define SQL_Server    "192.168.0.4"
#define SQL_User      "SLR"
#define SQL_PW        "SkyLordsReBorn"
#define SQL_DB        "replaydb"

///Pfad Constanten
static string Save_path         = "K:\\c++\\SLR_ReplayDB\\Release\\SAVE\\";
static string Log_path			= "K:\\c++\\SLR_ReplayDB\\Release\\LOG\\";
static string Tmp_path          = "K:\\c++\\SLR_ReplayDB\\Release\\TMP\\";
static string PMV_path          = "K:\\c++\\SLR_ReplayDB\\Release\\REPLAY\\";
static string PMV_Arch          = "K:\\c++\\SLR_ReplayDB\\Release\\REPLAY_ARCH\\";
static string CardWebURL    	= "https://hub.backend.skylords.eu/api/auctions/cards?id=all";
static string WikiPre           = "https://skylords-reborn.fandom.com/wiki/";
static string WikiPos           = "_Card_Artwork.png";



enum STATUS { eWait, eStart, eRunning };
enum THREADTYP { eI, eW, eWS, eK, eO, eF, eL, eFB, eMAIN, THREADTYP_MAX };
enum SETTINGTYP {eB_Gui, eB_File, eB_Filter,SETTINGTYP_MAX};


#endif /* PROTOTYPES_H_ */
