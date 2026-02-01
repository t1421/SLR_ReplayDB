//#define DF_Debug

#include "..\..\incl\Broker.h"

#include "..\..\incl\Utility.h" 
#include "..\..\incl\LOAD.h" 
#include "..\..\incl\CardBaseSMJ.h" 
//#include "..\..\incl\MIS_Rank.h" 
#include "..\..\incl\WEB_Analyser\WEB_Analyser.h"
#include "..\..\incl\WEB_Analyser\WEB_Bounty.h"

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

#define EventNumber 20


broker *(WEB_Bounty::Bro) = NULL;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


WEB_Bounty::WEB_Bounty(WEB_Analyser *WR_) : WR(WR_)
{
	MISS;

    Wt::WString LINK;

	cMain = new Wt::WContainerWidget();	

    MISD("#0");

	auto layout = cMain->setLayout(std::make_unique<Wt::WVBoxLayout>());

    table = new Wt::WTableView();
    model = new Wt::WStandardItemModel();
    proxy = new Wt::WSortFilterProxyModel();
    status = new Wt::WText("Waiting for replay...");
    
    MISD("#2");
    model->insertColumns(model->columnCount(), 1);
    model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "Player");
    
    
    //model->insertColumns(model->columnCount(), 1);
    //model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "Runs");

    MISD("#5");
    proxy->setSourceModel(std::shared_ptr<Wt::WAbstractItemModel>(model));
    proxy->setDynamicSortFilter(true);
    proxy->setFilterKeyColumn(1);    
    proxy->setFilterRole(Wt::ItemDataRole::Display);

    MISD("#6");
    table->setModel(std::shared_ptr<Wt::WAbstractItemModel>(proxy));
    table->setSortingEnabled(true);
    table->sortByColumn(0, Wt::SortOrder::Descending);
    table->setColumnResizeEnabled(true);
    table->setAlternatingRowColors(true);
    table->setSelectionMode(Wt::SelectionMode::Single);
    table->setRowHeight(25);
    table->setHeaderHeight(140);  
    //table->setStyleClass("fusionIMG");
    table->setHeight(800);
    
    MISD("#66");

    TabelRefresh();

    MISD("#7");

    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(status)));
    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(table)));

    MISD("#8");

    

    MISE;
}

void WEB_Bounty::WRefresh()
{
	MISS;

    unsigned long iTimes[RankRowStamps] = { 0 };
    
    std::string sReturn;
    std::string sID;

    Wt::Chart::WCartesianChart* chart = nullptr;;

    status->setText("Checking...");
    
    sReturn = WR->Kalk_Bounty01(iTimes);

    if (sReturn != "")
    {
        status->setText("<h3 style='color:Tomato;'>Error: " + sReturn + "</h3>");
        MISEA("Not OK");
        return;
    }

    sID = WR->GetPlayerName(WR->getPMVPlayerID()) + "_" + Bro->J->GetSMJCard(iTimes[0])->cardSlug + "_" + Bro->J->GetSMJCard(iTimes[1])->cardSlug;
    if (Bro->A_AddPlayer(EventNumber, sID, WR->getReplayHash(), iTimes) == 1)
    {
        WR->SaveReplay(Bro->L->sPMV_WEB_PATH + std::to_string(EventNumber) + "_" + sID + ".pmv");
        TabelRefresh();
    }
    status->setText("<h3>Nice run : -) </h3> ");

	MISE;
}

bool WEB_Bounty::TabelRefresh()
{
    MISS;
    std::vector<std::string> vPlayers;
    std::vector<std::string> vCards;
    bool found;
    unsigned int iRow;
    unsigned int iColumn;


    for (auto R : Bro->A_getRankeROW(EventNumber))
    {
        vPlayers.push_back(entry(R.ID, 0, "_"));
        vCards.push_back(std::to_string(R.Stamps[0]) + ";" + std::to_string(R.Stamps[1]));
    }
    std::sort(vPlayers.begin(), vPlayers.end());
    vPlayers.erase(std::unique(vPlayers.begin(), vPlayers.end()), vPlayers.end());

    std::sort(vCards.begin(), vCards.end());
    vCards.erase(std::unique(vCards.begin(), vCards.end()), vCards.end());
    
    MISD("vPlayers.size() " + std::to_string(vPlayers.size()));
    MISD("model->rowCount() " + std::to_string(model->rowCount()));

    //Add rows AKA Players
    if (vPlayers.size() > model->rowCount()) 
        for (auto P : vPlayers)
        {
            found = false;
            for (unsigned int i = 0; i < model->rowCount() && found == false; i++)
                found = Wt::asString(model->data(i, 0)) == P;

            if (found == false)
            {
                MISD(P);
                model->insertRows(model->rowCount(), 1);
                model->setData(model->rowCount() - 1, 0, P);
                //model->setData(model->rowCount() - 1, 1, 0);
            }
        }

    MISD("vCards.size() " + std::to_string(vCards.size()));
    MISD("model->columnCount() " + std::to_string(model->columnCount()));

    //Add Coloums AKA Cards
    if (vCards.size() + 1 > model->columnCount())
        for (auto C : vCards)
        {
            found = false;
            for (unsigned int i = 1; i < model->columnCount() && found == false; i++)
                found = Wt::asString(model->headerData(i, Wt::Orientation::Horizontal, Wt::ItemDataRole::ToolTip)) == C;

            if (found == false)
            {
                model->insertColumns(model->columnCount(), 1);
                model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, Bro->J->fusionIMG(entry(C, 0), entry(C, 1)), Wt::ItemDataRole::Decoration);
                model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, C, Wt::ItemDataRole::ToolTip);
                model->setHeaderData(model->columnCount() - 1, Wt::Orientation::Horizontal, "fusionIMG", Wt::ItemDataRole::StyleClass);
                //table->setHeaderAlignment(model->columnCount() - 1, Wt::AlignmentFlag::Middle);
            }
        }

    for (auto R : Bro->A_getRankeROW(EventNumber))
    {
        iRow = 0;
        iColumn = 0;
        for (unsigned int i = 0; i < model->rowCount(); i++)if (Wt::asString(model->data(i, 0)) == entry(R.ID, 0, "_"))
        {
            iRow = i;
            break;
        }

        for (unsigned int i = 0; i < model->columnCount(); i++)if (Wt::asString(model->headerData(i, Wt::Orientation::Horizontal, Wt::ItemDataRole::ToolTip)) == std::to_string(R.Stamps[0]) + ";" + std::to_string(R.Stamps[1]))
        {
            iColumn = i;
            break;
        }

        if (Wt::asString(model->data(iRow, iColumn)) == "")
        {
            model->setData(iRow, iColumn, sTime(R.Stamps[2]));
            model->setData(iRow, iColumn, "green", Wt::ItemDataRole::StyleClass);
            model->setData(iRow, iColumn, R.Stamps[2], Wt::ItemDataRole::ToolTip);
        }
    }
    unsigned int iCount;

    for (iRow = 0; iRow < model->rowCount(); iRow++)
    {
        iCount = 0;
        for (iColumn = 1; iColumn < model->columnCount(); iColumn++)
            if (Wt::asString(model->data(iRow, iColumn)) != "")
                iCount++;
        model->setData(iRow, 0, iCount, Wt::ItemDataRole::ToolTip);        
    }
    double dTime, ddTime;
    for (iColumn = 1; iColumn < model->columnCount(); iColumn++)
    {
        dTime = 9999999;
        for (iRow = 0; iRow < model->rowCount(); iRow++)
            if (Wt::asString(model->data(iRow, iColumn, Wt::ItemDataRole::ToolTip)) != "" &&
                Wt::asNumber(model->data(iRow, iColumn, Wt::ItemDataRole::ToolTip)) < dTime)
                dTime = Wt::asNumber(model->data(iRow, iColumn, Wt::ItemDataRole::ToolTip));
        
        for (iRow = 0; iRow < model->rowCount(); iRow++)
            if (Wt::asNumber(model->data(iRow, iColumn, Wt::ItemDataRole::ToolTip)) == dTime)
                model->setData(iRow, iColumn, "organe", Wt::ItemDataRole::StyleClass);
    }

    for (unsigned int i = 1; i < model->columnCount(); i++)
        table->setColumnWidth(i, 50);      
    MISE;
    return true;
}
