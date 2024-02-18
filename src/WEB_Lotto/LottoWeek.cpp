#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Lotto\LottoWeek.h"
#include "..\..\incl\Utility.h"

#include <fstream>

broker *(LottoWeek::Bro) = NULL;

bool LottoWeek::bLoadGame(unsigned int _iWeek)
{
	MISS;
	std::string line;
	std::string sName = Bro->L_getLOTTO_SAVE_PATH() + std::to_string(_iWeek);

	std::ifstream ifFile;
	ifFile.open(sName.c_str(), std::ios::binary);
	unsigned int iCountSemi;
	

	if (ifFile.good())
	{
		MISD("good");

		while (getline(ifFile, line))
		{
			line.erase(line.size() - 1);

			//MainSettings
			if (INI_Value_Check(line, "W"))
			{												
				iWeek = atoi(entry(line, 0).c_str()); 
				iBFP = atoi(entry(line, 1).c_str());
				iStatus = atoi(entry(line, 2).c_str());
			}

			//PulledCards
			if (INI_Value_Check(line, "C"))
			{
				iCountSemi = 0;
				for (char character : line)
					if (character == ';')
						iCountSemi++;

				for (unsigned int i = 0; i < iCountSemi; i++)
					vCardsPulled.push_back(entry(line, 0 + i).c_str());
			}

			//Player
			if (INI_Value_Check(line, "P"))
			{
				vPlayer.push_back(new Lotto_Player(
					entry(line, 0), 
					entry(line, 1),
					entry(line, 2)));				
			}

			//Player Cards
			if (INI_Value_Check(line, "PC"))
			{
				iCountSemi = 0;
				for (char character : line) 
					if (character == ';') 
						iCountSemi++;

				for (unsigned int i = 0; i < iCountSemi - 1; i++)
					vPlayer[vPlayer.size() - 1]->vSimpleDeck.push_back(entry(line, 2 + i).c_str());
			}
				
			ifFile.clear();
		}
		ifFile.close();
	}
	else
	{
		MISEA("No Game");
		return false;
	}
	
	MISE;
	return true;
}


bool LottoWeek::bSaveGame()
{
	MISS;

	std::string line;
	std::string sName = Bro->L_getTOME_SAVE_PATH() + std::to_string(iWeek);
	
	std::ofstream ofFile;
	ofFile.open(sName.c_str(), std::ios::binary);

	if (ofFile.good())
	{
		MISD("good");
		ofFile << "G=" << iWeek
			<< ";" << iBFP
			<< ";" << iStatus
			<< ";\n";

		ofFile << "C=";
		for each(std::string C in vCardsPulled) ofFile << C << ";";
		ofFile << "\n";

		for (unsigned int i = 0; i < vPlayer.size(); i++)
		{
			ofFile << "P=" << vPlayer[i]->sPlayerID
				<< ";" << vPlayer[i]->sPlayerName 
				<< ";" << vPlayer[i]->sGameID
			    << ";\n";
#
			ofFile << "PC=";
			for each (std::string C in vPlayer[i]->vSimpleDeck)ofFile << C << ";";
			ofFile << "\n";	
		}
		ofFile.close();
	}
	
	MISE;
	return true;
}
