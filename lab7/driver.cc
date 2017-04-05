#include "Hashtable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void usage(char* argv[]) {
	cerr << "Usage: " << argv[0] << " scheme numberOfKeys sizeOfTable" << endl;
	exit(-1);
}

int main(int argc, char *argv[]) {
	int n, m;
	srand(time(0));

	if (argc == 1) {
		//cout << "Running your test code..." << endl;
		
		/* GENERAL PROBE TESTS */
		cout << endl << "/////// GENERAL PROBE TESTS ---" << endl;
		for (int i = 1; i < MAXTABLESIZE; i += INC) {
			// create Hashtable of size i
			cout << "**** _size: " << i << " ****" << endl;
			Hashtable L(i); Hashtable Q(i); Hashtable D(i);
			Hashtable _L(i); Hashtable _Q(i); Hashtable _D(i);
			
			// insert some stuff into the table
			for (int j = 0; j < i+INC; j++) {
				L.linsert(rand() + 1);
				Q.qinsert(rand() + 1);
				D.dinsert(rand() + 1);
			}
			
			// print stats
			cout << "**** # keys: " << i+INC << " ****" << endl;
			cout << "Linear: "; L.printStats();
			cout << "Quadratic: "; Q.printStats();
			cout << "Double: "; D.printStats();
			
			// insert some stuff into the table
			for (int k = 0; k < i-INC; k++) {
				_L.linsert(rand() + 1);
				_Q.qinsert(rand() + 1);
				_D.dinsert(rand() + 1);
			}
			
			// print stats
			cout << "**** # keys: " << i-INC << " ****" << endl;
			cout << "Linear: "; _L.printStats();
			cout << "Quadratic: "; _Q.printStats();
			cout << "Double: "; _D.printStats();
		}
		
		/* PRIME SIZE PROBE TEST */
		cout << endl << "/////// PRIME SIZE PROBE TEST ---" << endl;
		cout << "**** _size: " << BIGPRIME << " ****" << endl;
		Hashtable PL(BIGPRIME); Hashtable PQ(BIGPRIME); Hashtable PD(BIGPRIME);
		
		// insert some stuff into the table
		for (int p = 0; p < BIGPRIME; p++) {
			PL.linsert(rand() + 1);
			PQ.qinsert(rand() + 1);
			PD.dinsert(rand() + 1);
		}
		
		// print stats
		cout << "**** # keys: " << BIGPRIME << " ****" << endl;
		cout << "Linear: "; PL.printStats();
		cout << "Quadratic: "; PQ.printStats();
		cout << "Double: "; PD.printStats();

		return 0;
	}
	
	if (argc != 4) {
		usage(argv);
	}
	n = atoi(argv[2]);
	m = atoi(argv[3]);
	Hashtable H(m);
	
	switch(argv[1][0]) {
	case 'l':
		for (int i=0; i<n; ++i) {
			H.linsert(rand() + 1);
		}
		//H.print();
		cout << "Linear: ";  
		H.printStats();
		break;
	case 'q':
		for (int i=0; i<n; ++i) {
			H.qinsert(rand() + 1);
		}
		//H.print();
		cout << "Quadratic: ";
		H.printStats();
		break;
	case 'd':
		for (int i=0; i<n; ++i) {
			H.dinsert(rand() + 1);
		}
		//    H.print();
		cout << "Double Hashing: "; 
		H.printStats();
		break;
	default:
		usage(argv);
	}
}

/*
 * QUESTIONS
 *
 * Ran some tests w/ load 100000, 10000, 9973 (largest prime < 10000).
 * Also referenced:
 * https://cathyatseneca.gitbooks.io/data-structures-and-algorithms/tables/quadratic_probing_and_double_hashing.html
 *
 * 1. L & Q probing are about same when table is empty but L will begin
 *    to cluster when table starts to fill up; Q will win out at that point.
 *    Also for large non-prime table sizes, Q won't probe successfully.
 *
 * 2. Choice of hash2 affects avg probing per insertion and if it will form 
 *    either primary/secondary clustering. You can find hash2 to make probe rate
 *    better than quadratic but you may have higher failures as a result. Also
 *    should never choose hash2 s.t. it hashes to 0 cuz then hash will die.
 *
 * 3. Double hashing wins against L starts to cluster, wins against Q when
 *    number of keys >= _size * 0.5, for non-prime _size.
 *
 * 4. I would choose double hashing since it doesn't have the clustering issues
 *    you see in L & Q probing, given most generic preconditions. For situations
 *    that may involve complex hash functions (i.e., cryptography or w/e) I would
 *    consider using quadratic probing instead to reduce overhead.
 *
 */

