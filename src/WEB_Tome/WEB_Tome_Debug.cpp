#define DF_Debug

#include "..\..\incl\Broker.h"
#include "..\..\incl\WEB_Tome\WEB_Tome_Debug.h"

#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WGridLayout.h>
#include <Wt/WPushButton.h>


broker *(WEB_Tome_Debug::Bro) = NULL;

WEB_Tome_Debug::WEB_Tome_Debug(WEB_Container_Tome *Con_) : Con(Con_)
{
	MISS;

	cMain = new Wt::WContainerWidget();
	Wt::WGridLayout *TempGrid = new Wt::WGridLayout();
	cMain->setLayout(std::unique_ptr<Wt::WGridLayout>(std::move(TempGrid)));
	MISD("#0");

	messages_ = new Wt::WContainerWidget();
	sendButton_ = new Wt::WPushButton("Send");
	messageEdit_ = new Wt::WTextArea();

	MISD("#1");

	messages_->setHeight(200);
	messageEdit_->setRows(1);
	messageEdit_->setFocus();

	MISD("#3");

	TempGrid->addWidget(std::unique_ptr<Wt::WPushButton>(std::move(sendButton_)), 0, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WTextArea>(std::move(messageEdit_)), 1, 0);
	TempGrid->addWidget(std::unique_ptr<Wt::WWidget>(std::move(messages_)), 2, 0);

	MISD("#5");
	sendButton_->clicked().connect(std::bind([=]() {
		send();
	}));
	messageEdit_->enterPressed().connect(std::bind([=]() {
		send();
	}));
	MISD("#6");

	WRefresh();

	MISE;
}

void WEB_Tome_Debug::WRefresh()
{
	MISS;
	
	MISE;
}


void WEB_Tome_Debug::send()
{
	MISS;
	if (!messageEdit_->text().empty())
	{
		std::string sMessage = WSTRINGtoSTRING(messageEdit_->text()) + ";";
		std::string MesValue1 = sMessage.substr(0, sMessage.find(";"));
		sMessage.erase(0, sMessage.find(";") + 1);
		std::string MesValue2 = sMessage.substr(0, sMessage.find(";"));
		sMessage.erase(0, sMessage.find(";") + 1);
		std::string MesValue3 = sMessage.substr(0, sMessage.find(";"));
		sMessage.erase(0, sMessage.find(";") + 1);
		std::string MesValue4 = sMessage.substr(0, sMessage.find(";"));
		sMessage.erase(0, sMessage.find(";") + 1);

		Bro->postChatEventMIS(MesValue1, MesValue2, MesValue3, MesValue4);
	}

	messageEdit_->setText("");
	MISE;	
}

void WEB_Tome_Debug::UpdateMes(std::string _Input)
{
	MISS;
	Wt::WText *w = messages_->addWidget(Wt::cpp14::make_unique<Wt::WText>());
	MISD("#1");
	w->setText(_Input);
	MISD("#2");
	w->setInline(false);
	MISD("#3");
	if (messages_->count() > 10)
		messages_->removeChild(messages_->children()[0]);
	MISE;
}