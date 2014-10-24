// Helen Chac

#include <iostream>
#include <iomanip>
#include "appointment.h"
#include "day.h"
#include "dayofweek.h"

using namespace std;

Day::Day() : apptCount(0)
{
} // Day()

Day::Day(short mo, short d): apptCount(0)
{
  month = mo;
  day = d;
//  appts = new Appointment;
}//constructor();

Day& operator+= (Day &day, Day &nday)
{
  day.appts[day.apptCount] = new Appointment;
  *(day.appts[day.apptCount]) = *(nday.appts[0]);
  day.apptCount++;
  return day;
}//+= operator

short Day::getmonth()
{
  return month;
}//getmonth getterfunction

short Day::getday()
{
  return day;
}//getday getter functio)
istream& operator>> (istream& is, Day &day)
{
  day.appts[day.apptCount] = new Appointment;
  is >> *(day.appts[day.apptCount]);
 
  return is;
}//>>operator


Day::~Day()
{
  for(int j = 0; j < apptCount; j++)
    delete  appts[j];
} // ~Day()


int Day::compareDate(short mo, short d) const
{
  if(month == mo)
    return day - d;
  else
    return month - mo;
}//compareDate();

ostream& operator<< (ostream& os, const Day &day)
{
  DayOfWeek dayOfWeek(day.month, day.day);
  dayOfWeek.read();
  os << dayOfWeek;
  return os;
}// << operator

void Day::printAppts() const
{
  for(int j = 0; j < apptCount; j++)
  cout << *appts[j];
//    appts[j]->print();
}  // printAppts()


void Day::printSubject( const char *s, bool &found) const
{
  Appointment app(s);
  for(int j = 0; j < apptCount; j++)
//    if(appts[j]->compareSubject(s))
    if (*appts[j] == app)
    {
      if(!found)
        cout << "Date                           Start End   Subject         "
          << "Location\n";

      cout << *this;
      cout << *appts[j];
      found = true;
    } // if appts matched subject
} // printSubject()


void Day::read()
{
  appts[apptCount] =  new Appointment;
  appts[apptCount++]->read();
} // read()


void Day::reset(short mo, short d)
{
  month = mo;
  day = d;

  for(int j = 0; j < apptCount; j++)
    delete appts[j];
  apptCount = 0;
}  // setDate()


Day& Day::operator= (const Day &d)
{
  if(this == &d)
    return *this;

  for(int j = 0; j < apptCount; j++)
    delete  appts[j];

  day = d.day;
  month = d.month;
  apptCount = d.apptCount;

  for(int i = 0; i < apptCount; i++)
  {
    appts[i] = new Appointment();
    *appts[i] = *d.appts[i];
  }

  return *this;
}  // operator=
