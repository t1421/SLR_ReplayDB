#include "..\incl\Broker.h" 

#define Log_path "LOG/"
#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>

#include "..\incl\DEBUG.h"


broker *(DEBUG::Bro) = NULL;

DEBUG::DEBUG(std::string sLogName, bool _bGUI, bool _bFile, bool _bFilter)
{
	bGUI = _bGUI;
	bFile = _bFile;
	bFilter = _bFilter;


		//printf("DEBUG WIRD GESTARTET -->\n");

		Fill_DBArray("*", "*", "*", "true");
		

		/////////////////////////////////////////////////////
		///Fill_DBArray("DEBUG", "*", "*", "true");
		/////////////////////////////////////////////////////
		Fill_DBArray("E", "*", "*", "true"); //ERRORS

		Fill_DBArray("", "*", "*", "true"); // MAIN

		Fill_DBArray("CardBaseSMJ", "*", "*", "true");		
		Fill_DBArray("CardBaseSMJ", "OpenBooster", "*", "true");
		Fill_DBArray("CardBaseSMJ", "GetImage", "*", "true");
		Fill_DBArray("CardBaseSMJ", "ConvertImage", "*", "false");
		Fill_DBArray("CardBaseSMJ", "DownloadImage", "*", "false");
		Fill_DBArray("CardBaseSMJ", "GetActionOrbForCardID", "*", "false");
		

		Fill_DBArray("Replay", "*", "*", "true");
		Fill_DBArray("Replay", "SwitchType", "*", "false"); 
		Fill_DBArray("Replay", "FindWinningTeam", "*", "false");
		Fill_DBArray("Replay", "CountActions", "*", "false");
		Fill_DBArray("Replay", "readDelta", "*", "false");
		
		
		Fill_DBArray("Reader", "*", "*", "false");
		Fill_DBArray("Reader", "SaveFile", "*", "true");
		
		Fill_DBArray("PMV_to_SQL", "*", "*", "true");

		Fill_DBArray("Imager", "*", "*", "true");

		Fill_DBArray("LOAD", "*", "*", "true");
		Fill_DBArray("LOAD", "INI_Value_Check", "*", "false");

		Fill_DBArray("Thread_MIS", "*", "*", "true");

		
		Fill_DBArray("Manager", "*", "*", "true");	
		Fill_DBArray("Manager", "processActions", "*", "false");
		Fill_DBArray("Manager", "SetCard", "*", "false");
		Fill_DBArray("Manager", "SetCardBack", "*", "false");
		Fill_DBArray("Manager", "SetPlayer", "*", "false");
		Fill_DBArray("Manager", "AddCardToPlayer", "*", "false");
		Fill_DBArray("Manager", "FillActionLog", "*", "false");
		Fill_DBArray("Manager", "SetActionLog", "*", "false");
		Fill_DBArray("Manager", "UpdateActionPerSec", "-->", "false");
		Fill_DBArray("Manager", "UpdateActionPerSec", "<--", "false");
		Fill_DBArray("Manager", "SetActionsPerSec", "-->", "false");
		Fill_DBArray("Manager", "SetActionsPerSec", "<--", "false");
		Fill_DBArray("Manager", "AddActionPerSec", "*", "false");
		Fill_DBArray("Manager", "UpdateFiles", "*", "false");
		

		Fill_DBArray("SQL_MIS_New", "*", "*", "true");
		Fill_DBArray("SQL_MIS_New", "send", "*", "false");
		Fill_DBArray("SQL_MIS_New", "clearString", "*", "false");
		Fill_DBArray("SQL_MIS_New", "SendBLOB", "*", "false");
				
		Fill_DBArray("WEB_Main", "*", "*", "true");
		Fill_DBArray("WEB_Server", "*", "*", "true");		
		Fill_DBArray("WEB_Server", "postChatEvent", "*", "false");
		Fill_DBArray("WEB_Toolbar", "*", "*", "true");
		Fill_DBArray("WEB_Container_Analyser", "*", "*", "true");
		
		Fill_DBArray("WEB_Container_Tome", "*", "*", "true");
		Fill_DBArray("WEB_Container_Tome", "processChatEvent", "*", "false");
		Fill_DBArray("WEB_Container_Tome", "DrawBooster", "*", "false");
		Fill_DBArray("WEB_Container_Tome", "DrawBooster", "*", "false");
		Fill_DBArray("WEB_Container_Tome", "BoosterToFilter", "*", "false");


		Fill_DBArray("WEB_Tome_Admin", "*", "*", "true");
		Fill_DBArray("WEB_Tome_Login", "*", "*", "true");
		Fill_DBArray("WEB_Tome_Debug", "*", "*", "true");
		Fill_DBArray("WEB_Tome_Player", "*", "*", "true");
		Fill_DBArray("WEB_Tome_Public", "*", "*", "true");

		Fill_DBArray("WEB_Tome_PublicBoosters", "*", "*", "true");
		Fill_DBArray("WEB_Tome_PublicPlayers", "*", "*", "true");
		Fill_DBArray("WEB_Tome_PublicCards", "*", "*", "true");
		Fill_DBArray("WEB_Tome_PublicPlayersBooster", "*", "*", "true");

		Fill_DBArray("WEB_Tome_Leave", "*", "*", "true");
		

		Fill_DBArray("Tome_Game", "*", "*", "true");
		Fill_DBArray("Tome_Game", "AllBoostersMax", "*", "false");
		Fill_DBArray("Tome_Game", "AllBoosters", "*", "false");
		Fill_DBArray("Tome_Game", "bSaveGame", "*", "false");
		
		
		Fill_DBArray("WEB_Event", "*", "*", "true");

		Fill_DBArray("WEB_Rank", "*", "*", "true");

		Fill_DBArray("MIS_Rank", "*", "*", "true");

		Fill_DBArray("WEB_Analyser", "*", "*", "true");	
		Fill_DBArray("WEB_Analyser_Head", "*", "*", "true");
		Fill_DBArray("WEB_Analyser_Deck", "*", "*", "true");
		Fill_DBArray("WEB_Analyser_Acti", "*", "*", "true");

		Fill_DBArray("broker", "*", "*", "true");

		Fill_DBArray("()", "*", "*", "true"); //lambda

		
		Fill_DBArray("LottoWeek", "*", "*", "true");
		Fill_DBArray("WEB_Container_Lotto", "*", "*", "true");
		Fill_DBArray("WEB_Lotto_Admin", "*", "*", "true");
		Fill_DBArray("WEB_Lotto_Admin_Main", "*", "*", "true");
		Fill_DBArray("WEB_Lotto_Admin_Pull", "*", "*", "true");
		Fill_DBArray("WEB_Lotto_Week", "*", "*", "true");

		Fill_DBArray("Challonge", "*", "*", "true");
		Fill_DBArray("Challonge", "WEBRequestToCHASH", "*", "false");

		Fill_DBArray("Quiz", "*", "*", "true");
		Fill_DBArray("Question", "*", "*", "true");
		Fill_DBArray("Question", "SetCountDown", "*", "false");
		Fill_DBArray("Question", "CleanString", "*", "false");
		Fill_DBArray("Question", "splitString", "*", "false");

		
		/////////////////////////////////////////////////////

		if (bFile)ofB.open(Log_path + sLogName + ".log", std::ios::binary);
		ofE.open(Log_path + sLogName + "_E.log", std::ios::binary | std::ofstream::app);

		//printf("DEBUG WIRD GESTARTET <--\n");

}


void DEBUG::Fill_DBArray(std::string Modul, std::string Funktion, std::string Wert, std::string Status)
{
	std::vector<std::string> vs;
	DebugInfo.push_back(vs);

	DebugInfo[DebugInfo.size() - 1].push_back(Modul);
	DebugInfo[DebugInfo.size() - 1].push_back(Funktion);
	DebugInfo[DebugInfo.size() - 1].push_back(Wert);
	DebugInfo[DebugInfo.size() - 1].push_back(Status);
}

void DEBUG::StatusE(std::string Modul, std::string Funktion, std::string Wert)
{
	ofE << Modul << ";" << Funktion << ";" << Wert << std::endl;
	StatusNew(Modul + "::" + Funktion, Wert);
}

void DEBUG::StatusNew(std::string Fun, std::string Wert)
{
	std::string sClass = "";
	std::string sMethode;

	size_t colons = Fun.find("::");

	if (colons != std::string::npos)
	{
		sMethode = Fun.substr(colons + 2, Fun.rfind("("));		
		if(Fun.find(" ")!= std::string::npos)
			sClass = Fun.substr(Fun.find(" ") + 1, colons - Fun.find(" ") - 1);
		else sClass = Fun.substr(0,colons);
	}
	else sMethode = Fun.substr(0, Fun.rfind("("));

	if ( bGUI == false &&
		bFile == false)return;

	t = time(NULL);	
	localtime_s(&ts, &t);

	if (bFilter && (Wert == "-->" || Wert == "<--"))return;

	if(bGUI || bFile)
		if (check_MFW(sClass, sMethode, Wert))
		{
			mtx.lock();
			if (bGUI)
			{
				printf("%02i:%02i:%02i - %-20.20s %-20.20s %-60.60s\n", ts.tm_hour, ts.tm_min, ts.tm_sec,
					sClass.c_str(), sMethode.c_str(), Wert.c_str());
			}
			if (bFile)
			{
				ofB << ts.tm_hour << ":" << ts.tm_min << ":" << ts.tm_sec << ";";
				ofB << sClass.c_str() << ";" << sMethode.c_str() << ";" << Wert.c_str() << std::endl;
			}
			mtx.unlock();
		}

}

bool DEBUG::check_MFW(std::string Modul, std::string Funktion, std::string Wert)
{
	std::string return_ = "";

	for (unsigned int i = 0; i < DebugInfo.size(); i++)
	{
		if (DebugInfo[i][0] == Modul &&
			DebugInfo[i][1] == "*" &&
			DebugInfo[i][2] == "*")return_ = DebugInfo[i][3];

		if (DebugInfo[i][0] == Modul &&
			DebugInfo[i][1] == Funktion &&
			DebugInfo[i][2] == "*")return_ = DebugInfo[i][3];

		if (DebugInfo[i][0] == Modul &&
			DebugInfo[i][1] == Funktion &&
			DebugInfo[i][2] == Wert)return_ = DebugInfo[i][3];
	}

	if (return_ == "true")return true;

	return false;
}
