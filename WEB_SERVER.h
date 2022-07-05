#ifndef WEB_SERVER_H
#define WEB_SERVER_H

class MISEvent;

typedef std::function<void(const MISEvent&)> ChatEventCallback;

class MISSERVER 
{
public:
	class Client{};

	MISSERVER(WServer& server) : server_(server) {};

	bool connect(Client *client, const ChatEventCallback& handleEvent);
	bool disconnect(Client *client);

	void MISSERVER::postChatEventMIS(string Value1, string Value2, string Value3, string Value4);

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	
private:
	struct ClientInfo {
		string sessionId;
		ChatEventCallback eventCallback;
	};
	
	mutex mutex_Server;

	typedef map<Client *, ClientInfo> ClientMap;
	WServer& server_;
	ClientMap clients_;

	void postChatEvent(const MISEvent& event);
};


class MISEvent
{
public:
	const WString& message() const { return message_; }

	WString message_;
	string Value1_;
	string Value2_;
	string Value3_;
	string Value4_;
private:
	MISEvent(string Value1, string Value2, string Value3, string Value4)
		: Value1_(Value1), Value2_(Value2), Value3_(Value3), Value4_(Value4)	{ }	

	friend class MISSERVER;
};


#endif // WEB_SERVER_H
