/*--- max_heap.cpp -----------------------------------------------
  This file implements hax_heap.hpp member functions.
-------------------------------------------------------------------------*/

#include "max_heap.hpp"
#include <stdexcept>

using namespace std;

max_heap::max_heap(int n){
	data = new text_item[n];
	numItems = 0;
	max_capacity = n;
}

max_heap::~max_heap()
{ 
	delete [] data;
}

bool max_heap::empty() const {
	return (numItems == 0);
}

bool max_heap::full() const {
	return (numItems == max_capacity);
}

int max_heap::size() const {
	return numItems;
}	

text_item& max_heap::top() {
	if (empty()) {
		throw std::logic_error("Heap is empty, can't access top!");
	}
	return data[0];
}


//--- You must complete the following functions: 


text_item max_heap::delete_max() {
	if (empty()) {
		throw std::logic_error("Cannot delete, heap is empty!");
	} else {
		// remove max from top of the heap
		text_item popped = data[0];
		data[0] = data[numItems-1];
		numItems--;
		
		// swap the bottom value according to max heap invariant
		swap_down(0);
		
		return popped;
	}
}

void max_heap::swap_down(int i) {
	// base case; we have reached the end of the array
	if (i == numItems) return;
	
	// otherwise compare and swap with left/right child if necessary
	int swap = i;
	int left = (i*2)+1;
	int right = (i*2)+2;

	// figure out first which freq is bigger, left or right
	if (left < numItems && data[swap].freq < data[left].freq) swap = left;
	if (right < numItems && data[swap].freq < data[right].freq) swap = right;
	
	// swap with the bigger child (if applicable)
	if (swap == i) return;
	else {
		text_item temp = data[i];
		data[i] = data[swap];
		data[swap] = temp;
		
		// keep going down the heap
		swap_down(swap);
	}

}

void max_heap::insert(const text_item & item) {
	if (full()) {
		throw std::logic_error("Cannot insert, heap array is full!");
	} else {
		// add the text_item to the heap
		int node = numItems;
		data[node] = item;
		numItems++;
		
		// apply heapify for max heap invariant
		swap_up(node);
	}
}

void max_heap::swap_up(int i) {
	// base case
	if (i == 0) return;

	// otherwise compare w/ parent and swap if necessary
	int parent = (i-1)/2;
	if (data[i].freq >= data[parent].freq) {
		text_item temp = data[i];
		data[i] = data[parent];
		data[parent] = temp;

		// keep going up the heap
		swap_up(parent);
	}
}

void max_heap::print() {
	for (int i = 0; i < numItems; i++) {
		cout << "node: " << i << " ";
		cout << "word: " << data[i].word << " ";
		cout << "freq: " << data[i].freq << endl;
	}	 
}

void max_heap::bin_print(int node, int d) {
	if (node >= numItems) return; // base case
	if (node == 0) {
		bin_print(node+2, d+1); // right child branch
		cout << data[node] << endl; // node
		bin_print(node+1, d+1); // left branch
	} else {
		bin_print(2*node+2, d+1); // right child branch
		for (int i = 0; i < d; i++) cout << "  "; // depth
		cout << data[node] << endl; // node value
		bin_print(2*node+1, d+1); // left child branch
	}
}
