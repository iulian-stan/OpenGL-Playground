#include <iostream>
#include <fstream>
#ifdef WIN32 
#include <Windows.h>
#endif

#include "file_utils.h"

void Error(const char* pFileName, unsigned int line, const char* format, ...)
{
  char msg[1000];
  va_list args;
  va_start(args, format);
  VSNPRINTF(msg, sizeof(msg), format, args);
  va_end(args);

#ifdef WIN32 
  char msg2[1000];
  SNPRINTF(msg2, sizeof(msg2), "%s:%d: %s", pFileName, line, msg);
  MessageBoxA(NULL, msg2, NULL, 0);
#else
  fprintf(stderr, "%s:%d - %s", pFileName, line, msg);
#endif    
}

bool ReadFile(const char* pFileName, std::string& outFile)
{
  std::ifstream f(pFileName);

  bool ret = false;

  if (f.is_open()) {
    std::string line;
    while (std::getline(f, line)) {
      outFile.append(line);
      outFile.append("\n");
    }

    f.close();

    ret = true;
  }
  else {
    ERROR("Could not open %s\n", pFileName);
  }

  return ret;
}