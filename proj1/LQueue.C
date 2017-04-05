/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

//--- Definition of size()
int Queue::size() const
{
   int size = 0;
   for (Queue::NodePointer ptr = myFront; ptr != 0; ptr = ptr->next) { size++; }
   
   return size;
}

//--- Definition of move_to_front()
void Queue::move_to_front(const QueueElement & value)
{
   // only do this if precondition is met
   if (!empty())
   {
      // if the value is already at the front of the Queue, do nothing
      if (myFront->data == value)
      {
#ifdef DEBUG
         cout << "*** Value is already at front ***\n";
#endif
	 return;
      }
      /* PROCEDURE
       * page thru the queue for the matching data
       * start at the second node because we already checked the front
       * but keep track of the node right before the current node w/ temp
       */
      Queue::NodePointer temp = myFront;
      for (Queue::NodePointer ptr = myFront->next; ptr != 0; ptr = ptr->next)
      {
	 // A::: we found the value
	 if (ptr->data == value)
	 {
#ifdef DEBUG
	    cout << "Found it! Moving to front.\n";
#endif
	    // (1) make new front node
	    Queue::NodePointer newptr = new Queue::Node(value);
	    newptr->next = myFront;
	    myFront = newptr;
	    // (2) delete the old node from queue
	    if (ptr == myBack) { // if we are at the back already
	       delete temp->next;
	       temp->next = NULL; // delete the old last element
	       myBack->next = temp;
	       myBack = temp; // chain myBack to the new last element
            } else {
	       delete temp->next; // delete the old value
	       temp->next = ptr->next; // chain to the next value in LQueue
            }
	    break;
	 }
	 // B::: if we didnt find value
	 else if (ptr == myBack)
	 {
            cout << "*** Value not in Queue ***\n";
	    break;
         }
	 // C::: increment temp as well
	 temp = temp->next;
      }
      cout << endl;
   }
   else cerr << "*** Queue is empty -- can't move to front ***\n";
}

//--- Definition of merge_two_queues()
void Queue::merge_two_queues(const Queue & queue2)
{
   // need both arrays to be non-empty
   Queue newQueue = queue2;
   if (newQueue.empty()) return;

   int temp = newQueue.front(); // always manipulate first value of q2
   newQueue.dequeue(); // always remove first value of q2
   
   // enqueue the value if it's definitely bigger
   if (myBack->data < temp) 
   {
      enqueue(temp);
      merge_two_queues(newQueue);
      
   } else {
   
      for (Queue::NodePointer ptr = myFront; ptr != 0; ptr = ptr->next)
      {
         if (temp > ptr->data && temp <= ptr->next->data)
         {
            // add queue2's first value to queue
            Queue::NodePointer newptr = new Queue::Node(temp);
            newptr->next = ptr->next;
            ptr->next = newptr;
            merge_two_queues(newQueue);	 
         }
      }
   }
}
