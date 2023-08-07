#include <chrono>
#include <thread>
#include <fstream>



void Sleep(int time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

std::string entry(std::string Liste, int pos)
{
	if (pos == 0)return Liste.substr(0, Liste.find(";"));
	else
	{
		Liste.erase(0, Liste.find(";") + 1);
		return entry(Liste, pos - 1);
	}
}