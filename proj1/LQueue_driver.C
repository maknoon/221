/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
using namespace std;
	
void print(Queue q)
{ q.display(cout); }

int main(void)
{
   Queue q1;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;

   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2); 
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;

   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();
   
   /* TESTING move_to_front */
   Queue q3;
   cout << "How many elements to add to the new queue? ";
   cin >> numItems;
   for (int i = 1; i <= numItems; i++)
      q3.enqueue(10*i);

   cout << "Contents of queue q3 (via  print):\n";
   print(q3);
   cout << endl;

   while (!q3.empty())
   {
      cout << "Element to move to front of queue? ";
      int inputKey;
      cin >> inputKey;
      q3.move_to_front(inputKey);
      cout << "New queue after move_to_front: ";
      q3.display(cout);
      q3.dequeue();
      cout << "New queue after dequeue: ";
      q3.display(cout);
   }
   
   cout << "Queue q3 empty? " << q3.empty() << endl;
   cout << "Front value in q3?" << endl << q3.front() << endl;
   cout << "Trying to remove front of q3: " << endl;
   q3.dequeue();
   
   /* TESTING merge_two_queues */
   Queue q4, q5;
   cout << "How many elements to add to the new queues? ";
   cin >> numItems;
   for (int i = 1; i <= numItems; i++)
   {
      q4.enqueue(2*i);
      q5.enqueue(3*i);
   }
   
   cout << "Contents of queue q4, q5 before merge (via print):\n";
   print(q4); print(q5); cout << endl;
   q4.merge_two_queues(q5);

   while (!q5.empty()) q5.dequeue();
   cout << "Contents of queue q4, q5 after merge (via print):\n";
   print(q4); print(q5); cout << endl;
   while (!q4.empty()) q4.dequeue();

   cout << "Queue q4 empty? " << q4.empty() << endl;
   cout << "Front value in q4?" << endl << q4.front() << endl;
   cout << "Trying to remove front of q4: " << endl;
   q4.dequeue();
   cout << "Queue q5 empty? " << q5.empty() << endl;
   cout << "Front value in q5?" << endl << q5.front() << endl;
   cout << "Trying to remove front of q5: " << endl;
   q5.dequeue();
   
   //system("PAUSE");
   return 0;
}
