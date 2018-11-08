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
struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs>rhs;}
};

typedef std::set<int, classcomp> myset;
#endif

int n;
int k;
myset s;
typedef myset::iterator sit;
typedef myset::reverse_iterator rsit;

inline void print_one_endl(int x) {	std::cout << x << std::endl; }
inline void print_endl() { std:: cout << std::endl; }
inline void print_one_elem(int x) { std::cout << x << " "; }

void biggest_4(myset& s) {
	rsit rit = s.rbegin();
	for(int i = 0; i < 4; ++i, ++rit)
		print_one_elem(*rit);
	print_endl();
}

int main() {
	std::fstream fs;
	sit it;
	rsit rit;
	fs.open("test.in");
	
	fs >> n;
	// 1
	while(n-->0) {
		fs >> k;
		s.insert(k);
	}
	
	// 2 
	for(int m : s) 
		print_one_elem(m);
	print_endl();
	
	// 3.1
	print_one_endl(*s.begin());
	
	// 3.2
	it = s.begin();
	for(int i = 0; i < 4; ++i, ++it)
		print_one_elem(*it);
	print_endl();
	
	// 3.3
	print_one_endl(*(--s.end()));
	
	// 3.4
	for(it=s.begin(); it != s.end(); ++it)
		print_one_elem(*it);
	print_endl();
	
	// 4.1
	biggest_4(s);

	// 4.2
	it = s.end();
	std::advance(it, -4);
	print_one_endl(*it);
	
	// 4.3
	s.erase(it, s.end());

	// 5
	print_one_endl(s.size());

	// 6
	#ifndef REVERSE
	assert(!s.count(8) && s.count(3));
	assert(s.find(8) == s.end() && s.find(3) != s.end());
	#endif
	
	// 7
	print_one_elem(*s.lower_bound(3));
	print_one_elem(*s.upper_bound(3));
	print_one_elem(*s.lower_bound(4));
	print_one_elem(*s.upper_bound(4));
	print_endl();
	
	fs.close();
	return 0;
}
