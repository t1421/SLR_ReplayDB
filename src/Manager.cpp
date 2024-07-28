#define DF_Debug

#include "..\incl\Broker.h" 
#include "..\incl\Manager.h"
#include "..\incl\Replay.h" 
#include "..\incl\Utility.h"

#ifndef noSQL
#include "..\incl\PMV_to_SQL.h" 
#include "..\incl\SQL_MIS_New.h" 
#endif

#ifdef BrokerNormal
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
#endif

#include <fstream>

broker *(Manager::Bro) = NULL;

Manager::Manager() :Thread_MIS("Manager")
{
	MISS;
#ifndef noSQL
	NN = new SQL_MIS_New("Manager");	
#endif

	MISE;
}
#ifdef BrokerNormal
void Manager::Thread_Function()
{
	MISS;

	std::stringstream ssCMD;

	while (bRunning)
	{
		
		path p = Bro->L_getPMV_AUTO_PATH();
		recursive_directory_iterator it = recursive_directory_iterator(p);
	
		while (it != recursive_directory_iterator{})
		{
		
			if (!(it->path().extension() == ".pmv" || it->path().extension() == ".PMV"))
			{
				it++;
				continue;
			}
			
			RR = new Replay();
			if (RR->LoadPMV(it->path().string()))
			{
				
				PP = new PMV_to_SQL();
				PP->UseThisSQL(NN);
				
				if (PP->UseThisPMV(RR))
				{
					path dir(it->path());
					if (dir.parent_path().string() != "REPLAY_AUTO")PP->sEvent = dir.parent_path().filename().string();
					if(PP->Upload())MISD("DONE");										
				} else MISD("Error using Replay Object ");
					
				
				ssCMD.str("");
				ssCMD << "move \"" << it->path().string() << "\" \"" << Bro->L_getPMV_ARCH_PATH();
				//MISD(ssCMD.str());
				if (PP->sEvent != "" && PP->sEvent != "REPLAY_AUTO") ssCMD << "\\" << PP->sEvent;
				//MISD(ssCMD.str());
				ssCMD << "\\" << it->path().filename().string() << "\"";
				//MISD(ssCMD.str());
				system(ssCMD.str().c_str());
				
			}
			
			it++;
		}
		
		
		Sleep(1000);
		
	}	
	MISE;
}
#endif


#if defined BrokerPVP
void Manager::Thread_Function()
{
	MISS;

	std::stringstream ssCMD;
	unsigned int iSaveNr;

	while (bRunning)
	{
		
		RR = new Replay();
		iLastAction = 0;		
		minActionPlayer = 0;
		maxActionPlayer = 0;
		if (RR->LoadPMV(Bro->L_getLivePvPPMV()))
		{			
			ResteLiveFiles();
			while(!RR->ConnectActionToPlayer())
			{
				MISD("Wait for Actions to Connect");
				Sleep(1000);
				RR->readDelta();
			}
			
			minActionPlayer = RR->PlayerMatrix[0]->ActionPlayer;
			maxActionPlayer = RR->PlayerMatrix[RR->PlayerMatrix.size() - 1]->ActionPlayer;

			iSaveNr = 0 ;
			for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
			{
				if (i > 0)if (RR->PlayerMatrix[i]->GroupID != RR->PlayerMatrix[i - 1]->GroupID)iSaveNr = 3;
				RR->PlayerMatrix[i]->iSaveID = iSaveNr;
				iSaveNr++;
			}

			for each (Player *P in RR->PlayerMatrix)SetPlayer(P->iSaveID, P->Name);
						
			while (RR->readDelta() != -1)
			{
				switch (processActions())
				{
				case -1: //Re Calc
					goto exit_loop;
					break;
				case 0: //Nichts
					break;
				case 1: //Karrte gespielt
					UpdateFiles();
					break;
				
				}

				//MISD(RR->CountActions());
				Sleep(1000);
			}

		exit_loop:;
			RR->close();
		}
		Sleep(1000);
	}
	MISE;
}

void Manager::ResteLiveFiles()
{
	MISS;
	for (unsigned int i = 0; i < 6; i++)
	{
		SetPlayer(i, "");
		SetCardBack(i, 0);
		for (unsigned int j = 0; j < 20; j++)
		{
			SetCard(i * 100 + j, 0, 0, 0, 0);
		}
	}

	MISE;
}

void Manager::UpdateFiles()
{
	MISS;
	for (unsigned int i = 0; i < RR->PlayerMatrix.size(); i++)
	{
		SetCardBack(RR->PlayerMatrix[i]->iSaveID, RR->PlayerMatrix[i]->Deck.size());
		for (unsigned int j = 0; j < RR->PlayerMatrix[i]->Deck.size(); j++)
			SetCard(
				RR->PlayerMatrix[i]->iSaveID * 100 + j,
				RR->PlayerMatrix[i]->Deck[j]->CardID,
				RR->PlayerMatrix[i]->Deck[j]->Upgrade,
				RR->PlayerMatrix[i]->Deck[j]->Charges,
				RR->PlayerMatrix[i]->Deck[j]->count);
	}
	MISE;
}

int Manager::processActions()
{
	MISS;
	int iReturn = 0;

	for (unsigned int i = iLastAction; i < RR->ActionMatrix.size(); i++)
	{

		if (RR->ActionMatrix[i]->ActionPlayer != 0
			&& (RR->ActionMatrix[i]->ActionPlayer < minActionPlayer ||
				RR->ActionMatrix[i]->ActionPlayer > maxActionPlayer))
		{
			MISEA("Re Calc Players");
			return -1;
		}

		if (RR->ActionMatrix[i]->Type == 4009 ||
			RR->ActionMatrix[i]->Type == 4010 ||
			RR->ActionMatrix[i]->Type == 4011 ||
			RR->ActionMatrix[i]->Type == 4012 ||
			RR->ActionMatrix[i]->Type == 4044)
		{
			AddCardToPlayer(RR->ActionMatrix[i]);
			iReturn = 1;
		}
		
	}
	iLastAction = RR->ActionMatrix.size();

	MISE;
	return iReturn;
}

void Manager::AddCardToPlayer(Action *Import)
{
	MISS;
	bool bFound = false;
	Card* Card_TEMP = new Card;
	for each (Player *P in RR->PlayerMatrix)
	{
		if (P->ActionPlayer == Import->ActionPlayer)
		{
			for each(Card *C in P->Deck)
			{
				if (C->CardID == Import->Card)
				{
					bFound = true;
					C->count++;
				}
			}

			if (!bFound)
			{
				Card_TEMP->CardFull = Import->CardFull;
				Card_TEMP->CardID = Import->Card;
				Card_TEMP->Charges = Import->Charges;
				Card_TEMP->Upgrade = Import->Upgrade;
				Card_TEMP->DeckCardID = P->Deck.size();
				Card_TEMP->count = 1;
				P->Deck.push_back(Card_TEMP);
			}
		}
	}	
	MISE;
}

void Manager::SetCard(unsigned int POS, unsigned short CardID, unsigned char Upgrade, unsigned char Charges, unsigned int Count)
{
	MISS;
	//std::ifstream  src(Bro->J_GetImage(CardID, Upgrade, Charges, Big, false), std::ios::binary);
	std::ifstream  src(Bro->J_GetImageSmall(CardID), std::ios::binary);
	std::ofstream  dst(Bro->L_getLivePvP_OBS_Export() + std::to_string(POS) + ".webp", std::ios::binary);
	dst << src.rdbuf();
	src.close();
	dst.close();

	dst.open(Bro->L_getLivePvP_OBS_Export() + std::to_string(POS) + ".txt", std::ios::binary);
	if(Count>0)dst << Count;
	else dst << " ";
	dst.close();	
	MISE;
}

void Manager::SetCardBack(unsigned int POS, unsigned int iCount)
{
	MISS;
	std::ifstream src(Bro->L_getLivePvP_Pics() + std::to_string(iCount) + ".webp", std::ios::binary);
	std::ofstream dst(Bro->L_getLivePvP_OBS_Export() + "B" + std::to_string(POS) + ".webp", std::ios::binary);
	dst << src.rdbuf();
	src.close();
	dst.close();

	MISE;
}

void Manager::SetPlayer(unsigned int POS, std::string sName)
{
	MISS;	
	std::ofstream  dst(Bro->L_getLivePvP_OBS_Export() + "P" + std::to_string(POS) + ".txt", std::ios::binary);	
	dst << sName;
	dst.close();
	MISE;
}


#endif

