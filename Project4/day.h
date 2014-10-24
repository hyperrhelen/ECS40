//Helen Chac

#ifndef dayH
#define dayH

#include <iostream>
#include "appointment.h"
using namespace std;

class Day
{
private:
  short day;
  short month;
  Appointment *appts[8];
  short apptCount;
  friend istream& operator>> (istream& is, Day &day);
  friend ostream& operator<< (ostream& os, const Day &day);
  friend Day& operator< (Day &day, Day& nday);
  friend Day& operator+= (Day &day, Day &nday);
public:
  Day();
  Day(short mo, short d);
  ~Day();
  int compareDate(short mo, short d) const;
  void printAppts() const;
  void printSubject(const char *s, bool &found) const;
  void read();
  void reset(short mo, short d);
  Day& operator= (const Day &d);
  short getmonth();
  short getday();
}; // class Day

#endif
