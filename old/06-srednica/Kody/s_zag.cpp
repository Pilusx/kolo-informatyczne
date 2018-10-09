#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> v;  // 0...n OK
vector<int> kolejnosc;  // 0... OK
vector<int> visited;    // 0...n OK (równie dobrze moglibyśmy nazwać ten vector 'ojciec')
vector<int> odleglosci; // 0...n OK
void bfs(int x) {
    // Lepiej by było jakby inicjowanie odleglosci bylo w poblizu ich obliczania. Czyli na początku funkcji zbierz.
    for (int i = 0; i < odleglosci.size(); i++) { // OK krocej fill(visited.begin(), visited.end(), -1), zawsze potencjalnym błędem jest złe iterowanie (wyjscie poza zakres lub pominięcie indeksów)
        odleglosci[i] = 0;
    }
    for (int i = 1; i < n + 1; i++) { // NIE OK, n powinno być globalne, ale wtedy w bfs2 inna zmienna też nazywa się n ... lub krócej fill(visited.begin(), visited.end(), -1)
        visited[i] = -1;
    }

    queue<int> s;
    s.push(x);
    // Pierwszy wierzchołek trzeba ustawić jako odwiedzony(visited) np. na zero, ważne jest to, żeby ta liczba nie była przypisana do istniejącego wierzchołka.

    while (!s.empty()) {
        int z = s.front();
        s.pop();

        // size() zwraca zmienną typu unsigned, co zazwyczaj nie ma znaczenia. Zazwyczaj, bo zazwyczaj na olimpiadach w vectorze nie będzie więcej niż 10^8 intów...
        for (int i = 0; i < v[z].size(); i++) { // OK
            int q = v[z][i];
            if (q == -1) {
                visited[q] = z;
                kolejnosc.push_back(q);
                // Trzeba jeszcze wrzucić q na koniec kolejki 's', w przeciwnym wypadku do kolejnosci wrzucimy tylko wierzchołek początkowy i jego sąsiadów.
            }
        }
    }
}
int bfs2(int x) {
    bfs(x);
    reverse(kolejnosc.begin(), kolejnosc.end()); //OK

    for (int i = 0; i < kolejnosc.size(); i++) {
        for (int j = 0; j < v[kolejnosc[i]].size(); j++) {
            if (v[kolejnosc[i]][j] != visited[kolejnosc[i]] && odleglosci[kolejnosc[i]] < odleglosci[v[kolejnosc[i]][j]] + 1) { // Coś z nawiasami kwadratowymi nie działało.
                odleglosci[kolejnosc[i]] = odleglosci[v[kolejnosc[i]][j]] + 1;
            }
        }
    }
    /* Równoważny trickowy zapis tego samego. Warto wiedzieć, że to co tutaj się dzieje to 'iterowanie' po vectorze przy użyciu 'iteratorów'. Dosyć nieprzydatne JEŚLI potrzebujemy indeksów w vectorze.
    for(int k : kolejnosc) { // k - oznacza aktualnie przetwarzany wierzchołek
		for(int s : g[k]) { // s - jest jakimś jego sąsiadem
			if(visited[s] == k) { //  k jest ojcem s
				odleglosci[k] = max(odleglosci[k], odleglosci[s] + 1);
            }
        }
    }
    */

    
    int m = 0;
    int n = 0;
    for (int i = 0; i < odleglosci.size(); i++) {
        if (odleglosci[i] > m) { // OK
            m = odleglosci[i];
            n = i;
        }
    }

    // Można zauważyć, że wierzchołek najdalszy to kolejnosc[0] (dopiero po odwroceniu kolejnosci)
    // n = kolejnosc[0];
    // m = odleglosci[n];
    return n;
}
int main() {
    // Inicjalizacja OK
    int n;
    cin >> n;
    v.resize(n + 1);
    for (int i = 0; i < n - 1; i++) { // OK
        int a, b;
        cin >> a;
        cin >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }

    visited.resize(n + 1); //OK
    odleglosci.resize(n + 1); //OK

    // Nie zdążyliśmy tego zrobić, ale wypadałoby zrobić jeszcze:
    // Odpalenie bfs'a ?

    // Wypisanie wyniku ?
    // Konce srednicy to bfs2(1), bfs2(bfs2(1)). Jak wypisać średnicę w czasie proporcjonalnym do jej długości? (Wskazówka: visited / ojciec)

    return 0;
}
