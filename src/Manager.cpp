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
#include <algorithm>

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
	bool _UpdateCards;
	bool _UpdateActionLog;
	bool _UpdateActionPerSec;

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
				_UpdateCards = false;
				_UpdateActionLog = false;
				_UpdateActionPerSec = false;

				if(processActions(_UpdateCards, _UpdateActionLog, _UpdateActionPerSec)== -1)goto exit_loop;
				
				if(_UpdateCards)UpdateFiles();
				
				if (_UpdateActionLog && Bro->L_getLivePvPActionLog() == 1 && vsActionLog.size() > 0)
				{
					for (auto A: vsActionLog)SetActionLog(A);
					vsActionLog.clear();
				}

				if (/* _UpdateActionPerSec && */ Bro->L_getLivePvPActionPerSec() == 1)UpdateActionPerSec();

				//MISD(RR->CountActions());
				Sleep(Bro->L_getLivePvPRefreshRate());
			}

		exit_loop:;
			RR->close();
		}
		Sleep(Bro->L_getLivePvPRefreshRate());
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
		SetActionsPerSec(i, 0);
		for (unsigned int j = 0; j < 20; j++)
		{
			SetCard(i * 100 + j, 0, 0, 0, 0);
		}
	}

	SetActionLog("");

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

int Manager::processActions(bool& _UpdateCards, bool& _UpdateActionLog, bool& _UpdateActionPerSec)
{
	MISS;
	int iReturn = 0;
	_UpdateCards = false;
	_UpdateActionLog = false;
	_UpdateActionPerSec = false;

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
			_UpdateCards = true;
		}

		if (Bro->L_getLivePvPActionLog() == 1)
			if (FillActionLog(RR->ActionMatrix[i])) _UpdateActionLog = true;;

		if (Bro->L_getLivePvPActionPerSec() == 1) // && RR->ActionMatrix[i]->ActionPlayer != 0)
			if (AddActionPerSec(RR->ActionMatrix[i])) _UpdateActionPerSec = true;;

		
	}
	iLastAction = RR->ActionMatrix.size();

	MISE;
	return iReturn;
}

void Manager::AddCardToPlayer(Action* Import)
{
	MISS;
	bool bFound = false;
	Card* Card_TEMP = new Card;
	for each (Player * P in RR->PlayerMatrix)
	{
		if (P->ActionPlayer == Import->ActionPlayer)
		{
			for each (Card * C in P->Deck)
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

bool Manager::AddActionPerSec(Action* Import)
{
	MISS;

	for each (Player * P in RR->PlayerMatrix)if (P->ActionPlayer == Import->ActionPlayer)
	{
		for (unsigned int i = P->ActionsPerSec.size(); i <= int(Import->Time / 10); i++)P->ActionsPerSec.push_back(0);
		P->ActionsPerSec[int(Import->Time / 10)]++;
	}

	MISE;
	return true;
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

void Manager::SetActionsPerSec(unsigned int POS, unsigned int iCount)
{
	MISS;
	//MISD(std::to_string(POS) + "#" + std::to_string(iCount))
	std::ofstream  dst(Bro->L_getLivePvP_OBS_Export() + "A" + std::to_string(POS) + ".txt", std::ios::binary);
	dst << iCount;
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

bool Manager::FillActionLog(Action *Import)
{
	MISS;

	std::string sAdd;

	switch (Import->Type)
	{
	case 4001:
	case 4003:
	case 4004:
	case 4005:
	case 4008:
	case 4016:
	case 4017:
	case 4018:
	case 4021:
	case 4022:
	case 4023:
	case 4024:
	case 4025:
	case 4026:
	case 4027:
	case 4032:
	case 4045:
		return false;;
	default:
		sAdd += sTimeFull(Import->Time) + ": ";
		sAdd += formatString(RR->SwitchType(Import->Type), 10) + " | ";
	}

	switch (Import->Type)
	{
	case 4009:
	case 4010:
	case 4011:
	case 4012:
	case 4044:
		sAdd += formatString(Bro->J_GetSMJCard(Import->Card)->cardName,15);
	}

	vsActionLog.push_back(sAdd);

	MISE;
	return true;
}

void Manager::SetActionLog(std::string sIN)
{
	MISS;	
	std::ofstream  dst;
	if(sIN=="")dst.open(Bro->L_getLivePvP_OBS_Export() + "ActionLog.txt", std::ios::binary);
	else dst.open(Bro->L_getLivePvP_OBS_Export() + "ActionLog.txt", std::ios::binary | std::ios::app);	
	dst << sIN<<"\n";
	dst.close();
	MISE;
}

void Manager::UpdateActionPerSec()
{
	MISS;

	unsigned int iHelper;
	unsigned int iMax = 0;
	//Add Missings MAX
	for each (Player * P in RR->PlayerMatrix)iMax = std::max(iMax, P->ActionsPerSec.size());

	for each (Player * P in RR->PlayerMatrix)
	{		
		//Add Missings
		for (unsigned int i = P->ActionsPerSec.size(); i < iMax; i++)P->ActionsPerSec.push_back(0);

		iHelper = 0;

		for (int i = P->ActionsPerSec.size() - 1; i >= 0  && i >= (int(P->ActionsPerSec.size()) - Bro->L_getLivePvPActionPerSecNumSec()) ; i--)
			iHelper += P->ActionsPerSec[i];
		
		SetActionsPerSec(P->iSaveID, iHelper);
	}

	MISE;
}

#endif


