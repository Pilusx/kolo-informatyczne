#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int U = 1000006;
int n;
int x, y;

struct sdp {
	vector<int> start;
	int dp;
} res[U];

void task() {
	cin >> n;
	for(int y = 0; y < U; y++) {
		res[y].start.clear();
		res[y].dp = 0;
	}
	
	while(n-->0) {
		cin >> x >> y;
		assert(x < y);
		res[y].start.push_back(x);
	}
	
	for(int y = U - 2; y >= 0; y--) {
		res[y].dp = max(res[y].dp, res[y+1].dp);
		for(int x : res[y].start) {
			res[x].dp = max(res[x].dp, res[y].dp + 1);
		}
	}
	cout << res[0].dp << endl;
}

int main() {
	int t;
	cin >> t;
	while(t-->0) {
		task();
	}	
	return 0;
}
