// Helen Chac && Gabriel Chan

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "year.h"
#include "linkedlist.h"
#include "day.h"

using namespace std;

Year::Year():count(0), size(30)
{
}  // Year()


Year::~Year()
{
}  // ~Year()


int Year::findDate(int month, int day) const
{
  for(int i = 0; i < count; i++)
    if(days[i].compareDate(month, day) == 0)
      return i;

  return count; // not found
} // findDate()

Year& Year::operator+= (const Day &day)
{
  int pos = findDate(day.getMonth(), day.getDay());

  if(pos == count)
  {
    days += day;
    pos = findDate(day.getMonth(), day.getDay());
  } // if date not found
  else
    days[pos] += day;

  return *this;
} // operator+=

Year& Year::operator-= (const Day &day)
{
  if(check(day))
  {
    days -= day; 
    count--;
  }
  return *this;
} // operator-=

bool Year::check(const Day &day)
{
  for (int i = 0; i < count; i++)
    if (days[i].compareDate(day.month, day.day) == 0)
      return true;
    cout << day.month << "/" << day.day << " not found." << endl << endl;
  return false;
}//check()

void Year::read()
{
  char s[256];
  int month, day;

  ifstream inf("appts.csv");
  inf.getline(s, 256); // eat titles.
  while(inf.getline(s, 256))
  {
    month = atoi(strtok(s,"/"));
    day = atoi(strtok(NULL,"/"));
    strtok(NULL, ","); // read through 2003

    int pos = findDate(month, day);

    if(pos == count)
    {
//        days += day;
//      addDate(month, day);
      Day newDay(month,day);
      days += newDay;
      count++;
      pos = findDate(month, day);
    } // if date not found

    days[pos].read();

  } // while more to read

  inf.close();
} // read()


void Year::searchDate(int month, int day) const
{

  bool found = false;

  for(int i = 0; i < count; i++)
    if(days[i].compareDate(month, day) == 0)
    {
      cout << "Start End   Subject         Location\n";
      days[i].printAppts();
      found = true;
      break;
    }  // if found a matching date

  if(!found)
    cout << "There are no appointments for that date.\n";

  cout << endl;
} // searchDate()


void Year::searchSubject(const char *s) const
{
  bool found = false;

  for(int i = 0; i < count; i++)
    days[i].printSubject(s, found);

  if(!found)
    cout << s << " was not found as a subject in the calendar.\n";

  cout << endl;
} // searchSubject()



