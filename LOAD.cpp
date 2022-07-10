//#define DF_Debug

#include "prototypes.h"

#include "LOAD.h"

broker *(LOAD::Bro) = NULL;

void LOAD::Load_Settings()
{
	MISS;
	string line;
	string sName = "Settings.ini";

	ifstream ifFile;
	ifFile.open(sName.c_str(), ios::binary);

	if (ifFile.good())
	{
		MISD("good");
		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			if (INI_Value_Check(line, "SQL_Server"))sSQL_Server = line.c_str();
			if (INI_Value_Check(line, "SQL_User"))sSQL_User = line.c_str();
			if (INI_Value_Check(line, "SQL_PW"))sSQL_PW = line.c_str();
			if (INI_Value_Check(line, "SQL_DB"))sSQL_DB = line.c_str();

			if (INI_Value_Check(line, "PMV_PATH"))sPMV_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_AUTO_PATH"))sPMV_AUTO_PATH = line.c_str();
			if (INI_Value_Check(line, "PMV_ARCH_PATH"))sPMV_ARCH_PATH = line.c_str();

			if (INI_Value_Check(line, "TMP_PATH"))sTMP_PATH = line.c_str();
				
		}
		
		ifFile.close();
	}
	MISE;
}

void LOAD::StartUp()
{
	MISS;
	Load_Settings();
	MISE;
}

bool LOAD::INI_Value_Check(string &check, string name)
{
	MISS;
	if (check.substr(0, check.find("=")) == name)
	{
		check.erase(0, check.find("=") + 1);
		MISEA(" true: " + check);
		return true;
	}
	else
	{
		MISEA(" false");
		return false;
	}
}