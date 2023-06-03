#include "incl\Broker.h" 
#include "incl\DEBUG.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#define OneErrorLeave false

int main(int argc, char **argv)
{
	int error = 0;
	unsigned int iCoundPlayers = 0;
	unsigned int iStartPosSolo = 0;
	bool dublette;

	
	std::vector<std::pair<std::string, unsigned long>> Walls;
	std::vector<std::pair<std::string, unsigned long>> Amii;
	std::vector<std::pair<std::string, unsigned long>> Orb;
		
	if (!argc > 1)
	{
		printf("Drag and Drop you PMV on the Applikation\n");
		system("pause");
		return 0;
	}
	
	std::string sFile = std::string(argv[1]);
	printf("File %s\n", sFile.c_str());

	broker* Bro = new broker;

	DEBUG* B = new DEBUG("SLR_ReplayDB",true,false,false);
	B->teachB();		
	Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
	Bro->B->Fill_DBArray("OK", "*", "*", "true");
	Bro->B->Fill_DBArray("-", "*", "*", "true");

	Replay * RR = new Replay();
	if (RR->LoadPMV(sFile))
	{	
		Bro->B->StatusE("OK", "OpenFile", "");

		Bro->B->StatusE("", "ReplayTime",sTime(RR->Playtime));
		Bro->B->StatusE("", "LastAction", sTime(RR->ActionMatrix[RR->ActionMatrix.size() - 1]->Time));

		// Game Version CHeck
		if (RR->GameVersion = 400042)Bro->B->StatusE("OK", "GameVersion", std::to_string(RR->GameVersion));
		else
		{
			Bro->B->StatusE("ERROR", "GameVersion", std::to_string(RR->GameVersion));
			if(OneErrorLeave)return -1;
			else error = -1;
		}

		// Map CHeck
		if (RR->MapName == "11303_PvE_04p_KingOfTheGiants.map")Bro->B->StatusE("OK", "Map", RR->MapName);
		else
		{
			Bro->B->StatusE("ERROR", "Map", RR->MapName);
			if (OneErrorLeave)return -2;
			else error = -2;
		}

		// Div Check
		if (RR->DifficultyID == 3)Bro->B->StatusE("OK", "Difficulty", std::to_string(RR->DifficultyID));
		else
		{
			Bro->B->StatusE("ERROR", "Difficulty", std::to_string(RR->DifficultyID));
			if (OneErrorLeave)return -3;
			else error = -3;
		}


		Bro->B->StatusE("-", "---------", "---------");
		//Check Walls
		for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
		{
			if (RR->ActionMatrix[i]->Type != 4007) continue;

			if (   RR->ActionMatrix[i]->AdditionalInfo != "523"
				&& RR->ActionMatrix[i]->AdditionalInfo != "524"
				&& RR->ActionMatrix[i]->AdditionalInfo != "525"
				&& RR->ActionMatrix[i]->AdditionalInfo != "526"
				&& RR->ActionMatrix[i]->AdditionalInfo != "527"
				&& RR->ActionMatrix[i]->AdditionalInfo != "566")
				continue;

			dublette = false;
			for (unsigned int j = 0; j < Walls.size(); j++)
				if (RR->ActionMatrix[i]->AdditionalInfo == Walls[j].first)
						dublette = true;

			if (!dublette)Walls.push_back(std::make_pair(RR->ActionMatrix[i]->AdditionalInfo, RR->ActionMatrix[i]->Time));
		}
		
		if (Walls.size() == 6)Bro->B->StatusE("OK", "Walls", std::to_string(Walls.size()));
		else
		{
			Bro->B->StatusE("ERROR", "Walls", std::to_string(Walls.size()));
			if (OneErrorLeave)return -4;
			else error = -4;
		}

		for (unsigned int j = 0; j < Walls.size(); j++)
		{
			Bro->B->StatusE("-", Walls[j].first, sTime(Walls[j].second));
		}

		Bro->B->StatusE("-", "---------", "---------");

		//Check Amii-Spells
		for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
		{
			if (RR->ActionMatrix[i]->Type != 4014) continue;

			if (   RR->ActionMatrix[i]->AdditionalInfo != "2002215"
				&& RR->ActionMatrix[i]->AdditionalInfo != "2001750"
				&& RR->ActionMatrix[i]->AdditionalInfo != "2001751"
				&& RR->ActionMatrix[i]->AdditionalInfo != "2001268")
				continue;

			dublette = false;
			for (unsigned int j = 0; j < Amii.size(); j++)
				if (RR->ActionMatrix[i]->AdditionalInfo == Amii[j].first)
					dublette = true;

			if (!dublette)Amii.push_back(std::make_pair(RR->ActionMatrix[i]->AdditionalInfo, RR->ActionMatrix[i]->Time));
		}

		if (Amii.size() == 4)Bro->B->StatusE("OK", "AmiiSpells", std::to_string(Amii.size()));
		else
		{
			Bro->B->StatusE("ERROR", "AmiiSpells", std::to_string(Amii.size()));
			if (OneErrorLeave)return -5;
			else error = -5;
		}

		for (unsigned int j = 0; j < Amii.size(); j++)
		{
			Bro->B->StatusE("-", Amii[j].first, sTime(Amii[j].second));
		}

		Bro->B->StatusE("-", "---------", "---------");



		//Check Orbs + CHeck if Destreut
		for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
		{
			if (RR->ActionMatrix[i]->Type != 4031) continue;
			if (RR->ActionMatrix[i]->AdditionalInfo == "0") continue; // STart Orbs

			dublette = false;			
			for (unsigned int j = 0; j < Orb.size(); j++)
				if (RR->ActionMatrix[i]->AdditionalInfo.substr(RR->ActionMatrix[i]->AdditionalInfo.find(";") + 1) == Orb[j].first)
					dublette = true;

			if (!dublette)Orb.push_back(std::make_pair(RR->ActionMatrix[i]->AdditionalInfo.substr(RR->ActionMatrix[i]->AdditionalInfo.find(";") + 1), RR->ActionMatrix[i]->Time));
		}

		if (Orb.size() == 12)Bro->B->StatusE("OK", "Orbs", std::to_string(Orb.size()));
		else
		{
			Bro->B->StatusE("ERROR", "Orbs", std::to_string(Orb.size()));
			if (OneErrorLeave)return -6;
			else error = -6;
		}

		for (unsigned int j = 0; j < Orb.size(); j++)
		{
			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type != 4041) continue;
				
				if (RR->ActionMatrix[i]->AdditionalInfo == Orb[j].first + ";")
				{
					Bro->B->StatusE("ERROR", "OrbsKillByPlayer", Orb[j].first);
					if (OneErrorLeave)return -7;
					else error = -7;
				}
			}
		}

		for (unsigned int j = 0; j < Orb.size(); j++)
		{
			Bro->B->StatusE("-", Orb[j].first, sTime(Orb[j].second));
		}

		Bro->B->StatusE("-", "---------", "---------");
			
		}
		else Bro->B->StatusE("ERROR", "Cant_open_file", sFile);

		if (error != 0) Bro->B->StatusE("ERROR", "NotAllChecksWhereOK", "!!!FAILED!!!");
		else Bro->B->StatusE("OK", "AllChecksAreOK", "!!!VALID!!!");


	
	


	

	system("Pause");
    return 0;
}

