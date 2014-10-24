// Helen Chac

#ifndef timeH
#define timeH
#include <iostream>
using namespace std;
class Time
{
private:
  short hour;
  short minute;
  friend istream& operator>>(istream& is, Time &time);
  friend ostream& operator<< (ostream& os, const Time &time);
  friend bool operator< (Time &start, Time &end);
public:
  void read();
}; // class Time
#endif
