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