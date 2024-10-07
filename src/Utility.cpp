#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>

std::string formatString(const std::string& text, int length) 
{
	std::string formattedText = text.substr(0, length);
	formattedText.resize(length, ' ');
	return formattedText;
}

void Sleep(int time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

bool Checker(std::string &check, std::string name)
{
	if (check.substr(0, check.find(";")) == name)
	{
		check.erase(0, check.find(";") + 1);
		return true;
	}
	else
	{
		return false;
	}
}

bool INI_Value_Check(std::string &check, std::string name)
{
	if (check.substr(0, check.find("=")) == name)
	{
		check.erase(0, check.find("=") + 1);
		return true;
	}
	else
	{
		return false;
	}
}

bool File_exists(const std::string& name) 
{
	std::ifstream f(name.c_str());
	return f.good();
}

std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string sTime(unsigned long ulTime)
{
	char cOut[6];
	snprintf(cOut, 6, "%02d:%02d", int(floor(ulTime / 600)), int(ulTime / 10 % 60));
	return cOut;
}

std::string sTimeFull(unsigned long ulTime)
{
	char cOut[8];
	snprintf(cOut, 8, "%02d:%02d,%d", int(floor(ulTime / 600)), int(ulTime / 10 % 60), int(ulTime % 10));
	return cOut;
}

std::string entry(std::string Liste, int pos)
{
	if (pos == 0)return Liste.substr(0, Liste.find(";"));
	else
	{
		Liste.erase(0, Liste.find(";") + 1);
		return entry(Liste, pos - 1);
	}
}

unsigned long long STRtoNUM(std::string sIN)
{
	std::string sOUT;
	for (char c : sIN) if (isdigit(c)) sOUT += c;
	return atoi(sOUT.c_str());
}

void Twitch_Message(std::string ID, std::string Line1, std::string Line2, std::string Line3, std::string Line4, std::string Line5)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(100000, 999999 - 1);

	std::stringstream ssMessage;
	ssMessage << Line1 << "\n";
	ssMessage << Line2 << "\n";
	ssMessage << Line3 << "\n";
	ssMessage << Line4 << "\n";
	ssMessage << Line5 << "\n";

	std::ofstream Massage(".\\Twitch\\MES" + ID + "_" + std::to_string(distr(gen)), std::ios::trunc);
	Massage << ssMessage.str() << "\n";
	Massage.close();
}
void Twitch_Message(std::string ID, std::string Line1, std::string Line2, std::string Line3, std::string Line4)
{
	Twitch_Message(ID, Line1, Line2, Line3, Line4, "");
}
void Twitch_Message(std::string ID, std::string Line1, std::string Line2, std::string Line3)
{
	Twitch_Message(ID, Line1, Line2, Line3, "");
}
void Twitch_Message(std::string ID, std::string Line1, std::string Line2)
{
	Twitch_Message(ID, Line1, Line2, "");
}
void Twitch_Message(std::string ID, std::string Line1)
{
	Twitch_Message(ID, Line1, "");
}


std::string TimeToText(std::time_t timestamp)
{
	std::tm localTime;
	localtime_s(&localTime, &timestamp);
	std::ostringstream oss;
	oss << std::put_time(&localTime, "%d.%m.%Y %H:%M:%S");
	return oss.str();
}