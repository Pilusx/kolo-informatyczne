#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

//#define REVERSE
#ifndef REVERSE
typedef std::set<int> myset;
#else
// 8
#endif

int n;
int k;
myset s;
typedef myset::iterator sit;
typedef myset::reverse_iterator rsit;

inline void print_one_endl(int x) {	std::cout << x << std::endl; }
inline void print_endl() { std:: cout << std::endl; }
inline void print_one_elem(int x) {	std::cout << x << " "; }

int main() {
	std::fstream fs;
	sit it;
	rsit rit;
	fs.open("test.in");
	
	fs >> n;
	// 1
	
	// 2 
	
	// 3.1
	
	// 3.2
	
	// 3.3
	
	// 3.4

	// 4.1

	// 4.2
	
	// 4.3

	// 5

	// 6
	#ifndef REVERSE
	assert(!s.count(8) && s.count(3));
	assert(s.find(8) == s.end() && s.find(3) != s.end());
	#endif
	
	// 7
	
	fs.close();
	return 0;
}
