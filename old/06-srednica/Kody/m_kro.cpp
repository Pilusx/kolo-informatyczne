#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 10000;    // Nigdzie nie jest używana ta zmienna.
vector<vector<int>> g;  // indeksy 0...w OK
vector<int> kolejnosc;  // indeksy 0... OK
vector<int> visited;    // indeksy 0...w OK (równie dobrze moglibyśmy nazwać ten vector 'ojciec')
vector<int> odleglosci; // indeksy 0...w OK
queue<int> s;
int w, a, b;

void wczytaj() {
    cin >> w;
    g.resize(w + 1);
    // Drzewo ma w, wierzchołków, w-1 krawędzi, liczb od 1 do w-2 jest w-2. Powinno być <w lub <=(w-1)
    for (int i = 1; i < (w - 1); i++) {
        // cin >> a >> b; Tak też można to zrobić.
        cin >> a;
        cin >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
}
void bfs(int x) {
    // Lepiej by było jakby inicjowanie odleglosci bylo w poblizu ich obliczania. Czyli na początku funkcji zbierz.
    for (int i = 0; i < odleglosci.size(); i++) { // krocej fill(odleglosci.begin(), odleglosci.end(), 0), zawsze potencjalnym błędem jest złe iterowanie (wyjscie poza zakres lub pominięcie indeksów)
        odleglosci[i] = 0;
    }
    // Dla wierzchołków o numerach od 1 do w czyli <=w.
    for (int i = 1; i < w; i++) { // krocej fill(visited.begin(), visited.end(), -1)
        visited[i] = -1;
    }
    s.push(x);
    // Pierwszy wierzchołek trzeba ustawić jako odwiedzony(visited) np. na zero, ważne jest to, żeby ta liczba nie była przypisana do istniejącego wierzchołka.
    while (!s.empty()) {
        int z = s.front();
        s.pop();
       
        // size() zwraca zmienną typu unsigned, co zazwyczaj nie ma znaczenia. Zazwyczaj, bo zazwyczaj na olimpiadach w vectorze nie będzie więcej niż 10^8 intów...
        for (int i = 0; i < g[z].size(); i++) {
            int q = g[z][i];
            if (visited[q] == -1) {
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
        for (int j = 0; j < g[kolejnosc[i]].size(); j++) {
            if (g[kolejnosc[i]][j] == visited[kolejnosc[i]] && odleglosci[kolejnosc[i]] < (odleglosci[g[kolejnosc[i]][j]] + 1)) {
                odleglosci[kolejnosc[i]] = odleglosci[g[kolejnosc[i]][j]] + 1;
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
    int idx = 0;
    for (int i = 1; i < odleglosci.size(); i++) {
        if (odleglosci[i] == m) { // Przy takim zapisie m zawsze będzie równe zero. Może miało być >m ?
            m = odleglosci[i];
            idx = i;
        }
    }
    // Można zauważyć, że wierzchołek najdalszy to kolejnosc[0] (dopiero po odwroceniu kolejnosci)
    // idx = kolejnosc[0];
    // m = odleglosci[idx];

    return idx;
}

int main() {

    // Inicjalizacja OK
    odleglosci.resize(w + 1); //OK
    visited.resize(w + 1); // OK

    // Nie zdążyliśmy tego zrobić, ale wypadałoby zrobić jeszcze:
    // Wczytanie danych ?

    // Odpalenie bfs'a ?

    // Wypisanie wyniku ?
    // Konce srednicy to bfs2(1), bfs2(bfs2(1)). Jak wypisać średnicę w czasie proporcjonalnym do jej długości? (Wskazówka: visited / ojciec)

    return 0;
}
