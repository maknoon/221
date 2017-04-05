#include <cstdlib> // for atoi
#include <iostream>
// prototype
void moveDisks(int n, const char* FROM, const char* VIA, const char* TO);
#define STRING1	"Move disk from "

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " number_of_disks" << std::endl;
    return -1;
  }
  int n = atoi(argv[1]);
  moveDisks(n, "peg A", "peg B", "peg C");
  return 0;
}

// put your moveDisks() function here 
void moveDisks(int n, const char* FROM, const char* VIA, const char* TO) {
  // base case
  // when there is 1 disk, just move it from A to C
  if (n == 1) {
    std::cout << STRING1 << FROM << " to " << TO << std::endl;
  } else {
    // if there is >1 disk we want to move it out of the way
    // accomplish this by following the steps described in lab1
    
    // (1) move n - 1 disks from A to B recursively 
    moveDisks(n - 1, FROM, TO, VIA);
    // (2) move nth disk from A to C (bottom of new tower)
    std::cout << STRING1 << FROM << " to " << TO << std::endl;
    // (3) move n - 1 disks from B to C recursively 
    moveDisks(n - 1, VIA, FROM, TO);
  }
}
