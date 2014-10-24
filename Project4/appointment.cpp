// Helen Chac

#include <cstring>
#include <iostream>
#include <iomanip>
#include "appointment.h"

using namespace std;

Appointment::Appointment() : subject(NULL), location(NULL)
{
}  // Appointment()

Appointment::Appointment(const char *s): location(NULL) 
{
  subject = new char[strlen(s)+1];
  strcpy(subject, s);
}

Appointment::~Appointment()
{
  if(subject)
    delete [] subject;

  if(location)
    delete [] location;
} // ~Appointment()


istream& operator>> (istream& is, Appointment &temp)
{

  char t_subject[100], t_location[100];

  cout << "Subject >> ";
  cin.getline(t_subject, 100);
  temp.subject = new char [strlen(t_subject)+1];
  strcpy(temp.subject, t_subject);
  cout << "Location >> ";
  cin.getline(t_location, 100);
  temp.location = new char[strlen(t_location)+1];
  strcpy(temp.location, t_location);
  while(1)
  {
    cout << "Start time >> ";
    is >> temp.startTime;
    cout << "End time >> ";
    is >> temp.endTime;
    if (temp.startTime < temp.endTime)
      break;
    cout <<"Start time is later than end time!" << endl;
  }
  return is;
}//>> operator

bool operator== (Appointment &tf, Appointment &s)
{
  if(strcmp(tf.subject, s.subject) == 0)
    return true;
  return false;
}//== operator

bool Appointment::compareSubject(const char *s) const
{
  return strcmp(subject, s) == 0;
}  // compareSubject()


void Appointment::read()
{
  char *ptr;

  ptr = strtok(NULL, ",");
  subject = new char[strlen(ptr) + 1];
  strcpy(subject, ptr);
  startTime.read();
  endTime.read();
  ptr = strtok(NULL, ",");
  location = new char[strlen(ptr) + 1];
  strcpy(location, ptr);
} // read()

ostream& operator<< (ostream& os, const Appointment &appointment)
{
  os << (appointment).startTime;
  os << (appointment).endTime;
  os << setw(15) << left << (appointment).subject << " " << (appointment).location << endl;
  return os;
}// << operator

Appointment& Appointment::operator= (const Appointment &rhs)
{
  if(this == &rhs)
    return *this;

  startTime = rhs.startTime;
  endTime = rhs.endTime;

  if(subject)
  {
    delete [] subject;
    subject = NULL;
  }  // if subject already set

  if(location)
  {
    delete [] location;
    location = NULL;
  } // if location already set

  if(rhs.subject)
  {
    subject = new char[strlen(rhs.subject) + 1];
    strcpy(subject, rhs.subject);
  }  // if rhs has a subject

  if(rhs.location)
  {
    location = new char[strlen(rhs.location) + 1];
    strcpy(location, rhs.location);
  } // if rhs has a location

  return *this;
} // operator=



