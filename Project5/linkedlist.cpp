// Helen Chac && Gabriel Chan

#include <cstdlib>
#include "linkedlist.h"

ListNode::ListNode(const Day &d, ListNode *n)
{
//  day = new Day;
  day = d;
//  n.day = day;
//  next = new ListNode;
  next = n;
} // constructor;

LinkedList::LinkedList():head(NULL)
{
} // constructor 

LinkedList::~LinkedList()
{
} // destructor

const Day& LinkedList::operator[](int index)const
{
  ListNode *ptr = head;
  for(int i = 0; i < index; i++)
    ptr = ptr->next;
  return ptr->day;
} // operator [] const 

Day& LinkedList::operator[] (int index)
{
  ListNode *ptr = head; 
  for(int i = 0; i < index; i++)
    ptr = ptr->next;

  return ptr->day;
} // operator[] 

LinkedList& LinkedList::operator+= (const Day &d)
{
  ListNode *ptr, *prev = NULL;
  ListNode *node;




  for (ptr = head; ptr && (ptr->day < d); ptr = ptr->next)
    prev = ptr;

  node = new ListNode(d, ptr);
  node->day = d;

  if (prev)
    prev->next = node;

  else
    head = node;
//  cout << head << endl;
//  cout << head->day.month << " " << head->day.day << endl;
  return *this;
}// operator += const

LinkedList& LinkedList::operator-= (const Day &d)
{
  ListNode *ptr, *prev = NULL;

  if (!head)
    return *this;
  if (head->day == d)
  {
    ptr = head->next;
    delete head;
    head = ptr;
  }
  else
  {
  for (ptr = head; ptr; ptr = ptr->next)
  {
    if (ptr->day == d)
    {
      prev = ptr;
      break;
    }
  }
    if (prev)
      prev->next = ptr->next;
    else
      head = ptr->next;
    delete ptr;
  }
  return *this;
} // operator -=const  
