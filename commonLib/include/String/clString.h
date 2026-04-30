#ifndef clString_h
#define clString_h

#include <stddef.h>

class clString
{
public:
  clString(const char *text);
  ~clString();

  int Length();
  void SetText(const char *text);
  char at(int index);
  clString operator+(clString rhs);

public:
  char *m_data;
  int m_size;
};

#endif
