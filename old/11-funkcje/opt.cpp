#include<iostream>
#include<cassert> // assert
#include<climits> // MAX_INT

#define N 1000
using namespace std;

int dp[N+2][N+2];
int dpk[N+2][N+2];
int a[N+2];

// kolumny(i) == wiersze(i+1)
#define kolumny(i) a[(i)+1]
#define wiersze(i) a[(i)]
#define liczba_mnozen(i,j,k) wiersze(i) * kolumny(k) * kolumny(j) 

void oblicz(int i, int j) {
	assert(i < j);
	
	int minim = INT_MAX;
	int argmin = -1;
	int temp;
	
	for(int k = i; k < j; k++) {
		temp = dp[i][k] + dp[k+1][j] + liczba_mnozen(i,j,k);
		if(temp < minim) {
			minim = temp;
			//cout << i << " " << k << " " << j << liczba_mnozen(i, j, k) << endl;
			argmin = k;
		}
	}
	
	assert(argmin != -1);
	dpk[i][j] = argmin;
	dp[i][j] = minim;
}

void nawias(int i, int j) {
	assert(i <= j);
	
	if(i == j)
		cout << i;
	else {
		int k = dpk[i][j];
		
		cout << "(";
		nawias(i, k);
		cout << ")*(";
		nawias(k+1, j);
		cout << ")";
	}
}


void nawias2(int i, int j) {
	assert(i <= j);
	
	if(i == j)
		cout << i;
	else {
		int k = dpk[i][j];
		
		if(k - i >= 1) cout << "(";
		nawias2(i, k);
		if(k - i >= 1) cout << ")";
		
		cout << "*";
		
		if(j - k >= 2) cout << "(";
		nawias2(k+1, j);
		if(j - k >= 2) cout << ")";
	}
}

void wypisz_poziom(int v, int poziom){
	while(--poziom)
		cout << "-";
	cout << v << endl;
}

void drzewko(int i, int j, int poziom=0) {
	assert(i <= j);
	if(i == j)
		wypisz_poziom(i, poziom);
	else {
		int k = dpk[i][j];
		drzewko(i, k, poziom + 1);
		cout << "(" << liczba_mnozen(i, j, k) << ")" << endl;
		drzewko(k+1, j, poziom + 1);
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	int n; // Liczba macierzy, n+1 - liczba elementów w ciągu
	
	cin >> n;
	for(int i = 0; i <= n; i++)
		cin >> a[i];
	
	for(int i = 0; i < n; i++)
		dp[i][i] = 0;
		
	for(int d = 1; d < n; d++) {
		for(int i = 0; i + d < n; i++)
			oblicz(i, i + d);
	}
	
	cout << dp[0][n-1] << endl;
	nawias(0, n-1);
	cout << endl;
	nawias2(0, n-1);
	cout << endl;
	drzewko(0, n-1);
}
