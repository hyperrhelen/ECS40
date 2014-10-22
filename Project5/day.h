// Helen Chac && Gabriel Chan

#ifndef dayH
#define dayH

#include "appointment.h"

class Day
{
  short day;
  short month;
  Appointment *appts[8];
  short apptCount;
  friend class LinkedList;
  friend class Year;
public:
  Day();
  Day(short mo, short d);
  Day(Day &d);
  ~Day();
  int compareDate(short mo, short d) const;
  short getDay() const;
  short getMonth() const;
  Day& operator= (const Day &d);
  Day& operator+= (const Day & d);
  friend ostream& operator<< (ostream & os, const Day &d);
  friend istream& operator>> (istream & is, Day &d);
  bool operator< (const Day &rhs);
  bool operator== (const Day &rhs);
  void printAppts() const;
  void printSubject(const char *s, bool &found) const;
  void read();
  void reset(short mo, short d);
}; // class Day

#endif
