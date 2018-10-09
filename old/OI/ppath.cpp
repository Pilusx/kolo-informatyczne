#include <iostream>
#include <queue>

using namespace std;

const int N = 10004;
int p[N];
int d[N];
queue<int> q;

int czy_pierwsza(int n) {
	if(n < 2) return 0;
	for(int i = 2; i*i <= n; i++)
		if(n%i == 0)
			return 0;
	return 1;
}

void czysc() {
	for(int i = 0; i < N; i++)
		d[i] = -1;
}

void odwiedz(int x) {
	for(int i = 1; i <= 1000; i *= 10) {
		int z = x - (x%(10*i) / i) * i;
		for(int j = 0; j < 10; j++) {
			int next = z + j*i;
			if(next >= 1000 && d[next] == -1 && czy_pierwsza(next)) {
				d[next] = d[x] + 1;
				q.push(next);
			}
		}
	}
}

void bfs(int x) {
	q.push(x);
	
	while(!q.empty()) {
		int d = q.front();
		q.pop();
		odwiedz(d);
	}
}

int main() {
	int x, y, z;
	cin >> x;
	for(int i = 0; i < x; i++) {
		cin >> y >> z;
		czysc();
		d[y] = 0;
		bfs(y);
		if(d[z] == -1)
			cout << "Impossible" << endl;
		else
			cout << d[z] << endl;
	}
}
