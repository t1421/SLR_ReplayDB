#ifndef Utility_H
#define Utility_H

#include <string>

void Sleep(int time);

bool Checker(std::string &check, std::string name);

inline bool File_exists(const std::string& name);

inline std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

std::string sTime(unsigned long ulTime);

#endif //Utility_H


