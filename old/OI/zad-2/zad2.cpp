#include <iostream>

using namespace std;

const int N = 100005;
int t[N];
int a, b, q;

bool czy_pierwsza(long long int n){
	if(n < 2)
		return false;
	for(long long int i = 2; i * i <= n; i++)
		if(n%i == 0)
			return false;
			
	return true;
}

void preprocessing(){
	for(int i = 0; i <= b; i++)
		t[i] = i;

	// Sito Erastotenesa
	// Obliczamy najmniejszy dzielnik danej liczby
	for(int i = 2; i <= b; i++)
		if(t[i] == i) // jesli pierwsza
			for(int j = 2; i*j <= b; j++)
				if(t[i*j] == i*j) // jesli nie znaleziono mniejszego dzielnika
					t[i*j] = i;
		
	// Obserwacja
	// Obliczamy dlugosc rozkladu			
	for(int i = 0; i <= b; i++)
		if(t[i] == i) // jesli pierwsza
			t[i] = 1;
		else // jesli zlozona
			t[i] = t[i/t[i]] + 1;

	// Jesli liczba jest pierwsza to ma tylko jeden dzielnik w rozkladzie i jest wieksza od 2

	// Obliczamy sumę prefiksową
	t[0] = 0; // O nie jest zlozone
	t[1] = 0; // 1 nie jest zlozone
	for(int i = 2; i <= b; i++)
		if(t[i] == 1) // Nie bierzemy pod uwage liczb pierwszych
			t[i] = t[i-1];
		else // Jesli zlozona to dodajemy
			t[i] = t[i-1] + t[i];
}

int p(int x){
	long long int k = x;
	if(czy_pierwsza(k*k + 1))
		return 1;
	else 
		return 0;
}

int f(int i, int j){
	if(j < 2)
		return 0;
	int ni = max(2, i); // Nie istnieja liczby dodatnie zlozone mniejsze od 2
	return t[j] - t[ni - 1];
}

int main(){
	ios_base::sync_with_stdio(0);
	int r, r1, r2;
	cin >> a >> b >> q;
	preprocessing();
	cout << f(a,b) << endl;
	
	for(int i = 0; i < q; i++){
		cin >> r;
		int acc = 0;
		r--;
		cin >> r2;
		while(r > 0){
			r1 = r2;
			cin >> r2;
			
			acc += p(r1) * f(r1, r2);
			r--;
		}
		cout << acc << endl;
	}

	return 0;
}
