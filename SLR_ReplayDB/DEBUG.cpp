#include "stdafx.h"

#include "DEBUG.h"

broker *(DEBUG::Bro) = NULL;

DEBUG::DEBUG(string sLogName)
{
	bGUI = true;
	bFile = true;
	bFilter = false;


		printf("DEBUG WIRD GESTARTET -->\n");

		Fill_DBArray("*", "*", "*", "true");
		

		/////////////////////////////////////////////////////
		///Fill_DBArray("DEBUG", "*", "*", "true");
		/////////////////////////////////////////////////////
		Fill_DBArray("E", "*", "*", "true"); //ERRORS

		Fill_DBArray("", "*", "*", "true"); // MAIN

		Fill_DBArray("CardBase", "*", "*", "false");

		Fill_DBArray("Replay", "*", "*", "true");
		Fill_DBArray("Replay", "sTime", "*", "false");
		Fill_DBArray("Replay", "FindWinningTeam", "*", "false");
		
		Fill_DBArray("Reader", "*", "*", "true");
		//Fill_DBArray("Reader", "readString", "*", "false");
		
		Fill_DBArray("PMV_to_SQL", "*", "*", "true");

		Fill_DBArray("Imager", "*", "*", "true");

		Fill_DBArray("LOAD", "*", "*", "true");
		Fill_DBArray("LOAD", "INI_Value_Check", "*", "false");

		Fill_DBArray("Thread_MIS", "*", "*", "true");

		Fill_DBArray("Manager", "*", "*", "true");

		Fill_DBArray("SQL_MIS_New", "*", "*", "true");
		Fill_DBArray("SQL_MIS_New", "send", "*", "false");
		Fill_DBArray("SQL_MIS_New", "clearString", "*", "false");
		Fill_DBArray("SQL_MIS_New", "SendBLOB", "*", "false");
		
		
		
		Fill_DBArray("broker", "*", "*", "true");

		/////////////////////////////////////////////////////

		if (bFile)ofB.open(Log_path + sLogName + ".log", ios::binary);
		ofE.open(Log_path + sLogName + "_E.log", ios::binary | std::ofstream::app);

		printf("DEBUG WIRD GESTARTET <--\n");

}


void DEBUG::Fill_DBArray(string Modul, string Funktion, string Wert, string Status)
{
	std::vector<string> vs;
	DebugInfo.push_back(vs);

	DebugInfo[DebugInfo.size() - 1].push_back(Modul);
	DebugInfo[DebugInfo.size() - 1].push_back(Funktion);
	DebugInfo[DebugInfo.size() - 1].push_back(Wert);
	DebugInfo[DebugInfo.size() - 1].push_back(Status);
}

void DEBUG::StatusE(string Modul, string Funktion, string Wert)
{
	ofE << Modul << ";" << Funktion << ";" << Wert << endl;
	StatusNew(Modul + "::" + Funktion, Wert);
}

void DEBUG::StatusNew(string Fun, string Wert)
{
	string sClass = "";
	string sMethode;

	size_t colons = Fun.find("::");

	if (colons != std::string::npos)
	{
		sMethode = Fun.substr(colons + 2, Fun.rfind("("));
		sClass = Fun.substr(0, colons);
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
				ofB << sClass.c_str() << ";" << sMethode.c_str() << ";" << Wert.c_str() << endl;
			}
			mtx.unlock();
		}

}

bool DEBUG::check_MFW(string Modul, string Funktion, string Wert)
{
	string return_ = "";

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
