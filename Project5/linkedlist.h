// Helen Chac && Gabriel Chan

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "day.h"

class ListNode
{
  ListNode(const Day &d, ListNode *n);
  Day day;
  ListNode *next;
  friend class LinkedList;
}; // class ListNode

class LinkedList
{
private:
  ListNode *head;
public:
  LinkedList();
  ~LinkedList();
  const Day& operator[](int index) const;
  Day& operator[](int index);
  LinkedList& operator+= (const Day &d);
  LinkedList& operator-= (const Day &d);
};
#endif
