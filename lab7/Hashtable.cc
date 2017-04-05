#include "Hashtable.h"
#include <cstdlib>
#include <iostream>
#include <cassert> 

using namespace std; 

Hashtable::Hashtable(int size) {
	//constructor
	int prime = nextPrime( size ); 
	_size = size;
	if (prime != size) { 
#ifdef ANNOYING
	  cout << "Warning: size = " << size << " is not a prime number." << endl; 
	  cout << "Using " << prime << " instead." << endl; 
	  _size = prime;
#endif
	}
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	_table = new int [ _size ];
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}
void Hashtable::clear(void) {
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	for (int ii=0; ii < _size; ii++) {
		_table[ ii ] = EMPTY;
	}
}    
    

Hashtable::~Hashtable() {
	//deconstructor
	delete[] _table;
}

void Hashtable::tallyProbes(int p) {
	// Add the number of probes, p, for one insert operation to the tally.
	_totalProbes += p;
	_numInserts += 1;
}

void Hashtable::printStats() {
	cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			_totalProbes << "/" << _numInserts;
	cout <<", size = "<< _size;
	cout <<", failures = " << _numFailures << endl;
}

float Hashtable::probeRate() {
	return (float)_totalProbes / (float)_numInserts;
}

int Hashtable::hash(int k) {
	return k % _size;
}

void Hashtable::qinsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with quadratic probing and hash(k) = k % _size.

    // Quadratic probing :: h(k, i) = (hash(k) + i^2) mod m
    // -> *(_table + (hash_k + i*i) % _size)
    int hash_k = hash(k);
    int j = hash_k;
    
    // iterate thru table; stop at _size to prevent infinite looping
    for (int i = 0; i < _size; i++) {
	// if the slot is empty, insert it
	if (*(_table + j) == EMPTY) { 
	    *(_table + j) = k;
	    tallyProbes(i + 1); // statistic
	    return;

        } else {
            // recompute position in table
	    j = (hash_k + i*i) % _size;
        }
    }
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1;
#ifdef ANNOYING
     cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;
#endif
}

void Hashtable::linsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with linear probing and hash(k) = k % _size.

    // Linear probing :: h(k, i) = (hash(k) + i) mod m
    // -> *(_table + (hash_k + i) % _size)
    int hash_k = hash(k);
    
    // iterate thru table; stop at _size to prevent infinite looping
    for (int i = 0; i < _size; i++) {
	// if the slot is empty, insert it
	if (*(_table + (hash_k + i) % _size) == EMPTY) { 
	    *(_table + (hash_k + i) % _size) = k;
	    tallyProbes(i + 1); // statistic
	    return;
	}
	
    }
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1;
#ifdef ANNOYING
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;
#endif
}

void Hashtable::dinsert(int k) {
    // Insert k in the hash table.
    // Use open addressing with double hashing. Use the existing hash function
    // and also implement a second hash function.
    
    // Double hashing: h(k, i) = (hash(k) + i · hash2(k)) mod m
    // where hash2(k) = r − (k mod r)
    // -> *(table + (hash_k + i + hash2(k)) % _size)
    // -> hash2(k) = _size - hash(k)
    int hash_k = hash(k);
    int hash2_k = _size - hash_k; // _size should be prime
    
    // iterate thru table; stop at _size to prevent infinite looping
    for (int i = 0; i < _size; i++) {
        // if the slot is empty, insert it
	if (*(_table + hash_k) == EMPTY) { 
	    *(_table + hash_k) = k;
	    tallyProbes(i + 1); // statistic
	    return;

	} else {
	    // recompute position in table by hash2_k
	    hash_k = (hash_k + hash2_k) % _size;
	}
    }
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
#ifdef ANNOYING
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl;
#endif
}

void Hashtable::print() {
	// Print the content of the hash table.

	for (int i=0; i<_size; i++) {
		cout<<"["<<i<<"] ";
		if (_table[i] != EMPTY)
			cout << _table[i];
		cout << endl;
	}
}

bool Hashtable::checkValue(int k, int i) {
	// Check if value k is at index i. Use this to help you with testing.

	return (_table[i] == k);
}

int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if (n == 2) return true;
    if (n % 2 == 0) return false;  
    return isPrime( n, 3 ); 
}
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    return isPrime( n, divisor + 2 ); 
}

