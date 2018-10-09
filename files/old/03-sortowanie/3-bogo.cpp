#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;
using vit = vector<int>::iterator;

void wypisz(vector<int> &v) {
	cout << "Wektor: ";
	vit it = v.begin();
	
	while(it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

int main() {
	unsigned n;
	vector<int> v;
	//cin >> k >> n;
	n = 4;
	for(unsigned i = 0; i < n; i++)
		v.push_back(n-i);
	
	cout << v.size() << endl;
	
	wypisz(v);
	
	while(!is_sorted(v.begin(), v.end())) {
		for(unsigned i = 0; i < n; i++)
			cout << v[i] << " ";
		cout << endl;
		
		random_shuffle(v.begin(), v.end());
	}
	
	if(v.end() == v.begin() + n) {
		cout << "Sa rowne" << endl;
	}
	
	for(unsigned i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << endl;
	
}
