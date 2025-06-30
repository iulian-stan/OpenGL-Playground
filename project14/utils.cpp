#include <cstdio>
#include <cstdlib>
#include "utils.h"

bool ReadFile(const char* pFileName, const char*& pText, int& length)
{
  FILE* f = fopen(pFileName, "rb");
  if (f == NULL)
  {
    fprintf(stderr, "Error reading file %s\n", pFileName);
    return false;
  }
  fseek(f, 0, SEEK_END);
  length = ftell(f);
  fseek(f, 0, SEEK_SET);

  pText = (char*)malloc(length + 1);
  if (pText == NULL)
  {
    fprintf(stderr, "Error allocating text buffer\n");
    return false;
  }
  fread((void*)pText, 1, length, f);
  ((char*)pText)[length] = 0;

  fclose(f);
  return true;
}