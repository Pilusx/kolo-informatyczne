/** 
 * Kolko i krzyzyk cz. 1-8
 */
#include <iostream>
#include <vector>

using namespace std;

const int N = 9;
const int SPRAWDZENIE = 8;
const int SPRAWDZENIE_DL = 3;
const int KONIEC = 2;

unsigned pot_n[N];
int n;
vector<vector<int> > g;
vector<int> wyniki;

const int sprawdzenie[SPRAWDZENIE][SPRAWDZENIE_DL] = {{0, 1, 2}, {3, 4, 5}, 
	{6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

const int koniec[KONIEC] = {13, 26}; // 111 lub 222
const char stan[3] = {'_', 'X', 'O'};

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

void wypisz_sasiadow(unsigned x) {
	cout << x << " : ";
	for(unsigned i = 0; i < g[x].size(); i++)
		cout << g[x][i] << " ";
	cout << endl;
	
}

inline unsigned zmien_gracza(unsigned x) {
	return x%2 + 1;
}



void wypisz_stan(unsigned x) {
	cout << "===" << endl;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++)
			cout << stan[wyciagnij(x, 3*i + j)];
		cout << endl;
	}
	cout << "===" << endl;
}


/*
 * 1 - wygrywa X
 * 0 - remis
 * -1 - wygrywa O
 * -2 - gra sie jeszcze nie skonczyla
 */
int wynik_w_ustawieniu(unsigned x, int numer_sprawdzenia) {
	int wynik = 0;
	for(int i = 0; i < SPRAWDZENIE_DL; i++) {
		wynik += pot_n[i] * wyciagnij(x, sprawdzenie[numer_sprawdzenia][i]);
	}
	
	if (wynik == koniec[0]) 
		return 1;
	else if (wynik == koniec[1])
		return -1;
	else if (g[x].size() == 0)
		return 0;
	else 
		return -2;
} 

int wynik_w_stanie(unsigned x) {
	int wynik = -2;
	
	for(int i = 0; i < SPRAWDZENIE; i++) {
		wynik = max(wynik, wynik_w_ustawieniu(x, i));
	}
	
	return wynik;
}

void generuj_gracz(unsigned x, unsigned gracz) {
	g[x].clear();
	for(unsigned i = 0; i < N; i++) {
		if(wyciagnij(x, i) == 0) {
			g[x].push_back(x + gracz*pot_n[i]);
		}
	}
}

int dfs_rek(unsigned x, unsigned gracz) {
	generuj_gracz(x, gracz);
	
	int wynik = wynik_w_stanie(x);
	if(wynik == -2) {
		wynik = (gracz == 1 ? -1 : 1);
		for(unsigned i = 0; i < g[x].size(); i++) {
			int czesciowy = dfs_rek(g[x][i], zmien_gracza(gracz));
			wynik = (gracz == 1 ? max(czesciowy, wynik) : min(czesciowy, wynik));
		}
	}
	
	wyniki[x] = wynik;
	return wynik;
}

void dfs_rek_odtworz(unsigned x) {
	wypisz_stan(x);
	wypisz(x);
	wypisz_sasiadow(x);
	cout << endl;
	
	int w = wynik_w_stanie(x);
	if(w == -2) {
		int i = 0;
		while(wyniki[g[x][i]] != wyniki[x])
			i++;
		
		dfs_rek_odtworz(g[x][i]);
	}
}

int main() {
	potegi(3);
	g.resize(pot_n[8]*3);
	wyniki.resize(pot_n[8]*3);
	
	int wynik = dfs_rek(0, 1);
	cout << "Jesli X zaczyna gre na pustej planszy to przy optymalnej grze przeciwnika " <<
		(wynik == 1 ? "wygra" : (wynik == 0 ? "zremisuje" : "przegra")) << endl;
	
	cout << "Przykladowa rozgrywka" << endl;
	dfs_rek_odtworz(0);

	return 0;
}
