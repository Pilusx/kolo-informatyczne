#include <list>
#include <string>
#include <iostream>

using namespace std;

list<char> q;
string s;

void foo() {
	cin >> s;
	
	for(size_t i = 0; i < s.size(); i++) {
		while(!q.empty() && s[i] < q.back()) {
			q.pop_back();
		}
		q.push_back(s[i]);
	}
	
	while(!q.empty()) {
		cout << q.front();
		q.pop_front();
	}
	cout << endl;
	
	s.clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		foo();
	}
	
	return 0;
}
