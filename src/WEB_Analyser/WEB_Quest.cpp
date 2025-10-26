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
                    model->setData(model->rowCount() - 1, i + 3, "green", Wt::ItemDataRole::StyleClass);
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

    return;


    MISD("#3");
    model->insertRows(model->rowCount(), 1);
    model->setData(0, 0, 1);
    model->setData(0, 1, Wt::WString("Alice"));
    model->setData(0, 2, 85);
    model->setData(0, 2, "green", Wt::ItemDataRole::StyleClass);

    //wcChart->setStyleClass("yChart");

    model->insertRows(model->rowCount(), 1);
    model->setData(1, 0, 2);
    model->setData(1, 1, Wt::WString("Bob"));
    model->setData(1, 2, 90);
    model->setData(1, 2, "black", Wt::ItemDataRole::StyleClass);

    model->insertRows(model->rowCount(), 1);
    model->setData(2, 0, 3);
    model->setData(2, 1, Wt::WString("Charlie"));
    model->setData(2, 2, 75);

    model->insertRows(model->rowCount(), 1);
    model->setData(3, 0, 4);
    model->setData(3, 1, Wt::WString("Diana"));
    model->setData(3, 2, 95);

    model->insertRows(model->rowCount(), 1);
    model->setData(4, 0, 5);
    model->setData(4, 1, Wt::WString("Eve"));
    model->setData(4, 2, 80);

    MISD("#4");

    
    MISD("#5");
    proxy->setSourceModel(std::shared_ptr<Wt::WAbstractItemModel>(model));
    proxy->setDynamicSortFilter(true);
    proxy->setFilterKeyColumn(1);
    proxy->setFilterRole(Wt::ItemDataRole::Display);

    MISD("#6");
    table->setModel(std::shared_ptr<Wt::WAbstractItemModel>(proxy));
    table->setSortingEnabled(true);  // <-- WICHTIG: Sortieren aktivieren
    table->setColumnResizeEnabled(true);
    table->setAlternatingRowColors(true);
    table->setSelectionMode(Wt::SelectionMode::Single);
    table->setRowHeight(28);

    table->setColumnWidth(0, 50);
    table->setColumnWidth(1, 120);
    table->setColumnWidth(2, 80);

  
    MISD("#6");

    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(filterEdit)));
    layout->addWidget(std::unique_ptr<Wt::WWidget>(std::move(table)));

    MISD("#7");
    
    filterEdit->changed().connect([=] {
        std::regex re = std::regex(".*" + filterEdit->text().toUTF8() + ".*", std::regex_constants::icase | std::regex_constants::ECMAScript);
        proxy->setFilterRegExp(std::make_unique<std::regex>(std::move(re)));
        });

	MISE;
}

void WEB_Quest::WRefresh()
{
	MISS;

    unsigned long iTimes[RankRowStamps] = { 0 };
    unsigned long long iValue = 0;
    std::string sReturn = "";
    std::string sEvent = "";

    EventData* Quest = nullptr;
    QuestPlayer* QPlayer = nullptr;

    status->setText("Checking...");
    //find correct Event
    switch (str2int(WR->getMapName().c_str()))
    {
    case (str2int("sss1.map")):
        sReturn = WR->Kalk_Event0(iTimes, "sss1.map");
        sEvent = "201";
        iValue += iTimes[0] * 10000; //time
        iValue += iTimes[2] * 1; //power
        break;
    }
    MISD("#1");
    if (sEvent == "")
    {
        status->setText("No Event found");
        MISEA("No Quest");
        return;
    }

    for (EventData* Q : Bro->L->Quests)if (std::to_string(Q->ID) == sEvent)Quest = Q;
    if(Quest == nullptr)
    {
        status->setText("No Event found X");
        MISEA("No Quest XXX");
        return;
    }
    
    if (sReturn != "")
    {
        status->setText("<h3 style='color:Tomato;'>Quest: " + Quest->Name + " Error: " + sReturn + "</h3>");
        MISEA("Error in Check");
        return;
    }
    MISD("#2");

    //Add all Players of replay
    for (auto PID : WR->ActivePlayers())
    {
        for (auto QP : Bro->QPlayer)
            if (QP->PlayerID == std::to_string(PID))
                QPlayer = QP;

        MISD("#3");
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

        MISD("#4");
        if (QPlayer->UpdateEvent(sEvent, iValue))
        {
            MISD("#44");
            for (unsigned int i = 0; i < model->rowCount(); i++)
            {
                MISD("#45");
                if (Wt::asString(model->data(i, 0)) == QPlayer->PlayerID)
                {
                    MISD("#46");
                    model->setData(i, 2, QPlayer->Stamps.size());
                    for (auto QPQ : QPlayer->Stamps)
                    {
                        MISD("#47");
                        for (unsigned int ii = 0; ii < Bro->L->Quests.size(); ii++)
                        {
                            MISD(std::to_string(Bro->L->Quests[ii]->ID) + " - " + QPQ.first);
                            if (std::to_string(Bro->L->Quests[ii]->ID) == QPQ.first)
                            {
                                MISD("#5");
                                model->setData(i, ii + 3, QPQ.second);
                                model->setData(i, ii + 3, "green", Wt::ItemDataRole::StyleClass);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    status->setText("Nice run :-)");
    Bro->saveQPlayer();
    

	MISE;
}

