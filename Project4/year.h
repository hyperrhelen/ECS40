// Helen Chac

#ifndef yearH
#define yearH

#include "day.h"

class Year
{
  Day *days;
  int count;
  int size;
  friend Year& operator+= (Year &year, Day &day);
public:
  Year();
  ~Year();
  void addDate(int month, int day);
  int findDate(int month, int day) const;
  void read();
  void searchDate(int month, int day) const;
  void searchSubject(const char *s) const;
};  // class Year
#endif
