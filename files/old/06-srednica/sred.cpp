#include <algorithm>
#include <iomanip> // setw, left w makrze S(x) do ładnego wypisywania wyjścia
#include <iostream>
#include <vector>

using namespace std;

int v; // Liczba wierzcholkow, numerujemy od 1..v, 0 jest nieużywane

struct Values {
  int h; // height - głebokość
  int D; // diameter - średnica
  int r; // sciezka nie przechodzaca przez korzen
  int s; // sciezka przechodzaca przez korzen
  int p; // parent - rodzic (-1 jeśli nie wpisany, 0 jeśli korzeń)
};

vector<vector<int>> g; // Graph - graf
vector<Values> val;    // Result - wynik

int current_parent;
int start;           // Wierzcholek początkowy
const int SPACE = 6; // Ile cyfrowe liczby chcemy wypisywać
const int TITLE_SPACE = 6 * SPACE + 20;

// Aby skrócić kod (jedynie w warunkach konkursowych, gdzie liczy się czas, w
// projektach nazwy powinny "dawać się czytać")
#define h(x) val[x].h
#define r(x) val[x].r
#define s(x) val[x].s
#define p(x) val[x].p
#define D(x) val[x].D
//#define n(x) g[x].size() // <- Byłoby jeszcze krócej i mniej czytelnie n(x) =
// deg_out(x) (liczba krawędzi wychodzących)

#define h2(x, i) h(g[x][i])
#define r2(x, i) r(g[x][i])
#define s2(x, i) s(g[x][i])
#define p2(x, i) p(g[x][i])
#define D2(x, i) D(g[x][i])

// Porządek dla synów wierzchołka, ojciec jest zawsze na końcu
bool cmp(int a, int b) {
  if (a == current_parent)
    return false;
  if (b == current_parent)
    return true;
  return h(a) > h(b);
}

void for1(int x) {
  for (unsigned i = 0; i < g[x].size(); i++) {
    if (g[x][i] != p(x)) {
      h(x) = max(h(x), h2(x, i) + 1); // Przedlużamy ścieżkę do liścia o 1
      r(x) = max(r(x), D2(x, i)); // !!! Jakaś długa ścieżka z poddrzewa nie
                                  // przechodząca przez korzeń
    }
  }
}

void for2(int x) {
  // Poniższy zapis jest równowazny, ALE nie umożliwia nam zmiany g[x][i](tj. y)
  for (int y : g[x]) { // Iterujemy od lewej do prawej
    if (y != p(x)) {
      h(x) = max(h(x), h(y) + 1);
      r(x) = max(r(x), D(y));
    }
  }
}

// Kumuluje wynik z poddrzew
void cumul(int x) {
  current_parent = x;
  for1(x);
  // for2(x);

  // Sortujemy tylko dlatego, że potrzebujemy dwóch największych wartości, jeśli
  // kolejność nie ma znaczenia to nasz algorytm stanie się liniowy.
  sort(g[x].begin(), g[x].end(), cmp);

  // Nie wliczamy ojca (ojciec + 2 synów, o ile w g[x] jest ojciec (w korzeniu
  // go nie ma))
  if (g[x].size() >= 3 || (start == x && g[x].size() >= 2))
    s(x) = h2(x, 0) + h2(x, 1) + 2;

  D(x) = max(h(x), max(r(x), s(x)));
}

// Zagłębia się rekurencyjnie do poddrzew i kumuluje wynik
void dfs(int x) {
  for (unsigned i = 0; i < g[x].size(); i++) {
    if (g[x][i] != p(x)) {
      p2(x, i) = x; // Ustaw mnie jako ojca u syna
      dfs(g[x][i]); // Policz wyniki dla syna
    }
  }

  // Zakładamy, że do tego momentu zostały: policzone wszystkie wartości Values
  // dla poddrzeworaz x zna swojego rodzica
  cumul(x);
}

// Można prosto pokazać, że cały algorytm zadziała w czasie O(V log V)
int dfs_run(int x) {
  // Inicjalizacja
  // Wartości początkowe dla liści {h = 0, d = 0, r = 0, s = 0, p = ? }
  fill(val.begin(), val.end(), Values{0, 0, 0, 0, -1});
  val[x] = Values{0, 0, 0, 0, 0};
  start = x;

  dfs(x);
  return D(x);
}

void add_edge(int x, int y) {
  g[x].push_back(y);
  g[y].push_back(x);
}

void clear() {
  for (auto& l : g)
    l.clear();

  g.clear();
  val.clear();
}

// Przystosowuje wektory do grafów v_num-1 - wierzchołkowych
void resize(int v_num) {
  g.resize(v_num);
  val.resize(v_num);
}

void print_value(int i) {
  cout << "Idx: " << setw(SPACE) << i << " h: " << setw(SPACE) << h(i)
       << " D: " << setw(SPACE) << D(i) << " r: " << setw(SPACE) << r(i)
       << " s: " << setw(SPACE) << s(i) << " p: " << setw(SPACE) << p(i)
       << endl;
}

void print_vec() {
  cout << "Values: " << endl;
  for (unsigned i = 0; i < val.size(); i++)
    print_value(i);
}

// Scieżka
void test_path(int v_num) {
  clear();
  v = v_num;
  resize(v + 1);

  for (int i = 1; i < v; i++)
    add_edge(i, i + 1);

  dfs_run(1);
  print_vec();
}

// Drzewo binarne
void test_bin(int v_num) {
  clear();
  v = v_num;
  resize(v + 1);
  for (int i = 2; i <= v; i++)
    add_edge(i / 2, i);

  dfs_run(1);
  print_vec();
}

// iomanip
#define TITLE(x)                                                               \
  cout << "=== " << setw(TITLE_SPACE) << left << x << " ===" << endl

int main() {
  TITLE("Ścieżka długości 5");
  test_path(5);

  TITLE("Ścieżka długości 70");
  test_path(70);

  TITLE("Drzewo binarne 32 wierzchołkowe");
  test_bin((1 << 5) - 1);

  TITLE("Drzewo binarne 33 wierzchołkowe");
  test_bin(1 << 5);
}
