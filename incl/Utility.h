#ifndef Utility_H
#define Utility_H

#include <string>

void Sleep(int time);

std::string formatString(const std::string& text, int length);

bool Checker(std::string &check, std::string name);
bool INI_Value_Check(std::string &check, std::string name);

inline bool File_exists(const std::string& name);

inline std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

std::string sTime(unsigned long ulTime);
std::string sTimeFull(unsigned long ulTime);

std::string entry(std::string Liste, int pos);

unsigned long long STRtoNUM(std::string sIN);

#endif //Utility_H


