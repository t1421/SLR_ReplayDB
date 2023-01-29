#include "incl\Broker.h" 
#include "incl\DEBUG.h" 
#include "incl\Replay.h" 



int main(int argc, char **argv)
{
	unsigned int iCoundPlayers = 0;
	
	unsigned int CardsCound = 0;
	unsigned int CardsCoundTotal = 0;
	Card Cards[4][20];
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
				return -1;
			}

			// Map CHeck
			if (RR->MapName == "11202_PvE_02p_MadGod.map")Bro->B->StatusE("OK", "Map", RR->MapName);
			else
			{
				Bro->B->StatusE("ERROR", "Map", RR->MapName);
				return -2;
			}

			// Div Check
			if (RR->DifficultyID == 1)Bro->B->StatusE("OK", "Difficulty", std::to_string(RR->DifficultyID));
			else
			{
				Bro->B->StatusE("ERROR", "Difficulty", std::to_string(RR->DifficultyID));
				return -3;
			}

			for (unsigned i = 0; i < RR->PlayerMatrix.size(); i++)
			{
				if (RR->PlayerMatrix[i]->Name == "pl_Enemy1") continue;
				Bro->B->StatusE("", "Player" + std::to_string(i), RR->PlayerMatrix[i]->Name);
				iCoundPlayers++;
				CardsCound = 0;

				for (unsigned int j = 0; j < RR->ActionMatrix.size(); j++)
				{
					if (RR->ActionMatrix[j]->Type == 4009
						|| RR->ActionMatrix[j]->Type == 4010
						|| RR->ActionMatrix[j]->Type == 4011
						|| RR->ActionMatrix[j]->Type == 4012)
					{
						for (unsigned int k = 0; k < 20; k++)
						{
							if (Cards[i][k].CardID == RR->ActionMatrix[j]->Card) break; //Kare schon mal gespielt
							if (Cards[i][k].CardID != 0) continue; // irgend eine andere Karte
							
							Cards[i][k].CardID = RR->ActionMatrix[j]->Card;
							CardsCound++;
							CardsCoundTotal++;
							
							break;
						}
					}
				}
				Bro->B->StatusE("", "Cards", std::to_string(CardsCound));				
			}

			// Card Count CHeck
			if (CardsCoundTotal <= 20)Bro->B->StatusE("OK", "TotalCardsPlayed", std::to_string(CardsCoundTotal));
			else
			{
				Bro->B->StatusE("ERROR", "TotalCardsPlayed", std::to_string(CardsCoundTotal));
				return -4;
			}

			///Count Powerells
			//Check Starting Pos







			
		}
		else Bro->B->StatusE("ERROR", "Cant_open_file", sFile);
	}
	else printf("Drag and Drop you PMV on the Applikation\n");

	system("Pause");
    return 0;
}

