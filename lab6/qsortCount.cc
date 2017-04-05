#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//#define ANNOYING
//#define Q2
//#define Q3

int * x;
long comps = 0;

void swap(int & a, int & b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int randint(int a, int b) {
	return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
	if (a >= b) return;
	int p = randint(a,b); // pivot
	swap(x[a], x[p]);
	int m = a;
	int i;
	// in-place partition:
	for (i = a+1; i <= b; i++) {
		if (x[i] < x[a])
			swap(x[++m], x[i]);
		comps++;
	}
	swap(x[a],x[m]);
	quicksort(a, m-1);
	quicksort(m+1, b);
}

#define NN 1000
#define RE 100

/* Q2
 * stats: NN - avg comps
 *	  2000 - 1912869
 *	  1000 - 457746
 *	  500 - 104491
 *	  100 - 2569
 */
int calc_avg(int reps) {	

	x = new int[NN];
	for (int i = 0; i < reps; i++) {
		srand(time(0));
		for (int j=0; j<NN; ++j) {
			x[i] = rand() % NN;
		}
		quicksort(0, NN-1);
	}
	delete[] x;

	return comps / reps;
}

/* Q3 */
 int qc (int num) {
	 // base cases
	 if (num <= 1) return 0;
	 else if (num == 2) return 1;
	 
	 // values to use for next recurse
	 srand(time(0));
	 int next = num - 1; // decrement array size
	 int p = randint(0, next); // pivot

	 // add left and right together
	 next += qc(p) + qc(next - p);
	 
	 return next;
 }
 
 /* Q4
  * C(n) = (1/n) SUMM(m=1 to n) [(n-1) + C(m-1) + C(n-m)]
  
  * Q5
  * A) avg case = theta(nlogn)
  * B) worse case = O(n^2)
  * -> Not likely to see O(n^2) cuz we aren't going by pivots in order. It's
  *    done randomly so chances are low of picking smallest / largest value
  *    every single time we invoke quicksort.
  * -> Done in-place bc we just swap existing values; no other significant
  *    pieces of memory space used besides array & small static variables.
  * -> Not stable bc the swaps are randomly selected so order is not traced.
  
  * Q6 -- too busy this week do the DP later
  */


int main(int argc, char *argv[]) {

#ifdef ANNOYING
	for (int i=0; i<NN; ++i) {
		std::cout << x[i] << " ";
	}
#endif
#ifdef Q2
	int average = calc_avg(RE);
	cout << "num comps: " << comps << endl;
	cout << "avg comps: " << average << endl;
#endif
#ifdef Q3
	comps += qc(NN);
	cout << "comps: " << comps << endl;
#endif
	
	return 0;
}

