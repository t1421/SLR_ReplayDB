#define DF_Debug

#include "prototypes.h"

#include "WEB_Main.h"
#include "WEB_SERVER.h"

//#include "SQL_MIS.h"

broker *(MISSERVER::Bro) = NULL;

bool MISSERVER::connect(Client *client, const ChatEventCallback& handleEvent)
{
	MISS;
	mutex_Server.lock();
	if (clients_.count(client) == 0) {
		ClientInfo clientInfo;

		clientInfo.sessionId = WApplication::instance()->sessionId();
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

void MISSERVER::postChatEvent(const MISEvent& event)
{
	MISS;

	WApplication *app = WApplication::instance();
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

void MISSERVER::postChatEventMIS(string Value1, string Value2, string Value3, string Value4)
{
	MISS;
	if (Value1 == "SYS")
	{
		if (Value2 == "SAVE")
		{
			
		}
	}
	else postChatEvent(MISEvent(Value1, Value2, Value3, Value4));
	MISE;
}

bool MISSERVER::disconnect(Client *client)
{
	MISS;
	mutex_Server.lock();
	bool ret = clients_.erase(client) == 1;
	mutex_Server.unlock();

	MISE;
	return ret;
}
