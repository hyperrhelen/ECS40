// Helen Chac

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "time.h"

using namespace std;


void Time::read()
{
  hour = atoi(strtok(NULL, ":"));
  minute = atoi(strtok(NULL, ":"));
  char *ptr = strtok(NULL, ",");

  if(strchr(ptr, 'P') && hour != 12)
    hour += 12;
} // read()

ostream& operator<< (ostream& os, const Time &time)
{
  os << setw(2) << setfill('0') << right << time.hour << ":" << setw(2) << 
    time.minute << " " << setfill(' ');
  return os;
}//ostream()

istream& operator>> (istream& is, Time &temp)
{
  char line[80], *ptr;
  short hour, minute;
  cin.getline(line, 80);
  do
  {
    if ((ptr = strchr(line, ' '))==NULL)
    cout << "Your time is invalid." << endl << "Format of time is hh:mm PM or hh:mm AM." << endl;
    else
    {
    ptr = strtok(line, "\t:");
    hour = atoi(ptr);
    if (hour < 0 || hour > 12)
      cout << "Hour must be between 1 and 12." << endl << "Format of time is hh:mm PM or hh:mm AM." << endl;
    else
    {
      ptr = strtok(NULL, " \t");
      minute = atoi(ptr);
      if (minute < 0 || minute > 59 || line [2] == ' ' || line[3] == ' ' ||line[4] == ' '|| ptr[0] == ' ' || ptr [1] == ' ' )
        cout << "Minutes must be between 00 and 59" << endl << "Format of time is hh:mm PM or hh:mm AM."<< endl;
      else
      {
        ptr = strtok(NULL, "\n");
        temp.minute = minute;
        if (strchr(ptr, 'P') && temp.hour != 12)
        {
          temp.hour = hour + 12;
          break;
        }//if
        else if (strchr(ptr, 'A'))
        {
          temp.hour = hour;
          break;
        }//elseif
        else
          cout << "The AM/PM is invalid." << endl << "Format of time is hh:mm PM or hh:mm AM." << endl;
      }//else
    }//else()
    }//if
  cout << "\nTime >> ";
  cin.getline(line,80);
  }while(true);
  return is;
}//istream


bool operator< (Time &start, Time &end)
{
  int t_start = start.hour * 60 + start.minute;
  int t_end = end.hour * 60 + end.minute;
  if (t_start < t_end)
    return true;
  return false;
}

