// Helen Chac

#ifndef appointmentH
#define appointmentH

#include "time.h"

class Appointment
{
private:
  Time startTime;
  Time endTime;
  char *subject;
  char *location;
  friend ostream& operator<< (ostream& os, const Appointment &appointment);
  friend istream& operator>> (istream& is, Appointment &temp);
  friend bool operator== (Appointment &tf, Appointment &s);
public:
  Appointment();
  Appointment(const char *s);
  ~Appointment();
  void read();
  bool compareSubject(const char *s) const;
  Appointment& operator= (const Appointment &a);
  short getmonth();
  short getday();
}; // class Appointment

#endif
