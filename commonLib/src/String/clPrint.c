#include "clPrint.h"

#include <windows.h>

void clPrint(char *text)
{
  DWORD written;

  if (!text)
    return;

  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), text, lstrlenA(text), &written, NULL);
  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, &written, NULL);
}
