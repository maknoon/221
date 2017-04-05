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
	
	// insert up to 25%
	for (int i = 1; i <= n/4; i++) {
		std::cout << "I " << i << std::endl;
	}

	// splay & mtf should be faster
	for (int i = 1; i <= n/4; i++) {
		std::cout << "F " << n/8 << std::endl;
	}

	// find 25%
	for (int i = 1; i <= n/4; i++) {
		std::cout << "F " << i << std::endl;
	}

	// splay & mtf should be faster
	for (int i = 1; i <= n/4; i++) {
		std::cout << "F " << n/8-1 << std::endl;
	}
	
	return 0;
}