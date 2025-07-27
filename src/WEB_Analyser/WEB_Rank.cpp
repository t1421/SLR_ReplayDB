#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Rank.h"
#include "..\..\incl\DataTypes.h"
#include "..\..\incl\Utility.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WTable.h>
#include <Wt/WText.h>
#include <Wt/WAnchor.h>
#include <Wt/Utils.h>
#include <Wt/WSlider.h>


broker *(WEB_Rank::Bro) = NULL;

WEB_Rank::WEB_Rank(WEB_Analyser *WR_, unsigned int _iRankList):WR(WR_)
{
	MISS;
	iRankList = _iRankList;
	cMain = new Wt::WContainerWidget();
	wtTabelle = new Wt::WTable();
	wtTabelleHead = new Wt::WTable();
	waRankLink = new Wt::WAnchor();

	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waRankLink)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelleHead)));
	cMain->addWidget(std::unique_ptr<Wt::WWidget>(std::move(wtTabelle)));
	
	MISE;
}



void WEB_Rank::WRefresh()
{
	MISS;
	
	Wt::WAnchor *waLink;
	unsigned int iCol = 0;
	std::vector<ROW> vListe;
	unsigned int iDeckCheck = 0;
	Wt::WSlider* slider = new Wt::WSlider();

	MISD(iRankList);
	MISD(Bro->A_getRankMode(iRankList));


	wtTabelle->clear();
	wtTabelleHead->clear();
	if (Bro->A_getRankMode(iRankList) > 10 && !WR->WA_Admin)
	{		
		MISEA("Event Over");
		return;
	}
	if ((Bro->A_getRankMode(iRankList) == 5 || Bro->A_getRankMode(iRankList) == 6) && !WR->WA_Admin)
	{
		
		switch (iRankList)
		{
		case 11:
			
			wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Public Leaderboard </h3>"))));
			vListe = Bro->A_getRankeROW(iRankList);
			for (auto R : vListe)if (R.Stamps[2] <= 60) iDeckCheck++;
			
			slider->resize(390, 5);
			slider->disable();
			slider->setRange(0, vListe.size());
			slider->setValue(iDeckCheck);

			wtTabelle->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(slider)));
			wtTabelle->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" Replays: " + std::to_string(vListe.size())))));
			wtTabelle->elementAt(3, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" With Deck Lvl <= 60: " + std::to_string(iDeckCheck)))));
			return;

		//case 13:
		//	return;
		case 15:
			vListe = Bro->A_getRankeROW(iRankList);
			slider->resize(390, 5);
			slider->disable();
			slider->setRange(0, 10 - vListe.size() % 10 + vListe.size());
			slider->setValue(vListe.size());
			wtTabelleHead->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(slider)));
			wtTabelleHead->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" Replays: " + std::to_string(vListe.size())))));
			wtTabelleHead->elementAt(3, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" More Random Draws Boosters with " + std::to_string(10 - vListe.size() % 10 + vListe.size()) + " Players"))));
			break;

		case 17:
			vListe = Bro->A_getRankeROW(iRankList);
			for (auto L : vListe) iDeckCheck += L.Stamps[1];			
			wtTabelleHead->elementAt(1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" Player: " + std::to_string(vListe.size())))));
			wtTabelleHead->elementAt(2, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(" Tickets Total: " + std::to_string(iDeckCheck)))));
			//return;
			break;
		}
	}

	if (!WR->isOK() && Bro->A_getRankMode(iRankList) == 5 && !WR->WA_Admin)
	{		
		wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h3> No Replay </h3>"))));
		MISEA("no Replay");
		return;
	}

	if (WR->WA_Admin)
	{
		waRankLink->setText("#");
		waRankLink->setLink(Wt::WLink(Bro->L_getRANK_PATH() + Wt::Utils::urlEncode(std::to_string(iRankList) + ".csv")));
	}

	
	
	if (Bro->A_getRankMode(iRankList) == 5 && !WR->WA_Admin)
	{
		vListe = Bro->A_getRankeROW(iRankList, WR->GetTeamID());
		if(vListe.size() == 0)vListe = Bro->A_getRankeROW(iRankList, WR->GetPlayerName(WR->getPMVPlayerID()));
	}
	else vListe = Bro->A_getRankeROW(iRankList);
	
	wtTabelle->elementAt(0, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Rank </h4>"))));
	wtTabelle->elementAt(0, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Player </h4>"))));	
		
	wtTabelle->columnAt(0)->setWidth(75);
	wtTabelle->columnAt(1)->setWidth(200);
	
	/// Fill HEADERS
	switch (iRankList)	
	{ 
	case 0:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Points </h4>"))));			
		break;
	case 2:		
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Score </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		break;
	case 3:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Buildings </h4>"))));
		break;
	case 5:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Units </h4>"))));
		break;
	case 7:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Score </h4>"))));
		break;
	case 8:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Power </h4>"))));
		break;
	case 9:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Adv </h4>"))));
		wtTabelle->elementAt(0, 2)->widget(0)->setToolTip("Finish Unexpected Visitors on advanced difficulty or higher");
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Exp </h4>"))));
		wtTabelle->elementAt(0, 3)->widget(0)->setToolTip("Finish Unexpected Visitors on expert difficulty");
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> UV-Deck </h4>"))));
		wtTabelle->elementAt(0, 4)->widget(0)->setToolTip("Finish Unexpected Visitors with only shadow or amii cards");
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Adv </h4>"))));
		wtTabelle->elementAt(0, 5)->widget(0)->setToolTip("Finish Into the Jungle on advanced difficulty or higher");
		wtTabelle->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Exp </h4>"))));
		wtTabelle->elementAt(0, 6)->widget(0)->setToolTip("Finish Into the Jungle on expert difficulty");
		wtTabelle->elementAt(0, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4 style='color:RoyalBlue;'> IJ-Deck </h4>"))));
		wtTabelle->elementAt(0, 7)->widget(0)->setToolTip("Finish Into the Jungle with only nature or amii cards");
		break;
	case 10:
		iCol = 2;
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Points </h4>"))));
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Split1 </h4>"))));
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Split2 </h4>"))));
		wtTabelle->elementAt(0, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Split3 </h4>"))));
		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1690,50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 556, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
		iCol++;
		iCol++;

		//WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 862, 50);
		//wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
		//iCol++;
		//iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1232, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol),815, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(1);
		iCol++;
		//iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1578, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(2);
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 554, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(3);
		iCol++;
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1440, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(3);
		iCol++;
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1164, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(4);
		iCol++;
		iCol++;
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1288, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(4);
		iCol++;
		iCol++;
		iCol++;
		iCol++;

		WR->AddCardIMG(wtTabelle->elementAt(0, iCol), 1577, 50);
		wtTabelle->elementAt(0, iCol)->setColumnSpan(4);
		iCol++;
		iCol++;
		iCol++;
		iCol++;
		break;

	case 11:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Power </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Deck Level </h4>"))));
		break;
	case 12:
		break;
	case 13:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Spells </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Units </h4>"))));
		break;
	case 15:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Dif </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Cry </h4>"))));
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Cry Time </h4>"))));
		break;
	case 17:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));
		wtTabelle->elementAt(0, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Dif </h4>"))));
		wtTabelle->elementAt(0, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Red </h4>"))));
		wtTabelle->elementAt(0, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Black </h4>"))));
		wtTabelle->elementAt(0, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Yellow </h4>"))));
		break;
	default:
		wtTabelle->elementAt(0, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<h4> Time </h4>"))));		
	}
	wtTabelle->columnAt(2)->setWidth(100);
	wtTabelle->columnAt(3)->setWidth(100);



	/// FILL ROWS 

	for (unsigned int i = 0; i <vListe.size(); i++)
	{	
		wtTabelle->elementAt(i + 1, 0)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(i + 1)))));
		//if(iRankList<100 || iRankList==101)wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID + "#" + std::to_string(vListe[i].ReplayID)))));  //Bro->GetTeamName(vListe[i].ID)
		switch (iRankList)
		{
		//Replay ID
		case 8:		
		case 10:
		case 11:
			wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(Bro->GetTeamName(vListe[i].ID) + "#" + std::to_string(vListe[i].ReplayID)))));
			break;
		//Name
		default:
			wtTabelle->elementAt(i + 1, 1)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(vListe[i].ID))));
		
		}
		
		switch (iRankList)
		{
		case 0:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			break;
		case 2:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			break;
		case 1:		
		case 4:
		case 6:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 3:
		case 5:			
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 7:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(
				std::to_string(vListe[i].Stamps[0])
				+ "/" +
				std::to_string(vListe[i].Stamps[1])
			))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;
		case 8:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			break;
		case 9:
			if (vListe[i].Stamps[0] == 1)wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[1] == 1)wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[2] == 1)wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[3] == 1)wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[4] == 1)wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			if (vListe[i].Stamps[5] == 1)wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:ForestGreen ;'>Done</span>"))));
			else wtTabelle->elementAt(i + 1, 7)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("<span style='color:Tomato;'>ToDo</span>"))));
			
			break;
		case 10:
			iCol = 2;
			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));

			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[3] - vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, iCol++)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0] - vListe[i].Stamps[3])))));
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[4] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[4] >= 2);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[5] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[5] >= 2);

			//WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[6] >= 1);
			//WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[6] >= 2);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[7] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[7] >= 2);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[8] >= 1);
			//WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[8] >= 2);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[12] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[13] >= 1);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[9]  >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[10] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[11] >= 1);			

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[14] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[14] >= 2);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[14] >= 3);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[15] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[15] >= 2);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[15] >= 3);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[15] >= 4);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[16] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[16] >= 2);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[16] >= 3);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[16] >= 4);

			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[17] >= 1);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[17] >= 2);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[17] >= 3);
			WR->AddIMG(wtTabelle->elementAt(i + 1, iCol++), vListe[i].Stamps[17] >= 4);
			
			break;

		case 11:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			break;

		case 12:
			break;
		case 13:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[1])))));
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			if (vListe[i].ID == WR->GetTeamID())wtTabelle->rowAt(i + 1)->setStyleClass("grau-box");			
			break;
		case 15:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			switch (vListe[i].Stamps[1])
			{
			case 1:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Std"))));
				break;
			case 2:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Adv"))));
				break;
			case 3:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Exp"))));
				break;
			}
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(std::to_string(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[15])))));
			//if (vListe[i].ID == WR->GetPlayerName(WR->getPMVPlayerID()))wtTabelle->elementAt(i + 1, 2)->setStyleClass("grau-box");
			if (vListe[i].ID == WR->GetPlayerName(WR->getPMVPlayerID()))wtTabelle->rowAt(i + 1)->setStyleClass("grau-box");
			break;
		case 17:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
			switch (vListe[i].Stamps[1])
			{
			case 1:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Std"))));
				break;
			case 2:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Adv"))));
				break;
			case 3:
				wtTabelle->elementAt(i + 1, 3)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText("Exp"))));
				break;
			}		
			wtTabelle->elementAt(i + 1, 4)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[2])))));
			wtTabelle->elementAt(i + 1, 5)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[3])))));
			wtTabelle->elementAt(i + 1, 6)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[4])))));
			break;
		default:
			wtTabelle->elementAt(i + 1, 2)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(new Wt::WText(sTimeFull(vListe[i].Stamps[0])))));
		}			

		if (WR->WA_Admin)
		{
			MISD(vListe[i].ID);
			waLink = new Wt::WAnchor();
			waLink->setText("#");
			waLink->setLink(Wt::WLink(Bro->L_getPMV_WEB_PATH() + Wt::Utils::urlEncode(std::to_string(iRankList) + "_" + vListe[i].ID + ".pmv")));
			wtTabelle->elementAt(i + 1, 9)->addWidget(std::unique_ptr<Wt::WWidget>(std::move(waLink)));
		}
	}	
	
	/// POST CLEANUP
	switch (iRankList)
	{
	case 9:
		wtTabelle->removeColumn(0);
		wtTabelle->columnAt(2)->setWidth(100);
		wtTabelle->columnAt(3)->setWidth(100);
		wtTabelle->columnAt(4)->setWidth(100);
		wtTabelle->columnAt(5)->setWidth(100);
		wtTabelle->columnAt(6)->setWidth(100);
		wtTabelle->columnAt(7)->setWidth(100);
		break;
	case 10:
		iCol = 4;
		wtTabelle->columnAt(iCol++)->setWidth(75);
		wtTabelle->columnAt(iCol++)->setWidth(75);
		wtTabelle->columnAt(iCol++)->setWidth(75);

		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		//wtTabelle->columnAt(iCol++)->setWidth(30);
		//wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);
		wtTabelle->columnAt(iCol++)->setWidth(30);

		wtTabelle->columnAt(iCol++)->setWidth(30);
		//wtTabelle->columnAt(iCol++)->setWidth(30);

		wtTabelle->columnAt(iCol++)->setWidth(20);
		wtTabelle->columnAt(iCol++)->setWidth(20);
		wtTabelle->columnAt(iCol++)->setWidth(20);

		wtTabelle->columnAt(iCol++)->setWidth(20);
		wtTabelle->columnAt(iCol++)->setWidth(20);
		wtTabelle->columnAt(iCol++)->setWidth(20);

		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);

		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);

		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		wtTabelle->columnAt(iCol++)->setWidth(15);
		break;
	case 12:
		wtTabelle->removeColumn(0);
		break;
	case 13:
		wtTabelle->removeColumn(0); //rank
		wtTabelle->removeColumn(0); //player
		wtTabelle->columnAt(0)->setWidth(75);
		wtTabelle->columnAt(1)->setWidth(75);
		wtTabelle->columnAt(2)->setWidth(75);
		break;
	case 15:
		wtTabelle->removeColumn(0); //rank		
		wtTabelle->columnAt(0)->setWidth(150); //Player
		wtTabelle->columnAt(1)->setWidth(75);  //Time
		wtTabelle->columnAt(2)->setWidth(50);  //Dif
		wtTabelle->columnAt(3)->setWidth(50);  //Crystal
		wtTabelle->columnAt(4)->setWidth(75);  //Crystal Time
		break;
	case 17:
		wtTabelle->removeColumn(0); //rank		
		wtTabelle->columnAt(0)->setWidth(150); //Player
		wtTabelle->columnAt(1)->setWidth(75);  //Time
		wtTabelle->columnAt(2)->setWidth(50);  //Dif
		wtTabelle->columnAt(3)->setWidth(75);  //Time
		wtTabelle->columnAt(4)->setWidth(75);  //Time
		wtTabelle->columnAt(5)->setWidth(75);  //Time
		break;
	default:
		break;
	}
	MISE;
}
