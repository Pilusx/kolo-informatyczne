#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

const int N = 13;
const int M = N+1;
const int K = 130; // Zmienna do testow
int t[M]; // Drzewo Fenwicka gdzie t[i] jest sumą odpowiednich liczb a[j]... ze strażnikiem a[0] = 0
int fact[N]; // fact[i] = i!

/**
 * Oblicza kolejne silnie.
 */
void factorial() {
	fact[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = i*fact[i-1];
}

/**
 * Zwraca k-ta liczbe w zapisie silniowym.
 */
int wyciagnij(int n, int k) {
	return (n/fact[k-1])%k;
}

/**
 * Wypisuje vector na stdout.
 */
void vprint(vector<int> &v) {
	for(unsigned i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}


/**
 * Oblicza wartość a[1] + ... + a[x] na podstawie tablicy t.
 * read(0) powinno zwracać 0
 * (i&-i) może okazać się przydatne... (zwraca najmniejszą potęgę dwójki występującą w zapisie liczby)
 */
int read(int x){
	int res = 0;
	for(int i = x; i > 0; i-=(i&-i))
		res+=t[i];
	return res;
}

/**
 * Zwiększa a[x] o w, tj a[x] += w
 */
void update(int x ,int w) {
	for(int i = x; i < M; i+=(i&-i))
		t[i]+=w;
}

/**
 * Ma zwracać sumę liczb na przedziale [a...b] tj. a[a] + a[a+1] + ... + a[b]
 * Zakładamy, że 1 <= a <= b
 */
int query(int a, int b) {
	return read(b) - read(a-1);
}

/**
 * Funkcja inicjująca, mająca ustawić wszystkie wartości a[i] na 0
 * O(N)
 */
void clean() {
	fill(t, t+M, 0);
}


/**
 * Funkcja inicjująca ma ustawić wszystkie wartosci a[i] na 1
 * O(NlogN)
 */
void init() {
	for(int i = 1; i <= N; i++)
		update(i, 1);
}

/**
 * Wypisuje wartosci a[0] ... a[N] na stdout.
 * O(NlogN)
 */
void show_table() {
	cout << "Tree: ";
	for(int i = 0; i <= N; i++)
		cout << read(i) << " ";
	cout << endl;
}

/**
 * Komparator do wyszukiwania binarnego w wersji upper_bound.
 * 
 * Proszę zwrócić uwagę na miejsce występowania komparatora. (Wyciąg z cplusplus.com)
 * if (!(val<*it)) // or: if (!comp(val,*it)), for version (2)
 * 
 * O(logN)
 */
bool cmp(int k, int i) {
	return k < read(i);
}

/**
 * Należy znaleźć k-tą co do wielkości liczbę w zbiorze przy użyciu komparatora i upper_bound.
 * 
 * Uznajemy, że t jest naszą reprezentacją zbioru liczb od 1..n.
 * Liczba i jest w zbiorze gdy a[i] = 1, (a[i] = 0, gdy jej nie ma)
 * 
 * Obserwacja 1: Szukamy najmniejszej liczby i takiej, że a[1] + ... a[i] = k
 * Obserwacja 2: Jest to również pierwsza liczba i dla której a[1] + ... a[i] > k-1
 * 
 * Np. Dla {1,5,6,7} Drugą liczbą jest 5, a czwartą 7.
 * O((logN)^2)
 */
int kth(vector<int> &v, int k) {
	vector<int>::iterator vit = upper_bound(v.begin(), v.end(), k-1, cmp);
	return *vit;	
}

/**
 * Oblicza ktą permutację i zwracą ją jako vector (res).
 * 
 * Załozenia:
 * Często numeracja zaczyna się od 1, ale na potrzeby zadania zakładamy, że 0 <= k < N!
 * Vector v zawiera liczby od 0 do M
 * 
 * Np. dla N=3
 * k = 0 (1 2 3)
 * k = 5 (3 2 1)
 * 
 * Silniowy system pozycyjny
 * x = z[N-1]*(N-1)! + z[N-2]*(N-2)! + ... + z[1]*1! + z[0]*0!
 * 0 <= z[i] < i dla wszystkich i w zbiorze {0, 1 ... N-1}
 * Np. dla N=3
 * 5 = 2*2! + 1*1! + 0*0!
 * 0 = 0*0! + 0*1! + 0*0!
 * 
 * Obliczmy N=3, k=5
 * 1. {1, 2, 3} wybieramy (z[2]+1)-tą liczbę ze zbioru tj. 3 i usuwamy ją
 * 2. {1, 2} wybieramy (z[1]+1)-tą liczbe ze zbioru tj. 2 ..
 * 3. {1} wybieramy (z[0]+1)-tą liczbę ze zbioru tj 1 ...
 * Stąd (3 2 1)
 * 
 * Obliczmy N=4 k=7
 * 7 = 1*3! + 0*2! + 1*1! + 0*1!
 * 1. {1, 2, 3, 4} -> 2
 * 2. {1, 3, 4} -> 1
 * 3. {3, 4} -> 4
 * 4. {3} -> 3
 * (2 1 4 3)
 */
vector<int> kth_permutation(vector<int> &v, int k) {
	clean();
	//show_table();
	init();
	//show_table();
	
	vector<int> res;
	
	for(int i = N; i >= 1; i--) {
		int z = wyciagnij(k, i) + 1;
		int next = kth(v, z);
		update(next, -1);
		
		//cout << z << " " << next << " ";
		//show_table();
		res.push_back(next);	
	}

	return res;
}

int main() {
	vector<int> v, w;
	
	v.push_back(0);
	factorial();
    
    cout << "FACT: ";
    for(int i = 1; i < N; i++)
        cout << fact[i] << " ";
    cout << endl;
	
	for(int i = 1; i <= N; i++) {
		v.push_back(i);
		w.push_back(i);
	}
	v.push_back(N+1);
	
	/**
	 * Test poprawności, przykładowe zastosowanie słabych rozwiązań.
	 * Sprawdza poprawność dla pierwszych k permutacji
	 */
	for(int i = 0; i < K; i++) {
		vector<int> res = kth_permutation(v, i);
		if(!equal(w.begin(), w.end(), res.begin())) {
			cout << i << " BLAD, oczekiwano ";
			vprint(w);
			cout << " ,a otrzymano";
			vprint(res);
		}
		next_permutation(w.begin(), w.end());
	}
}
