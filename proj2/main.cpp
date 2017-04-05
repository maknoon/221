#include <iostream>
#include <cassert>

#include "string_bst.hpp"
#include "max_heap.hpp"
#include "text_item.hpp"
#include "util.hpp"

using namespace std;

//#define DEBUG

//--- PART 1A: Implementation and testing of heap insert
void heap_insert_tests(max_heap &hp) {
	string word = "item";
	int random_num;
	long int seed = long(time(0));    // seed for random number generator
	srand(seed);
	
	//--- Testing insert functionality
	cout << "*** TESTING INSERT ***" << endl;

	//--- This adds 5 items to the heap with random numbers
	//    and prints out the top, but it does not fully 
	//    test the correctness of the insert function.
	cout << endl << "@TEST: generic test" << endl;
	for (int i = 0 ; i < 5; i++) {
		random_num = rand() % 100;
		string text = word;
		text += std::to_string(i+1);
		cout << "adding " << text << ",  with number " << random_num << " to heap" << endl;
		hp.insert(text_item{text, random_num});	
		#ifdef DEBUG
		cout << "Top of heap is: " << hp.top() << endl;
		#endif
	}
	text_item top = hp.top();
	cout << "Top of heap is: " << top << endl; cout << endl;
	
	//--- Specific insert functionality that should be tested:
	
	// @TEST: insert without any swap_ups needed
	cout << "@TEST: insert without any swap_ups needed" << endl;
	string word1 = "nswap";
	int ordered = 5;
	for (int i = ordered; i > 0; i--) {
		string text = word1;
		text += std::to_string(i);
		cout << "adding " << text;
		cout << ", with number " << ordered*i << " to heap" << endl;
		hp.insert(text_item{text, ordered*i});
		
		// test for top
		top = (top.freq >= 25) ? top : hp.top();
		assert(hp.top() == top);
		#ifdef DEBUG
		cout << "Top of heap is: " << hp.top() << endl;
		#endif
	}
	cout << "Top of heap is: " << top << endl; cout << endl;
		
	// @TEST: insert with a swap_up / multiple swap_ups
	cout << "@TEST: insert with a swap_up / multiple swap_ups" << endl;
	string word2 = "yswap";
	int chaotic;
	for (int i = 0; i < 5; i++) {
		chaotic = (i % 2 == 1) ? 1000*i : i;
		string text = word2;
		text += std::to_string(i+1);
		cout << "adding " << text;
		cout << ", with number " << chaotic << " to heap" << endl;
		hp.insert(text_item{text, chaotic});
		#ifdef DEBUG
		cout << "Top of heap is: " << hp.top() << endl;
		#endif
	}
	assert(hp.top().freq == 3000);
	cout << "Top of heap is: " << hp.top() << endl; cout << endl;
	
	// @TEST: insert into full heap - will throw exception
	//hp.insert(text_item{"yswap1",5});
	
	// clean heap
	while (hp.size() > 0) hp.delete_max();
}

//--- PART 1B: Implementation and testing of heap delete
void heap_delete_tests(max_heap &hp) {
	text_item temp;
	string word = "item";
	int random_num;
	srand(10);
	
	//--- Testing deleteMax functionality
	cout << "*** TESTING DELETEMAX ***" << endl << endl;

	// add 5 new random items to heap
	for (int i = 0 ; i < 5; i++) {
		random_num = rand() % 100;
		string text = word;
		text += std::to_string(i+1);
		cout << "adding " << text << ",  with number " << random_num << " to heap" << endl;
		hp.insert(text_item{text, random_num});	
		#ifdef DEBUG
		cout << "Top of heap is: " << hp.top() << endl;
		#endif
	}
	cout << "Top of heap is: " << hp.top() << endl; cout << endl;

	//--- This does not fully test delete_max functionality.
	cout << "@TEST: generic test" << endl;
	if (hp.size() > 1) {
		temp = hp.delete_max();
		cout << "Item returned from heap delete: "<< temp << endl;
		temp = hp.top();
		cout << "Top of heap is now: " << temp << endl;	
	}
	
	//--- Specific insert functionality that should be tested:
	
	// @TEST: remove_max works when swap_down with left child
	cout << endl << "@TEST: remove_max works when swap_down with left child" << endl;
	if (hp.size() > 1) {
		temp = hp.delete_max();
		cout << "Item returned from heap delete: "<< temp << endl;
		temp = hp.top();
		cout << "Top of heap is now: " << temp << endl;	
	}
		
	// @TEST: remove_max works when swap_down with right child
	cout << endl << "@TEST: remove_max works when swap_down with right child" << endl;
	if (hp.size() > 2) {
		temp = hp.delete_max();
		cout << "Item returned from heap delete: "<< temp << endl;
		temp = hp.delete_max();
		cout << "Item returned from heap delete: "<< temp << endl;
		temp = hp.top();
		cout << "Top of heap is now: " << temp << endl;	
	}
	
	// @TEST: remove_max on an empty heap - will throw exception
	while (hp.size() > 0) temp = hp.delete_max();
	cout << "Item returned from heap delete: "<< temp << endl;
	//hp.delete_max();
		
}

//--- PART 2: Implementation and testing of BST word_frequency
void tree_tester(string_bst const &tree) {
	cout << endl << endl << "BEGINNING TESTS FOR PART 2" << endl;
	cout << "*** TESTING WORDFREQUENCY ***" << endl;
	
	//--- Testing word_frequency functionality
	//--- This does not fully test word_frequency functionality.
	cout << endl << "@TEST generic test (should not exist in file)." << endl;
	#ifdef DEBUG
	tree.display();
	#endif
	if (tree.size() > 1) {
		string to_find = "difficult";
		int num_times = tree.word_frequency(to_find);
		cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << endl;
	}
	
	//--- Specific word_frequency functionality that should be tested:
	
	// @TEST: The word to look for is not the root.
	// can search through both left and right subtrees if not found at current node
	cout << endl << "@TEST: The word exists but is not the root." << endl;
	if (tree.size() > 1) {
		string to_find1 = "harder";
		string to_find2 = "better";
		string to_find3 = "faster";
		string to_find4 = "stronger";
		int num_times1 = tree.word_frequency(to_find1);
		int num_times2 = tree.word_frequency(to_find2);
		int num_times3 = tree.word_frequency(to_find3);
		int num_times4 = tree.word_frequency(to_find4);
		cout << "Found: "<< to_find1 << 
			" in the input file " << num_times1 
			<< " time(s)." << endl;
		cout << "Found: "<< to_find2 << 
			" in the input file " << num_times2 
			<< " time(s)." << endl;
		cout << "Found: "<< to_find3 << 
			" in the input file " << num_times3 
			<< " time(s)." << endl;
		cout << "Found: "<< to_find4 << 
			" in the input file " << num_times4 
			<< " time(s)." << endl;
	}
		
	// @TEST: The word to look for is not found in the tree.
	// @expected: returns 0 if word is not found
	cout << endl << "@TEST: The word to look for is not found in the tree." << endl;
	if (tree.size() > 1) {
		string to_findn = "beyonce";
		int num_timesn = tree.word_frequency(to_findn);
		cout << "Found: "<< to_findn << 
			" in the input file " << num_timesn 
			<< " time(s)." << endl;
	}

}

//--- PART 3: Implementation and testing of word frequency analysis
void overall_most_freq(max_heap hp) {
	cout << "*** Top 5 most frequent words: ***" << endl;
	
	// case: we have a top 5
	if (hp.size() > 4) {
		//cout << "Most frequent text item: " << hp.top() << endl;
		cout << hp.top() << endl; // #1
		hp.delete_max();
		cout << hp.delete_max() << endl; // #2
		cout << hp.delete_max() << endl; // #3
		cout << hp.delete_max() << endl; // #4
		cout << hp.delete_max() << endl; // #5
	} else {
		// just pop off each max freq and print it out until heap clean
		while (hp.size() > 0) {
			cout << hp.top() << endl;
			hp.delete_max();
		}
	}

}

void at_least_length(max_heap hp, size_t num_letters) {
	cout << "*** Top 5 most frequent words with at least " 
		<< num_letters << " letters ***" << endl;
		
	// count reaches 5 or we are at end of heap
	// either way, only print out the top if its length is > num_letters
	int count = 0;
	while (hp.size() > 0) {
		text_item top = hp.delete_max();
		if (top.word.length() >= num_letters) {
			cout << top << endl;
			count++;
		}
		if (count == 5) break;		
	}

	if (count == 0) cout << "No words found matching the criteria!" << endl;
}

void starts_with(max_heap hp, char starts_with_letter) {
	cout << "*** Top 5 most frequent words that begin with " 
		<< starts_with_letter << " ***" << endl;
		
	// count reaches 5 or we are at end of heap
	// either way, only print out the top if its first letter is correct
	int count = 0;
	while (hp.size() > 0) {
		text_item top = hp.delete_max();
		if (top.word.at(0) == starts_with_letter) {
			cout << top << endl;
			count++;
		}
		if (count == 5) break;
	}

	if (count == 0) cout << "No words found matching the criteria!" << endl;
}

void heap_tester() {	
	text_item temp;
	int heap_size = 15; //feel free to create heaps of other sizes when testing
	//cout << "How many items should be added to heap? ";
	//cin >> heap_size;
	max_heap hp(heap_size);
	cout << "Created heap of size " << heap_size << endl;
		
	//--- Testing heap size and top
	cout << "Current number of items in heap is: " << hp.size() << endl;
	try {
		temp = hp.top(); //should throw and exception without items in heap
		cout << "Top of heap is: " << temp << endl;	
	} catch (std::logic_error e) {
		cout << e.what() << endl;
	}
	// PART 1A:
	cout << endl << "BEGINNING TESTS FOR PART 1A" << endl;
	heap_insert_tests(hp);
	
	// PART 1B:
	cout << endl << "BEGINNING TESTS FOR PART 1B" << endl;
	heap_delete_tests(hp);
	
	// clean heap
	while (hp.size() > 0) hp.delete_max();
}

void text_analysis_tester(string_bst &tree) {
	cout << endl << "BEGINNING TESTS FOR PART 3" << endl;
	cout << "*** TESTING OVERALLMOSTFREQ ***" << endl;
	cout << endl << "@TEST: generic test of overall_most_freq" << endl;
	overall_most_freq(copy_to_heap(tree));

	cout << endl << "*** TESTING ATLEASTLENGTH ***" << endl;
	cout << endl << "@TEST: test at_least_length for words that exist" << endl;
	at_least_length(copy_to_heap(tree), 8);
	cout << endl << "@TEST: test at_least_length for words that exist (<5)" << endl;
	at_least_length(copy_to_heap(tree), 10);
	cout << endl << "@TEST: test at_least_length for words that do not exist" << endl;
	at_least_length(copy_to_heap(tree), 12);
	cout << endl << "@TEST: test at_least_length for all words" << endl;
	at_least_length(copy_to_heap(tree), 0);
	
	cout << endl << "*** TESTING STARTSWITH ***" << endl;
	cout << endl << "@TEST: test starts_with for words that exist" << endl;
	starts_with(copy_to_heap(tree), 'k');
	cout << endl << "@TEST: test starts_with for words that exist (<5)" << endl;
	starts_with(copy_to_heap(tree), 'y');
	cout << endl << "@TEST: test starts_with for words that do not exist" << endl;
	starts_with(copy_to_heap(tree), 'x');
	cout << endl;
}

int main(int argc, char* argv[]) {
	
	//--- Part 1: max_heap implementation
	heap_tester(); 
	
	//--- Part 2: string_bst implementation
	string_bst tree;
	load_bst("kanye.txt", tree); // create a bst from an input file.
	tree_tester(tree);			//sample2.txt contains a much bigger file
	
	//--- Part 3: word frequency analysis of text files
	text_analysis_tester(tree);

}
