#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef map<int, int>::iterator MIT;

typedef struct interval {
	int start;
	int end;
} I;

const int U = 1000006;
int n;
int x, y;

map<int, int> m;
vector<I> r;

bool cmp(I& p1, I& p2) {
	return p1.end > p2.end || (p1.end == p2.end && p1.start > p2.start);
}

void compress(int bound) {
	MIT last = m.lower_bound(bound);
	if(last == m.end()) return;
	
	int val = last->second; 
	for(MIT curr = last; curr != m.end(); ++curr) {
		val = max(val, curr->second);
	}
	
	m[last->first] = val;
	++last;
	if(last == m.end()) return;
	m.erase(last, m.end());
}

void task() {
	cin >> n;
	r.clear();
	m.clear();
	
	while(n-->0) {
		cin >> x >> y;
		r.push_back(I{x,y});
	}
	sort(r.begin(), r.end(), cmp);
	m[U] = 0;
	
	for(I& p : r) {
		compress(p.end);			
		MIT mit = m.find(p.start);
		int nval = (--m.end())->second + 1;
		if(mit == m.end()) 
			m[p.start] = nval;
		else 
			m[p.start] = max(mit->second, nval);
	}
	
	compress(-1);
	assert(m.size() == 1);
	cout << m.begin()->second << endl;
}

int main() {
	int t;
	cin >> t;
	while(t-->0) {
		task();
	}	
	return 0;
}
