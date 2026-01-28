#ifndef Stream_H
#define Stream_H

#include "Thread_MIS.h"

class Stream : public Thread_MIS
{
public:
	Stream();
	~Stream();

	void Init();

	//BROKER
	static broker* Bro;
	void teachS() { Bro->S = this; }
	static void learnBro(broker *_Bro) { Bro = _Bro; }

private:
	
	void Thread_Function();
	void ProcessFile();
	std::string CleanCardNames(std::string sIN);
	std::string CleanChatMessage(std::string sIN);	
	void MessageToVectors(std::string sIN, std::vector<std::string>& V1, std::vector<std::string>& V2, std::vector<std::string>& V3);

	std::vector <std::pair<std::string,std::string>> CardPool;
	std::vector <std::string> TwitchEmots;

	std::streampos lastPosInFile;
	
};

#endif //Stream



