#ifndef Reader_H
#define Reader_H

#include <fstream>
#include <vector>

#define MaxString 512

class Reader
{
public:
	Reader();
	~Reader();

	bool Open(std::string sFile);
	//bool SaveFile(std::string sFile);
	unsigned long readUnsignedLong();
	unsigned char readUnsignedChar();	
	unsigned short readUnsignedShort();
	unsigned long long readUnsignedLongLong();
	std::string readString();
	std::string readWString();

	//BROKER
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }

	unsigned int PMVPosition;
	size_t length;
#if defined BrokerPVP
	size_t lastRead;
	void closeFile() { PMVFile.close(); };
	int readDeltaPMV();
#endif
protected:
	std::string sAddDoubleBackslash(std::string changeString);

private:
	std::ifstream     PMVFile;
	std::vector<char> PMVbuffer;


	

	


};

#endif //Reader_H


