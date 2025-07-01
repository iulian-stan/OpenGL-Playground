#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

void Error(const char* pFileName, unsigned int line, const char* msg, ... );

bool ReadFile(const char* pFileName, std::string& outFile);

#define ERROR(msg, ...) Error(__FILE__, __LINE__, msg, __VA_ARGS__)
#ifdef WIN32
#define SNPRINTF _snprintf_s
#define VSNPRINTF vsnprintf_s
#else
#define SNPRINTF snprintf
#define VSNPRINTF vsnprintf
#endif

#endif //FILE_UTILS_H