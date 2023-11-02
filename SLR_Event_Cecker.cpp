#include "incl\Broker.h"
#include "incl\DEBUG.h" 
#include "incl\CardBaseSMJ.h" 
#include "incl\Replay.h" 
#include "incl\Utility.h" 

#define OneErrorLeave false

int main(int argc, char **argv)
{	
	int error = 0;
	bool win = false;
	unsigned long TierTwoTime = 0;
	unsigned long WinTime = 0;
	std::vector<std::pair<std::string, std::string>> Orbs;

	if (argc > 1)
	{
		std::string sFile = std::string(argv[1]);
		printf("File %s\n", sFile.c_str());

		broker* Bro = new broker;

		DEBUG* B = new DEBUG("SLR_Event_Cecker", true, true, false);
		B->teachB();
		Bro->B->Fill_DBArray("ERROR", "*", "*", "true");
		Bro->B->Fill_DBArray("OK", "*", "*", "true");

		CardBaseSMJ* J = new CardBaseSMJ();
		J->teachJ();
		J->Init();

		Replay * RR = new Replay();

		if (RR->LoadPMV(sFile))
		{
			std::string sFile = std::string(argv[1]);			
			Bro->B->StatusE("OK", "OpenFile", "");

			// Game Version CHeck
			if (RR->GameVersion = 400044)Bro->B->StatusE("OK", "GameVersion", std::to_string(RR->GameVersion));
			else
			{
				Bro->B->StatusE("ERROR", "GameVersion", std::to_string(RR->GameVersion));
				if (OneErrorLeave)return -1;
				else error = -1;
			}

			// Map CHeck
			if (RR->MapName == "randommap/GeneratedMap.map")Bro->B->StatusE("OK", "Map", RR->MapName);
			else
			{
				Bro->B->StatusE("ERROR", "Map", RR->MapName);
				if (OneErrorLeave)return -2;
				else error = -2;
			}

			// Map CHeck2
			if (RR->MapID == 101)Bro->B->StatusE("OK", "MapID", std::to_string(RR->MapID));
			else
			{
				Bro->B->StatusE("ERROR", "MapID", std::to_string(RR->MapID));
				if (OneErrorLeave)return -2;
				else error = -2;
			}

			// SEED CHeck
			if (RR->Seed == 2216295399)Bro->B->StatusE("OK", "Seed", std::to_string(RR->Seed));
			else
			{
				Bro->B->StatusE("ERROR", "Seed", std::to_string(RR->Seed));
				if (OneErrorLeave)return -3;
				else error = -3;
			}

			// Div Check
			if (RR->DifficultyID == 12)Bro->B->StatusE("OK", "Difficulty", std::to_string(RR->DifficultyID));
			else
			{
				Bro->B->StatusE("ERROR", "Difficulty", std::to_string(RR->DifficultyID));
				if (OneErrorLeave)return -4;
				else error = -4;
			}

			//Orb Checkings
			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type == 4031)
				{
					Orbs.push_back(std::make_pair(
						entry(RR->ActionMatrix[i]->AdditionalInfo, 0),
						entry(RR->ActionMatrix[i]->AdditionalInfo, 1)));

					if (Orbs.size() == 2
						&& TierTwoTime == 0)
						TierTwoTime = RR->ActionMatrix[i]->Time + 30 * 10;
					

					if (Orbs.size() == 4)WinTime = RR->ActionMatrix[i]->Time + 30 * 10;

				}
			}

			//Setzen von Orb1 ID
			for (unsigned int i = 0; i < Orbs.size(); i++) if (Orbs[i].second == Orbs[i].first) Orbs[i].second = "5997";

			for (unsigned int i = 0; i < Orbs.size(); i++)
				Bro->B->StatusE("", "Orbs", Orbs[i].first + "#" + Orbs[i].second);

			// Orb Count
			if (Orbs.size() == 4)Bro->B->StatusE("OK", "OrbsCount", std::to_string(Orbs.size()));
			else
			{
				Bro->B->StatusE("ERROR", "OrbsCount", std::to_string(Orbs.size()));
				if (OneErrorLeave)return -5;
				else error = -5;
			}

			//Orb Colors
			if ((Orbs[0].first == "1" || Orbs[0].first == "3")
				&& (Orbs[1].first == "1" || Orbs[1].first == "3"))Bro->B->StatusE("OK", "OrbColors", Orbs[0].first + "&" + Orbs[1].first);
			else
			{
				Bro->B->StatusE("ERROR", "OrbColors", Orbs[0].first + "&" + Orbs[1].first);
				if (OneErrorLeave)return -6;
				else error = -6;
			}


			//Unit Checks
			Bro->B->StatusE("", "T2FinishTime", sTime(TierTwoTime));

			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
			{
				if (RR->ActionMatrix[i]->Type == 4009)
				{
					if (RR->ActionMatrix[i]->Time <= TierTwoTime)
					{
						Bro->B->StatusE("OK", "LSCard-Skip", sTime(RR->ActionMatrix[i]->Time) +  J->GetSMJCard(RR->ActionMatrix[i]->Card)->cardNameSimple);
						continue;
					}
					if (J->SwitchColor(J->GetSMJCard(RR->ActionMatrix[i]->Card)->color) == "Lost Souls")Bro->B->StatusE("OK", "LSCard", sTime(RR->ActionMatrix[i]->Time) + J->GetSMJCard(RR->ActionMatrix[i]->Card)->cardNameSimple);
					else
					{
						Bro->B->StatusE("ERROR", "LSCard", sTime(RR->ActionMatrix[i]->Time) + J->GetSMJCard(RR->ActionMatrix[i]->Card)->cardNameSimple);
						if (OneErrorLeave)return -7;
						else error = -7;
					}

				}
			}

			//check if it is a win
			for (unsigned int i = 0; i < RR->ActionMatrix.size(); i++)
				if (RR->ActionMatrix[i]->Type == 4045)
					//printf("%s\n", RR->ActionMatrix[i]->AdditionalInfo.c_str());
					if (RR->ActionMatrix[i]->AdditionalInfo == "RvERandomMapsGoal1;1;")win = true;
			if (win)Bro->B->StatusE("OK", "GameWon", "YES");
			else
			{
				Bro->B->StatusE("ERROR", "GameWon", "NO");
				if (OneErrorLeave)return -8;
				else error = -8;
			}

			Bro->B->StatusE("", "WinTime",sTime(WinTime));

			
		}
		else Bro->B->StatusE("ERROR", "Cant_open_file", sFile);

		if (error != 0) Bro->B->StatusE("ERROR", "NotAllChecksWhereOK", "!!!FAILED!!!");
		else Bro->B->StatusE("OK", "AllChecksAreOK", "!!!VALID!!!");
			
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");

	return 0;    
}

