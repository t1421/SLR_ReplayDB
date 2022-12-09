//#define DF_Debug

#include "Broker.h" 

#include "Reader.h" 

#include <sstream>
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
unsigned long long Reader::readUnsignedLongLong()
{
	unsigned long value = 0;
  	for (int i = 0; i < 8; ++i) 
    	value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i);  
  return value;
}

unsigned long Reader::readUnsignedLong()
{
	unsigned long value = 0;
  	for (int i = 0; i < 4; ++i) 
		value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i);
  return value;
}

unsigned short Reader::readUnsignedShort()
{
	unsigned short value = 0;
  	for (int i = 0; i < 2; ++i) 
    	value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i);  	
  	return value;
}

unsigned char Reader::readUnsignedChar()
{
	return (unsigned short)PMVbuffer[PMVPosition++];
}


std::string Reader::readString()
{
	std::stringstream ssOUT;
	unsigned long len = readUnsignedLong();	
	for (unsigned int iPos = 0; iPos < len; iPos++)ssOUT << PMVbuffer[PMVPosition++];
	return ssOUT.str();
}


std::string Reader::readWString()
{
	
	std::wstringstream wss;
	std::wstring ws;
	std::string sOut;
	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;
	
	unsigned long len = readUnsignedLong() * 2;
	for (unsigned int iPos = 0; iPos < len; iPos++)wss << PMVbuffer[PMVPosition++];

	ws = wss.str();
	sOut = converterX.to_bytes(ws); 
	len = 0;
	while ((len = sOut.find(char(0), len)) != sOut.npos)sOut.replace(len, 1, "");

	return sOut;
}

bool Reader::Open(std::string sFile)
{
	MISS;

	sFile = sAddDoubleBackslash(sFile);

	PMVFile.open(sFile, std::ios_base::binary);
	if (!PMVFile) 
	{
		MISEA("V1 " + sFile)
		return false;
	}

	PMVFile.seekg(0, std::ios_base::end);
	length = PMVFile.tellg();
	PMVFile.seekg(0, std::ios_base::beg);
	
	PMVbuffer.clear();
	PMVbuffer.reserve(length);
	PMVFile.read(&PMVbuffer[0], length);
	PMVFile.clear();
	PMVFile.close();

	if (length <= 0)
	{
		MISEA("V2")
		return false;
	}

	if (PMVbuffer[0] != 'P'
		&& PMVbuffer[1] != 'M'
		&& PMVbuffer[2] != 'V')
	{
		MISEA("V3")
		return false;
	}
	MISD(std::to_string(PMVbuffer[0]));
	MISD(std::to_string(PMVbuffer[1]));
	MISD(std::to_string(PMVbuffer[2]));

	// Pos 0-2 = "PMV"
	PMVPosition = 3;

	return true;

	MISE;
}

std::string Reader::sAddDoubleBackslash(std::string changeString)
{
	MISS;
	for (unsigned int start_pos = 0; start_pos <= changeString.length(); start_pos++)if (changeString[start_pos] == char(92))
	{
		changeString.insert(start_pos, "\\");
		start_pos++;
	}
	MISE;
	return changeString;
}