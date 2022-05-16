//#define DF_Debug

#include "stdafx.h"

#include "Reader.h" 

#include <locale>
#include <codecvt>

broker *(Reader::Bro) = NULL;

Reader::Reader()
{
	MISS;
	
	MISE;
}

Reader::~Reader()
{
	MISS;
	
	MISE;
}
//unsigned char			/// 8
//unsigned short		///16
//unsigned long			///32
//unsigned long long	///62
unsigned long long Reader::readUsignedLongLong()
{
	ULLU.b[0] = PMVbuffer[PMVPosition++];
	ULLU.b[1] = PMVbuffer[PMVPosition++];
	ULLU.b[2] = PMVbuffer[PMVPosition++];
	ULLU.b[3] = PMVbuffer[PMVPosition++];
	ULLU.b[4] = PMVbuffer[PMVPosition++];
	ULLU.b[5] = PMVbuffer[PMVPosition++];
	ULLU.b[6] = PMVbuffer[PMVPosition++];
	ULLU.b[7] = PMVbuffer[PMVPosition++];
	return ULLU.ull;
}

unsigned long Reader::readUnsignedLong()
{
	ULU.b[0] = PMVbuffer[PMVPosition++];
	ULU.b[1] = PMVbuffer[PMVPosition++];
	ULU.b[2] = PMVbuffer[PMVPosition++];
	ULU.b[3] = PMVbuffer[PMVPosition++];
	return ULU.ul;
}

unsigned short Reader::readUnsignedShort()
{
	USU.b[0] = PMVbuffer[PMVPosition++];
	USU.b[1] = PMVbuffer[PMVPosition++];
	return USU.us;
}

unsigned char Reader::readUnsignedChar()
{
	return (unsigned char)PMVbuffer[PMVPosition++];
}


string Reader::readString()
{
	stringstream ssOUT;
	unsigned long len = readUnsignedLong();	
	for (unsigned int iPos = 0; iPos < len; iPos++)ssOUT << PMVbuffer[PMVPosition++];
	return ssOUT.str();
}


string Reader::readWString()
{
	
	wstringstream wss;
	wstring ws;
	string sOut;
	using convert_typeX = codecvt_utf8<wchar_t>;
	wstring_convert<convert_typeX, wchar_t> converterX;
	
	unsigned long len = readUnsignedLong() * 2;
	for (unsigned int iPos = 0; iPos < len; iPos++)wss << PMVbuffer[PMVPosition++];

	ws = wss.str();
	sOut = converterX.to_bytes(ws); 
	len = 0;
	while ((len = sOut.find(char(0), len)) != sOut.npos)sOut.replace(len, 1, "");

	return sOut;
}

bool Reader::Open(string sFile)
{
	MISS;

	PMVFile.open(sFile,ios_base::binary);
	if (!PMVFile) 
	{
		MISEA("V1")
		return false;
	}

	PMVFile.seekg(0, std::ios_base::end);
	length = PMVFile.tellg();
	PMVFile.seekg(0, std::ios_base::beg);
	
	PMVbuffer.clear();
	PMVbuffer.reserve(length);
	PMVFile.read(&PMVbuffer[0], length);
	PMVFile.close();

	if (length <= 0)
	{
		MISEA("V2")
		return false;
	}

	// Pos 0-2 = "PMV"
	PMVPosition = 3;

	return true;

	MISE;
}