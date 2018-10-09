/** 
 * Kolko i krzyzyk cz. 1-4
 */
#include <iostream>
#include <vector>

using namespace std;

const int N = 9;
unsigned pot_n[N];
int n;
vector<vector<int> > g;

void potegi(unsigned x) {
	n = x;
	pot_n[0] = 1;
	for(unsigned i = 1; i < N; i++)
		pot_n[i] = x * pot_n[i-1];
}

unsigned wyciagnij(unsigned x, unsigned k) {
	return (x/pot_n[k])%n;
}

void wypisz(unsigned x) {
	for(int i = N - 1; i >= 0; i--)
		cout << wyciagnij(x, i) << " ";
	cout << endl;
}

void generuj(unsigned x) {
	g[x].clear();
	for(unsigned i = 0; i < N; i++) {
		if(wyciagnij(x, i) == 0) {
			for(unsigned j = 1; j <= 2; j++) {
				g[x].push_back(x + j*pot_n[i]);
			}
		}
	}
}

void wypisz_sasiadow(unsigned x) {
	cout << x << " : ";
	for(unsigned i = 0; i < g[x].size(); i++)
		cout << g[x][i] << " ";
	cout << endl;
	
}

unsigned zmien_gracza(unsigned x) {
	return x%2 + 1;
}

int main() {
	potegi(2);
	for(int i = 0; i <= 4; i++)
		cout << wyciagnij(13, i) << endl;
	cout << endl;
	
	
	potegi(3);
	wypisz(17);
	g.resize(3*pot_n[8]);
	generuj(0);
	wypisz_sasiadow(0);
	
	return 0;
}
