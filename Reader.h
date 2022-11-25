#ifndef Reader_H
#define Reader_H

#include <fstream>
#include <vector>

union UnsignedLongLongUnion { unsigned long ull; char b[8]; };
union UnsignedLongUnion { unsigned long ul; char b[4]; };
union UnsignedShortUnion { unsigned short us; char b[2]; };

#define MaxString 512

class Reader
{
public:
	Reader();
	~Reader();

	bool Open(std::string sFile);
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
protected:
	std::string sAddDoubleBackslash(std::string changeString);

private:
	UnsignedLongLongUnion ULLU;
	UnsignedLongUnion ULU;
	UnsignedShortUnion USU;

	std::ifstream     PMVFile;
	std::vector<char> PMVbuffer;


	

	


};

#endif //Reader_H


