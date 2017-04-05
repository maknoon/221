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
	
	// inserts up to n/2 integers into struct
	for (int i = 1; i <= n/2; i++) {
		cout << "I " << i << endl;
	}
	
	// removes up to n/2 integers from struct
	for (int i = 1; i <= n/2; i++) {
		cout << "R " << i << endl;
	}
	
	return 0;
}