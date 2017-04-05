#include <iostream>
#include <cstdlib>

using namespace std;

int main () {
  int x = 5, y = 15;
  int * p1, *p2;
		// value of	x	y	p1	p2
		//		5	15	uninit	uninit
  p1 = &x;
                //		5	15	addr(x)	uninit
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  p2 = &y;
                //		5	15	addr(x)	addr(y)
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  *p1 = 6;
                //		6	15	addr(x)	addr(y)
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  *p1 = *p2;
                //		15	15	addr(x) addr(y)
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  p2 = p1;
                //		15	15	addr(x)	addr(x)
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  *p1 = *p2+10;
                //		25	15	addr(x)	addr(x)
  cout << x << " ";
  cout << y << " ";
  cout << p1 << " ";
  cout << p2 << endl;
  
  return 0;
}
