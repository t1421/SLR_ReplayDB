#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\LOAD.h" 
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Quest.h"

#include <Wt/WTable.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WAnchor.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WTableView.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSortFilterProxyModel.h>
#include <Wt/WColor.h>
#include <regex>


broker *(WEB_Quest::Bro) = NULL;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


WEB_Quest::WEB_Quest(WEB_Analyser *WR_) : WR(WR_)
{
	MISS;

    Wt::WString LINK;

	cMain = new Wt::WContainerWidget();	

    MISD("#0");

	auto layout = cMain->setLayout(std::make_unique<Wt::WVBoxLayout>());

    filterEdit = new Wt::WLineEdit();
    table = new Wt::WTableView();
    model = new Wt::WStandardItemModel();
    proxy = new Wt::WSortFilterProxyModel();
    status = new Wt::WText("Waiting for replay...");
    

    MISD("#1");
    filterEdit->setPlaceholderText("Name filter...");

    MISD("#2");

    model->insertColumns(model->columnCount(), 1);
    model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "ID");

    model->insertColumns(model->columnCount(), 1);
    model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "Player");
    
    model->insertColumns(model->columnCount(), 1);
    model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "Events");

    for (auto Q : Bro->L->Quests)
    {       
        model->insertColumns(model->columnCount(), 1);
        model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, Q->Name,Wt::ItemDataRole::Display);
        model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, Q->Name, Wt::ItemDataRole::ToolTip);
        model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, Wt::WLink(Q->Link), Wt::ItemDataRole::Link); 
    }

    for (auto QP : Bro->QPlayer)
    {
        model->insertRows(model->rowCount(), 1);
        model->setData(model->rowCount() - 1, 0, QP->PlayerID);
        model->setData(model->rowCount() - 1, 1, QP->PlayerName);
        model->setData(model->rowCount() - 1, 2, QP->Stamps.size());
        for (auto QPQ : QP->Stamps)
        {            
            for(unsigned int i = 0; i < Bro->L->Quests.size();i++)
                if (std::to_string(Bro->L->Quests[i]->ID) == QPQ.first)
                {
                    model->setData(model->rowCount() - 1, i + 3 , QPQ.second);
                    if (WR->WA_Debug)model->setData(model->rowCount() - 1, i + 3, "green", Wt::ItemDataRole::StyleClass);
                    else model->setData(model->rowCount() - 1, i + 3, "greenFull", Wt::ItemDataRole::StyleClass);                    
                    model->setData(model->rowCount() - 1, i + 3, sToolTipp(atoi(QPQ.first.c_str()), QPQ.second), Wt::ItemDataRole::ToolTip);
                    break;
                }            
        }
    }

    MISD("#5");
    proxy->setSourceModel(std::shared_ptr<Wt::WAbstractItemModel>(model));
    proxy->setDynamicSortFilter(true);
    proxy->setFilterKeyColumn(1);
    proxy->setFilterRole(Wt::ItemDataRole::Display);

    MISD("#6");
    table->setModel(std::shared_ptr<Wt::WAbstractItemModel>(proxy));
    table->setSortingEnabled(true);
    table->setColumnResizeEnabled(true);
    table->setAlternatingRowColors(true);
    table->setSelectionMode(Wt::SelectionMode::Single);
    table->setRowHeight(28);
    //table->setColumnHidden(0, true);
    

    MISD("#7");

    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(status)));
    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(filterEdit)));
    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(table)));

    MISE;
}

void WEB_Quest::WRefresh()
{
	MISS;

    unsigned long iTimes[RankRowStamps] = { 0 };
    unsigned long long iValue = 0;
    
    bool refresh = false;
    std::string sReturn;

    Wt::Chart::WCartesianChart* chart = nullptr;;

    status->setText("Checking...");
    //find correct Event
    if (WR->getMapName() == "11105_PvE_01p_EncountersWithTwilight.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        sReturn = WR->Kalk_BOT01(iTimes);
        if (sReturn == "")
        {
            iValue = 0;            
            iValue += 0 * 100000 * 100000; //NONE
            iValue += iTimes[1] * 100000; //Points
            iValue += iTimes[0] * 1; //Time
            refresh = refresh || Add_Player_to_Quest("101", iValue);
        }
    }
    if (WR->getMapName() == "11104_PvE_01p_BehindEnemyLines.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        sReturn = WR->Kalk_BOT02(iTimes);
        if (sReturn == "")
        {
            iValue = 0;            
            iValue += 0 * 100000 * 100000; //NONE
            iValue += iTimes[1] * 100000; //Balanced
            iValue += iTimes[0] * 1; //Time
            refresh = refresh || Add_Player_to_Quest("102", iValue);
        }
    }
    if (WR->getMapName() == "11101_PvE_01p_TugOfWar.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        sReturn = WR->Kalk_BOT03(iTimes);
        if (sReturn == "")
        {
            iValue = 0;            
            iValue += 0 * 100000 * 100000; //NONE
            iValue += iTimes[1] * 100000; //Balanced
            iValue += iTimes[0] * 1; //Time
            refresh = refresh || Add_Player_to_Quest("103", iValue);
        }
    }
    if (WR->getMapName() == "11441_pve_12p_passagetodarkness.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        sReturn = WR->Kalk_BOT04(iTimes);
        if (sReturn == "")
        {
            iValue = 0;
            iValue += 0 * 100000 * 100000; //NONE
            iValue += 0 * 100000; //NONE
            iValue += iTimes[0] * 1; //Time
            refresh = refresh || Add_Player_to_Quest("104", iValue);
        }
    }
    if (WR->getMapName() == "battle_of_tactics_6.map" ||
        WR->getMapName() == "bot6.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        sReturn = WR->Kalk_BOT06(iTimes);
        if (sReturn == "")
        {
            iValue = 0;
            iValue += 0 * 100000 * 100000; //NONE
            iValue += 0 * 100000; //NONE
            iValue += iTimes[0] * 1; //Time
            refresh = refresh || Add_Player_to_Quest("106", iValue);
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    if (WR->getMapName() == "sss1.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
                
        if (WR->Kalk_Event0(iTimes, "sss1.map") == "")
        {
            iValue = 0;
            
            iValue += 0 * 100000 * 100000; //NONE
            iValue += iTimes[0] * 100000; //time
            iValue += iTimes[2] * 1; //power
            refresh = refresh || Add_Player_to_Quest("201", iValue);
        }
    }

    if (WR->getMapName() == "sss2.map")
    {
        std::fill(iTimes, iTimes + RankRowStamps, 0);
        
        if (WR->Kalk_Event2(iTimes) == "")
        {
            iValue = 0;
            
            iValue += iTimes[1] * 100000 * 100000; //Playtime * 10 + Power used * 0,1
            iValue += iTimes[0] * 100000; //time
            iValue += iTimes[2] * 1; //power
            refresh = refresh || Add_Player_to_Quest("202", iValue);
        }
    }
        
     if (WR->getMapName() == "sss3.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);
         
         if (WR->Kalk_Event3(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += iTimes[0] * 100000; //Buildings
             iValue += iTimes[2] * 1; //power
             refresh = refresh || Add_Player_to_Quest("203", iValue);
         }
     }
     if (WR->getMapName() == "sss4.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_Event0(iTimes, "sss4.map") == "")
         {

             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += iTimes[0] * 100000; //time
             iValue += iTimes[2] * 1; //power
             refresh = refresh || Add_Player_to_Quest("204", iValue);
         }
     }
     if (WR->getMapName() == "sss5.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_Event5(iTimes, new Wt::Chart::WCartesianChart()) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += iTimes[0] * 100000; //Units on screen
             iValue += iTimes[2] * 1; //power
             refresh = refresh || Add_Player_to_Quest("205", iValue);
         }
     }
     if (WR->getMapName() == "sss6.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_Event0(iTimes, "sss6.map") == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += iTimes[0] * 100000; //time
             iValue += iTimes[2] * 1; //power
             refresh = refresh || Add_Player_to_Quest("206", iValue);
         }
     }
     if (WR->getMapName() == "sss7.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_Event7(iTimes) == "")
         {
             iValue = 0;
             
             iValue += iTimes[0] * 100000 * 100000; //My Points
             iValue += iTimes[1] * 100000; //OP Points
             iValue += iTimes[2] * 1; //power
             refresh = refresh || Add_Player_to_Quest("207", iValue);
         }
     }
     /////////////////////////////////////////////////////////////////////////////////////////
     if (WR->getMapName() == "ccc - the besieged forge.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_CCC2(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += 0 * 100000; //NONE
             iValue += iTimes[0] * 1; //Time
             refresh = refresh || Add_Player_to_Quest("302", iValue);
         }
     }
     if (WR->getMapName() == "12101_PvE_01p_Mo.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_CCC4(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += iTimes[1] * 100000; //Points
             iValue += iTimes[0] * 1; //Time
             refresh = refresh || Add_Player_to_Quest("304", iValue);
         }
     }
     if (WR->getMapName() == "pve_oracle_ccc.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_CCC5(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += 0 * 100000; //NOINE
             iValue += iTimes[0] * 1; //Time
             refresh = refresh || Add_Player_to_Quest("305", iValue);
         }
     }
     if (WR->getMapName() == "pve_introduction_ccc_6.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_CCC6(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += 0 * 100000; //NOINE
             iValue += iTimes[0] * 1; //Time
             refresh = refresh || Add_Player_to_Quest("306", iValue);
         }
     }
     if (WR->getMapName() == "11200_pve_02p_crusade.map")
     {
         std::fill(iTimes, iTimes + RankRowStamps, 0);

         if (WR->Kalk_CCC10(iTimes) == "")
         {
             iValue = 0;
             
             iValue += 0 * 100000 * 100000; //NONE
             iValue += 0 * 100000; //NOINE
             iValue += iTimes[0] * 1; //Time
             refresh = refresh || Add_Player_to_Quest("310", iValue);
         }
     }

     if (refresh)status->setText("Events Refreshed");
     else status->setText("Cant fint matching event: " + sReturn);
    

	MISE;
}

bool WEB_Quest::Add_Player_to_Quest(std::string sEvent, unsigned long long iValue)
{
    MISS;

    EventData* Quest = nullptr;
    QuestPlayer* QPlayer = nullptr;

    MISD(sEvent);

    MISD("#1");
    if (sEvent == "")
    {
        status->setText("No Event found");
        MISEA("No Quest");
        return false;
    }

    for (EventData* Q : Bro->L->Quests)if (std::to_string(Q->ID) == sEvent)Quest = Q;
    if (Quest == nullptr)
    {
        status->setText("No Event found X");
        MISEA("No Quest XXX");
        return false;
    }

    /*
    if (sReturn != "")
    {
        status->setText("<h3 style='color:Tomato;'>Quest: " + Quest->Name + " Error: " + sReturn + "</h3>");
        MISEA("Error in Check");
        return;
    }
    MISD("#2");*/

    //Add all Players of replay
    for (auto PID : WR->ActivePlayers())
    {
        QPlayer = nullptr;
        for (auto QP : Bro->QPlayer)
            if (QP->PlayerID == std::to_string(PID))
                QPlayer = QP;

        //New player
        if (QPlayer == nullptr)
        {
            Bro->QPlayer.push_back(new QuestPlayer(std::to_string(PID), WR->GetPlayerName(PID)));
            QPlayer = Bro->QPlayer[Bro->QPlayer.size() - 1];
            model->insertRows(model->rowCount(), 1);
            model->setData(model->rowCount() - 1, 0, QPlayer->PlayerID);
            model->setData(model->rowCount() - 1, 1, QPlayer->PlayerName);
            model->setData(model->rowCount() - 1, 2, QPlayer->Stamps.size());
        }

        if (QPlayer->UpdateEvent(sEvent, iValue))
        {
            for (unsigned int i = 0; i < model->rowCount(); i++)
            {
                if (Wt::asString(model->data(i, 0)) == QPlayer->PlayerID)
                {
                    model->setData(i, 2, QPlayer->Stamps.size());
                    for (auto QPQ : QPlayer->Stamps)
                    {
                        for (unsigned int ii = 0; ii < Bro->L->Quests.size(); ii++)
                        {
                            if (std::to_string(Bro->L->Quests[ii]->ID) == QPQ.first)
                            {
                                model->setData(i, ii + 3, QPQ.second);
                                if (WR->WA_Debug)model->setData(i, ii + 3, "green", Wt::ItemDataRole::StyleClass);
                                else model->setData(i, ii + 3, "greenFull", Wt::ItemDataRole::StyleClass);
                                model->setData(i, ii + 3, sToolTipp(atoi(QPQ.first.c_str()), QPQ.second), Wt::ItemDataRole::ToolTip);

                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    Bro->saveQPlayer();
    MISE;
    return true;

}

std::string WEB_Quest::sToolTipp(unsigned int in, unsigned long long Number)
{
    MISS;
    std::string tt;
    switch (in)
    {
    
    case 202:
        return "Points: " + std::to_string(Number / 100000 / 100000)
            + " Time: " + sTime(Number / 100000 % 100000)
            + " Power: " + std::to_string(Number % 100000);
    case 203:
        return "Buildings : " + std::to_string(Number / 100000)
            + " Power: " + std::to_string(Number % 100000);
    case 205:
        return "Units: " + std::to_string(Number / 100000)
            + " Power: " + std::to_string(Number % 100000);
    case 207:
        return "My Points: " + std::to_string(Number / 100000 / 100000)
            + " Op Points: " + std::to_string(Number / 100000 % 100000)
            + " Power: " + std::to_string(Number % 100000);
    case 201:    
    case 204:    
    case 206:
        return "Time: " + sTime(Number / 100000)
            + " Power: " + std::to_string(Number % 100000);
    case 304:
    case 101:
    case 102:
        return "Points: " + std::to_string(Number / 100000)
            + " Time: " + sTime(Number % 100000);
    //case 302:
    //case 305:
    //case 306:
    //case 310:
    //case 103:
    //case 104:
    default:
        return "Time: " + sTime(Number);
    }
    MISE;
    return "";
}