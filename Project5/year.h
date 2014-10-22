// Helen Chac && Gabriel Chan

#ifndef yearH
#define yearH
#include "linkedlist.h"
#include "day.h"

class Year
{
//  Day *days;
  LinkedList days;
//  Day day;
  int count;
  int size;
public:
  Year();
  ~Year();
  void addDate(int month, int day);
  int findDate(int month, int day) const;
  Year& operator+= (const Day &d);
  Year& operator-= (const Day &d);
  bool check(const Day &day);
  void read();
  void searchDate(int month, int day) const;
  void searchSubject(const char *s) const;
};  // class Year
#endif
