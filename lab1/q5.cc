#include <cstdlib> // for atoi, rand, srand
#include <iostream>

/* function prototypes */
void make_guess();

int main(int argc, char *argv[]) {
  std::cout << "Enter 0 to quit at any time" << std::endl;
  make_guess();
  return 0;
}

/* prompt for guess from user */
void make_guess() {
  // prompt user for an inputted guess
  std::cout << "Make a guess between 1 to 100:" << std::endl;
  int guess;
  int random = rand() % 100;
  std::cin >> guess;
  
  // if the user wants to quit, return
  if (guess == 0) {
    std::cout << "Exiting program" << std::endl;
    return;

  // if guess is correct, return
  } else if (guess == random) {
    std::cout << "Correct! Exiting program" << std::endl;
    return;

  // if guess is incorrect, prompt user again
  } else {
    std::cout << "Incorrect! Try again" << std::endl;
    make_guess();
  }
}
