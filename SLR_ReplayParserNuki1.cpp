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

	std::vector<unsigned int> PowerWells;
	std::vector<unsigned int> Transforms;
	std::vector<std::string> Cards;
	
	//unsigned int CardsCound = 0;
	//unsigned int CardsCoundTotal = 0;
	//Card Cards[4][20];
	if (argc > 1)
	{
		std::string sFile = std::string(argv[1]);
		printf("File %s\n", sFile.c_str());

		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_ReplayDB",true,false,false);
		B->teachB();		
		Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
		Bro->B->Fill_DBArray("OK", "*", "*", "true");

		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{	
			Bro->B->StatusE("OK", "OpenFile", "");

			// Game Version CHeck
			if (RR->GameVersion = 400039)Bro->B->StatusE("OK", "GameVersion", std::to_string(RR->GameVersion));
			else
			{
				Bro->B->StatusE("ERROR", "GameVersion", std::to_string(RR->GameVersion));
				if(OneErrorLeave)return -1;
				else error = -1;
			}

			// Map CHeck
			if (RR->MapName == "11202_PvE_02p_MadGod.map")Bro->B->StatusE("OK", "Map", RR->MapName);
			else
			{
				Bro->B->StatusE("ERROR", "Map", RR->MapName);
				if (OneErrorLeave)return -2;
				else error = -2;
			}

			// Div Check
			if (RR->DifficultyID == 2)Bro->B->StatusE("OK", "Difficulty", std::to_string(RR->DifficultyID));
			else
			{
				Bro->B->StatusE("ERROR", "Difficulty", std::to_string(RR->DifficultyID));
				if (OneErrorLeave)return -3;
				else error = -3;
			}

			// Left Game Check
			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
				if (RR->ActionMatrix[i]->Type == 4002)
				{
					Bro->B->StatusE("ERROR", "LeftCheck", sTime(RR->ActionMatrix[i]->Time));
					if (OneErrorLeave)return -8;
					else error = -8;
				}
			if (RR->DifficultyID == 1)Bro->B->StatusE("OK", "LeftCheck", "NoOne");
				

			for (unsigned i = 0; i < RR->PlayerMatrix.size(); i++)
			{
				if (RR->PlayerMatrix[i]->Name == "pl_Enemy1") continue;
				if (RR->PlayerMatrix[i]->Name == "pl_Player2")
				{
					iStartPosSolo = 1;
					continue;
				}
				if (RR->PlayerMatrix[i]->Name == "pl_Player1")
				{
					iStartPosSolo = 2;
					continue;
				}
				Bro->B->StatusE("", "Player" + std::to_string(i), RR->PlayerMatrix[i]->Name);
				iCoundPlayers++;
				//CardsCound = 0;
			}

			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type == 4009
					|| RR->ActionMatrix[i]->Type == 4010
					|| RR->ActionMatrix[i]->Type == 4011
					|| RR->ActionMatrix[i]->Type == 4012)
				{
					dublette = false;
					for (unsigned int j = 0; j < Cards.size(); j++)
						if (std::to_string(RR->ActionMatrix[i]->ActionPlayer) + std::to_string(RR->ActionMatrix[i]->Card) == Cards[j])
							dublette = true;

					if (!dublette)Cards.push_back(std::to_string(RR->ActionMatrix[i]->ActionPlayer) + std::to_string(RR->ActionMatrix[i]->Card));
				}
			}

			// Card Count CHeck
			if (   Cards.size() <= 20 && iCoundPlayers == 2
				|| Cards.size() <= 10 && iCoundPlayers == 1)Bro->B->StatusE("OK", "TotalCardsPlayed", std::to_string(Cards.size()));
			else
			{
				Bro->B->StatusE("ERROR", "TotalCardsPlayed", std::to_string(Cards.size()));
				if (OneErrorLeave)return -4;
				else error = -4;
			}


			/*
			///Count Powerells
			//Add Start Wells
			for (unsigned int i = 0; i < iCoundPlayers * 2; i++)PowerWells.push_back(i);

			

			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type != 4030) continue;
				dublette = false;
				for (unsigned int j = 0; j < PowerWells.size(); j++)
					if (atoi(RR->ActionMatrix[i]->AdditionalInfo.c_str()) == PowerWells[j])
						dublette = true;

				if (!dublette)PowerWells.push_back(atoi(RR->ActionMatrix[i]->AdditionalInfo.c_str()));
			}
			
			if (iCoundPlayers == 2) //DUO
			{
				if (PowerWells.size() ==27)Bro->B->StatusE("OK", "PowerWellsDuo_27", std::to_string(PowerWells.size()));
				else
				{
					Bro->B->StatusE("ERROR", "PowerWellsDuo_27", std::to_string(PowerWells.size()));
					if (OneErrorLeave)return -5;
					else error = -5;
				}
			}
			else // SOLO
			{
				switch (iStartPosSolo)
				{
				case 1:
					if (PowerWells.size() == 22)Bro->B->StatusE("OK", "PowerSoloPOS1_22", std::to_string(PowerWells.size()));
					else
					{
						Bro->B->StatusE("ERROR", "PowerSoloPOS1_22", std::to_string(PowerWells.size()));
						if (OneErrorLeave)return -6;
						else error = -6;
					}
					break;
				case 2:
					if (PowerWells.size() == 23)Bro->B->StatusE("OK", "PowerSoloPOS2_23", std::to_string(PowerWells.size()));
					else
					{
						Bro->B->StatusE("ERROR", "PowerSoloPOS2_23", std::to_string(PowerWells.size()));
						if (OneErrorLeave)return -7;
						else error = -7;
					}
					break;
				}				
			}
			*/

			// Transform Check
			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type != 4007) continue;
				if (atoi(RR->ActionMatrix[i]->AdditionalInfo.c_str()) < 500)continue;

				dublette = false;
				for (unsigned int j = 0; j < Transforms.size(); j++)
					if (atoi(RR->ActionMatrix[i]->AdditionalInfo.c_str()) == Transforms[j])
						dublette = true;

				if (!dublette)Transforms.push_back(atoi(RR->ActionMatrix[i]->AdditionalInfo.c_str()));
			}

			if (Transforms.size() >= 2)Bro->B->StatusE("OK", "TransformCheck", std::to_string(Transforms.size()));
			else
			{
				Bro->B->StatusE("ERROR", "TransformCheck", std::to_string(Transforms.size()));
				if (OneErrorLeave)return -9;
				else error = -9;
			}


			
		}
		else Bro->B->StatusE("ERROR", "Cant_open_file", sFile);

		if (error != 0) Bro->B->StatusE("ERROR", "NotAllChecksWhereOK", "!!!FAILED!!!");
		else Bro->B->StatusE("OK", "AllChecksAreOK", "!!!VALID!!!");


	}
	else printf("Drag and Drop you PMV on the Applikation\n");


	

	system("Pause");
    return 0;
}

