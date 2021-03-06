#ifndef Reader_H
#define Reader_H

union UnsignedLongLongUnion { unsigned long ull; byte b[8]; };
union UnsignedLongUnion { unsigned long ul; byte b[4]; };
union UnsignedShortUnion { unsigned short us; byte b[2]; };

#define MaxString 512

class Reader
{
public:
	Reader();
	~Reader();

	bool Open(string sFile);
	unsigned long readUnsignedLong();
	unsigned char readUnsignedChar();	
	unsigned short readUnsignedShort();
	unsigned long long readUnsignedLongLong();
	string readString();
	string readWString();

	//BROKER
#ifndef noBroker
	static broker* Bro;
	static void learnBro(broker *_Bro) { Bro = _Bro; }
#endif

	unsigned int PMVPosition;
	size_t length;
protected:
	string sAddDoubleBackslash(string changeString);

private:
	UnsignedLongLongUnion ULLU;
	UnsignedLongUnion ULU;
	UnsignedShortUnion USU;

	ifstream     PMVFile;
	vector<char> PMVbuffer;


	

	


};

#endif //Reader_H


