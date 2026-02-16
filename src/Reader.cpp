//#define DF_Debug

#include "..\incl\Broker.h" 

#include "..\incl\Reader.h" 

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
//unsigned long long	///64
unsigned long long Reader::readUnsignedLongLong()
{
	MISS;
	unsigned long value = 0;
  	for (int i = 0; i < 8; ++i) 
    	value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i); 

	MISEA("" + std::to_string(value));
	return value;
}

unsigned long Reader::readUnsignedLong()
{
	MISS;
	unsigned long value = 0;	
	for (int i = 0; i < 4; ++i)
		value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i);
		
	MISEA("" + std::to_string(value));
	return value;
}

float Reader::readFloat()
{
	MISS;
	float value;
	uint8_t bytes[4];

	for (int i = 0; i < 4; ++i)
		bytes[i] = PMVbuffer[PMVPosition++];

	std::memcpy(&value, bytes, sizeof(float));
	MISEA("" + std::to_string(value));
	return value;
}

unsigned short Reader::readUnsignedShort()
{
	MISS;
	unsigned short value = 0;
  	for (int i = 0; i < 2; ++i) 
    	value += (unsigned long)(PMVbuffer[PMVPosition++] & 0xFF) << (8 * i);  	

	MISEA("" + std::to_string(value));
  	return value;
}

unsigned char Reader::readUnsignedChar()
{
	MISS;
	MISEA("" + std::to_string((unsigned short)PMVbuffer[PMVPosition]))
	return (unsigned short)PMVbuffer[PMVPosition++];
}


std::string Reader::readString()
{
	MISS;
	std::stringstream ssOUT;
	unsigned long len = readUnsignedLong();		
	for (unsigned int iPos = 0; iPos < len; iPos++)ssOUT << PMVbuffer[PMVPosition++];
	MISEA("" + ssOUT.str());
	return ssOUT.str();
}

std::string Reader::readWString()
{
	MISS;
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

	MISEA("" + sOut);
	return sOut;
}
/*
bool Reader::SaveFile(std::string sFile)
{
	MISS;
	std::ofstream PMVFile;
	sFile = sAddDoubleBackslash(sFile);
	PMVFile.open(sFile, std::ios_base::binary);
	if (!PMVFile)
	{
		MISEA("V1 " + sFile);
		return false;
	}
	MISD(PMVbuffer.size());
	for(auto c: PMVbuffer) PMVFile << c;
	PMVFile.close();

	MISE;
	return false;
}
*/
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
#if defined BrokerPVP
	lastRead = length;
#else
	PMVFile.close();
#endif // BrokerPVP

	

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

#if defined BrokerPVP
int Reader::readDeltaPMV()
{
	MISS;
	PMVFile.seekg(0, std::ios_base::end);
	length = PMVFile.tellg();
	//MISD(length);

	if (length == lastRead)
	{
		MISEA("nichts neues");
		return 0;
	}
	else if (length < lastRead)
	{
		MISEA("new File");
		return -1;
	}

	PMVFile.seekg(lastRead);
	PMVbuffer.resize(length);
	PMVFile.read(&PMVbuffer[lastRead], length - lastRead);
	PMVFile.clear();
	lastRead = length;

	MISE;
	return 1;
}
#endif