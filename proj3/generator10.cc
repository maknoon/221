#include <iostream>
#include <cstdlib> // for atoi

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) // remember, argv[0] is the program name
	{
		cerr << "Wrong number of arguments!" << endl;
		return 1;
	}
	
	int n = atoi(argv[1]);
	
	// inserts down to 1 from n/4 integers into struct
	for (int i = n/4; i >= 1; i--) {
		cout << "I " << i << endl;
	}
	
	// finds n/4 integers incrementing
	for (int i = 1; i <= n/4; i++) {
		cout << "F " << i << endl;
	}
	
	// finds n/8 bunch of times
	for (int i = 1; i <= n/4; i++) {
		cout << "F " << n/8 << endl;
	}
	
	// finds down to n/4 integers from struct
	for (int i = n/4; i >= 1; i--) {
		cout << "F " << i << endl;
	}
	
	return 0;
}