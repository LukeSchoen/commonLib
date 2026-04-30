#include <stdlib.h>
#include <string.h>

#include "clString.h"

static char *clStringAllocateCopy(const char *text, int size)
{
  char *data = (char *)malloc((size_t)size + 1u);
  if (!data) return NULL;
  if (size > 0) memcpy(data, text, (size_t)size);
  data[size] = '\0';
  return data;
}

clString::clString(const char *text)
{
  this->SetText(text);
}

void clString::SetText(const char *text)
{
  char *copy = 0;
  int size = 0;
  if (text)
  {
    size = (int)strlen(text);
    copy = clStringAllocateCopy(text, size);
  }
  this->m_data = copy;
  this->m_size = size;
}

clString::~clString()
{
  free(this->m_data);
  this->m_data = NULL;
  this->m_size = 0;
}

int clString::Length()
{
  return this->m_size;
}

char clString::at(int index)
{
  return this->m_data[index];
}

clString clString::operator+(clString rhs)
{
  int leftSize = this->m_size;
  int rightSize = rhs.m_size;
  int size = leftSize + rightSize;
  char *buffer = (char *)malloc((size_t)size + 1u);
  int i = 0;
  clString out("");

  while (i < leftSize)
  {
    buffer[i] = this->m_data[i];
    i = i + 1;
  }
  while (i < size)
  {
    buffer[i] = rhs.m_data[i - leftSize];
    i = i + 1;
  }
  buffer[size] = '\0';

  out.m_data = buffer;
  out.m_size = size;
  return out;
}
