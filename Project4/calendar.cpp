// Helen Chac

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "year.h"

using namespace std;

int getChoice()
{
  int choice;
  char s[80];

  do
  {
    cout << "Calendar Menu\n0. Done.\n1. Search for date.\n";
    cout << "2. Search for subject.\n3. Add an appointment.\n";
    cout << "Your choice >> ";
    cin >> choice;

    if(choice < 0 || choice > 3)
      cout << "\nChoice must be between 0 and 3.\nPlease try again.\n\n";
  } while(choice < 0 || choice > 3);

  cin.getline(s, 80);
  return choice; // eat end of line
} // getChoice()


void getDate(short &month, short &day)
{
  char s[80], s2[80], *ptr;

  month = 0;

  do
  {
    cout << "\nPlease enter the month and day (mm/dd) >> ";
    cin.getline(s, 80);
    strcpy(s2, s);
    ptr = strtok(s2,"/");

    if(ptr)
    {
      month = atoi(ptr);
      ptr = strtok(NULL, ",");
      if(ptr)
        day = atoi(ptr);
    }

    if(month < 1 || month > 12 || day < 1 || day > 31)
      cout << s << " is not a valid date.\nPlease try again.\n\n";
  } while(month < 1 || month > 12 || day < 1 || day > 31);
} //getDate()


void getSubject(char *s)
{
  cout << "\nPlease enter the subject >> ";
  cin.getline(s, 80);
} // getSubject()
void addAppointment(Year &year, const short month, const short day)
{
  Day nday(month, day);
  cin >> nday;
  year += nday;// add appointment to the day
}//addAppointment()


int main()
{
  Year year;
  int choice;
  short month, day;
  char s[80];
  year.read();
  choice = getChoice();

  while(choice != 0)
  {
    switch (choice)
    {
      case 1: 
      {
        getDate(month, day);
        year.searchDate(month, day);
        break;
      }
      case 2:
      {
        getSubject(s);
        year.searchSubject(s);
        break;
      }
      case 3:
      {
        getDate(month, day);
        addAppointment(year, month, day);
        break;
      }
    }
    choice = getChoice();
  } // while choice not Done

  return 0;
} // main()

