#include <iostream>

/* global defines */
#define ARRAYSIZE 10

/* function prototypes */
//void fill_array(); // part (a)
void fill_array(int first_value, int increment); // part (b)

/* global variables */
int array[ARRAYSIZE];

int main(void) {
  // collect first value & increment
  int first_value, increment;
  std::cout << "Enter first value:" << std::endl;
  std::cin >> first_value;
  std::cout << "Enter increment:" << std::endl;
  std::cin >> increment;
  
  // fill array according to the collected numbers
  fill_array(first_value, increment);

  // print out contents of the array
  std::cout << "Contents of array:" << std::endl;
  for (int i = 0; i < ARRAYSIZE; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
  
  // exit
  return 0;
}

/* fill an array with ten elements specified by the parameters */
void fill_array(int first_value, int increment) {
  for (int i = 0; i < ARRAYSIZE; i++) {
    array[i] = first_value + increment*i;
  }
}
