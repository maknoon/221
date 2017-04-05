// linked_list.cc -- functions for linked_list lab (cs221) 

#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: newKey is the value for the key in the new Node 
 * POST: the new Node is now the head of the linked_list
 */ 
void insert(Node*& head, int newKey) {
  Node * curr = new Node;
  curr->key  = newKey;
  curr->next = head;

  head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
void print(Node* head) {
  std::cout << "[";
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    std::cout << curr->key;
    if (curr->next != NULL) std::cout << ", ";
  }
  std::cout << "]" << std::endl;
}

/** 
 * Returns the size (number of Nodes) of the linked_list  
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 */ 
int size(Node* head){ 
  if (! head) return 0; 
  return 1 + size(head->next); 
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * POST: a new vector<int> containing the keys in the correct order has been returned.  
 */ 
std::vector<int> to_vector(Node* head) {
  std::vector<int> result;
  for (Node* curr = head; curr != NULL; curr = curr->next){ 
    result.push_back(curr->key); 
  }
  return result; 
}

/** 
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node*& head) {
  // if the linked list is empty
  if (!head) return;
  // if the first element is the last element in the LL, just delete it
  if (head->next == NULL) {
    /*
     * ok i have a question about this; code segfaults when i leave
     * this p.o.s. line uncommented & i have no idea why
     */
#ifdef RECURSIVE
    delete head;
#endif
    head = NULL;
  } else {
    // navigate to the end of the linked list by invoking curr->next
    Node* temp = head; //<-- doesnt really matter what temp begins w/
    for (Node* curr = head; curr->next != NULL; curr = curr->next) {
      temp = curr;
    }
    // delete element at end of LL & free the memory
    delete temp->next;
    temp->next = NULL;
  }
}

/**
 * Removes an existing Node (with key=oldKey) from the linked_list. 
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value of the key in the Node to be removed 
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed 
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */ 
void remove(Node*& head, int oldKey) {
  // if the linked list is empty
  if (!head) return;
  // if the first element is the last element in the LL
  if (head->next == NULL || head->key == oldKey) {
      delete head;
      head = head->next;
  } else {
    // navigate thru LL, checking for the key we want
    // we are only looking for the first occurrence of oldKey
    Node* temp = head; //<-- init doesnt matter
    Node* save = head->next; //<-- we need this to save the link
    for (Node* curr = head; curr->key != oldKey; curr = curr->next) {
      temp = curr;
      save = save->next;
    }
    // remove the offending node and re-link to next element in LL we saved
    delete temp->next;
    temp->next = save;
  }
}

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty) 
 * PRE: oldKey is the value to look for (in the key of an existing Node)  
 * PRE: newKey is the value of the key in the new Node (that might be inserted) 
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node* head, int oldKey, int newKey){
  // if the linked list is empty
  if (! head) return;
  // if the first key in the LL matches oldKey
  if (head->key == oldKey) insert(head->next, newKey);
  else {
    Node* temp;
    for (Node* curr = head; curr->key != oldKey; curr = curr->next) {
      temp = curr;
      // if we're at the end of the LL and we still didnt find oldKey
      if (curr->next == NULL) break;
    }
    // insert only if we found the oldKey; otherwise leave LL unchanged
    if (temp->next != NULL) insert(temp->next->next, newKey);
  }
}

/** 
 * Create a new linked_list by merging two existing linked_lists. 
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from 
 * the Nodes in list1 and list2, starting with the key of the first Node of list1, 
 * then the key of the first Node of list2, etc. 
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
#ifdef RECURSIVE
// ------------ RECURSIVE VERSION
Node* interleave(Node* list1, Node* list2){
  // create new nodes to link in the old ones
  Node* temp1 = list1;
  Node* temp2 = list2;
  Node* head = new Node; // head node we are building the interleaved LL from
  
  /* 
   * if either linked lists are empty, keep adding the next element
   * of the non-empty list into the LL
   */
  if (list1 && !list2) {
    // insert the next value of list1 into the interleaved LL
    head->key = temp1->key;
    head->next = interleave(temp1->next, NULL);
  }
  else if (!list1 && list2) {
    // insert the next value of list2 into the interleaved LL
    head->key = temp2->key;
    head->next = interleave(NULL, temp2->next);
  }
  // if both lists are empty
  else if (!list1 && !list2) return NULL;
  
  // both lists not empty, so need to insert extra node in between old one
  else {
    Node* insert = new Node;
    // the first value from list1
    head->key = temp1->key;
    head->next = insert;
    // the second value from list2
    insert->key = temp2->key;
    insert->next = interleave(temp1->next, temp2->next);
  }
    
  return head;
}
#endif

#ifdef ITERATIVE
// ------------ INTERATIVE VERSION
Node* interleave(Node* list1, Node* list2){
  Node * newlist1 = NULL;

  // if either linked lists are empty  
  if (list1 && ! list2) newlist1 = list1;
  else if (! list1 && list2) newlist1 = list2;
  else if (! list1 && ! list2) newlist1 = NULL;
  else {
    // since we need to save the list1&2 to be used later, gotta build 2 new LLs
    Node * newlist2 = NULL;
    insert(newlist1, list1->key);
    insert(newlist2, list2->key);
    for (Node* curr = list1; curr->next != NULL; curr = curr->next) {
      insert_after(newlist1, curr->key, curr->next->key);
    }
    for (Node* curr = list2; curr->next != NULL; curr = curr->next) {
      insert_after(newlist2, curr->key, curr->next->key);
    }
  
    // building the list iterativel...y.. this code sucks lmao

    // (1) insert the first element in list2 behind our position in list1
    // (2) then remove the first element of list2 and move to next element
    // (3) if we've exhausted the elements in list one, we insert differently
    Node* curr = newlist1;
    Node* temp = newlist2;
    int size1 = size(newlist1); // iterate according to size

    for (int i = 0; i < size1; i++) {
      insert_after(curr, curr->key, temp->key); // (1)
      remove(newlist2, temp->key); // (2)
      temp = temp->next;
      curr = curr->next->next;
    }

    // (4) insert remaining elements of list2 one after the other into list1
    // (5) make sure to delete the element inserted
    int lastKey;
    temp = newlist2;
    while (temp != NULL) {
      for (Node* curr = newlist1; curr != NULL; curr = curr->next) lastKey = curr->key;
      insert_after(newlist1, lastKey, temp->key); // (4)
      remove(newlist2, temp->key); // (5)
      temp = temp->next;
    }
  }
  
  return newlist1;
}
#endif
