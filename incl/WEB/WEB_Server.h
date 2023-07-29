#ifndef WEB_Server_H
#define WEB_Server_H

#include <map>
#include <Wt/WServer.h>

class MISEvent;

typedef std::function<void(const MISEvent&)> ChatEventCallback;

class WEB_Server 
{
public:
	class Client {};

	
	WEB_Server(Wt::WServer& server) : server_(server) {};

	bool connect(Client *client, const ChatEventCallback& handleEvent);
	bool disconnect(Client *client);

	void WEB_Server::postChatEventMIS(std::string Value1, std::string Value2, std::string Value3, std::string Value4);

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }


private:
	struct ClientInfo {
		std::string sessionId;
		ChatEventCallback eventCallback;
	};

	std::mutex mutex_Server;

	typedef std::map<Client *, ClientInfo> ClientMap;
	Wt::WServer& server_;
	ClientMap clients_;

	void postChatEvent(const MISEvent& event);
	
};

class MISEvent
{
public:
	const Wt::WString& message() const { return message_; }

	Wt::WString message_;
	std::string Value1_;
	std::string Value2_;
	std::string Value3_;
	std::string Value4_;
private:
	MISEvent(std::string Value1, std::string Value2, std::string Value3, std::string Value4)
		: Value1_(Value1), Value2_(Value2), Value3_(Value3), Value4_(Value4) { }

	friend class WEB_Server;
};

#endif // WEB_Server_H

