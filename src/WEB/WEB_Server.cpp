#define DF_Debug

#include "..\..\incl\Broker.h" 
#include "..\..\incl\WEB\WEB_Server.h"

broker *(WEB_Server::Bro) = NULL;

bool WEB_Server::connect(Client *client, const ChatEventCallback& handleEvent)
{
	MISS;
	mutex_Server.lock();
	if (clients_.count(client) == 0) {
		ClientInfo clientInfo;

		clientInfo.sessionId = Wt::WApplication::instance()->sessionId();
		clientInfo.eventCallback = handleEvent;

		clients_[client] = clientInfo;

		mutex_Server.unlock();
		MISEA("V1");
		return true;
	}

	mutex_Server.unlock();
	MISEA("V2");
	return false;
}

void WEB_Server::postChatEvent(const MISEvent& event)
{
	MISS;

	Wt::WApplication *app = Wt::WApplication::instance();
	MISD("X1");
	mutex_Server.lock();
	MISD("X2");

	for (ClientMap::const_iterator i = clients_.begin(); i != clients_.end(); ++i)
	{
		if (app && app->sessionId() == i->second.sessionId)
		{
			i->second.eventCallback(event);
		}
		else
		{
			server_.post(i->second.sessionId, std::bind(i->second.eventCallback, event));
		}
	}
	MISD("X3");
	mutex_Server.unlock();

	MISE;
}

void WEB_Server::postChatEventMIS(std::string Value1, std::string Value2, std::string Value3, std::string Value4)
{
	MISS;
	/*
	if (Value1 == "SYS")
	{
		if (Value2 == "SAVE")
		{
			//Bro->L_TriggerSave();
		}
	}
	else */
	postChatEvent(MISEvent(Value1, Value2, Value3, Value4));
	MISE;
}

bool WEB_Server::disconnect(Client *client)
{
	MISS;
	mutex_Server.lock();
	bool ret = clients_.erase(client) == 1;
	mutex_Server.unlock();

	MISE;
	return ret;
}
