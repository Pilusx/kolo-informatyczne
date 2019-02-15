#include <bitset>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "matrix.hpp"

using namespace std;

struct Mask {
  ?
};

/* Wypisuje maske na strumien */
ostream& operator<<(ostream& os, const Mask& mask) {
  const int B = 4;
  bitset<B> b = ? ;
  os << "(" << b.to_string() << " " << ? << ")";
  return os;
}

/* Sprawdza czy maska jest dobra (tzn. nie ma dwoch kolejnych zapalonych bitow)
 */
inline bool good_mask(int x) {
  // TODO
}

/* Oblicza liczbe zapalonych bitow (tj. bitset::count() dla intow */
inline int count(int x) {
  // TODO
}

/* Zapisuje wszystkie dobre maski (rozmiaru maksymalnie m, uzywajacych
 * maksymalnie k bitow) do vectora */
void get_good_masks(vector<Mask>& v, int m, int k) {
  // TODO
}

bool operator<(const Mask& lhs, const Mask& rhs) {
  // TODO
}

int task_1(int m, int n, int k) {
  /* Znajdz dobre maski i zapisz je do vectora */
  // TODO

  /* Zainicjalizuj liczbe sposobow dla pierwszej warstwy dp[1]. Dla kazdej maski
   * wynosi ona 1. */
  // TODO

  /* Oblicz wszystkie mozliwe kombinacje par dla nastepujacych po sobie warstw.
   */
  // TODO

  /* Przejdz po wszystkich warstwach obliczajac liczbe kombinacji */
  // TODO

  /* Przejdz po ostatniej warstwie i zsumuj wszystkie dobre mozliwosci (tj.
   * wszystkie warstwy uzywajace dokladnie k osob) */
  // TODO

  return res;
}

/*
  different_used - liczba roznych wartosci "used" dla maski (zazwyczaj k+1)
  mask - maska
  inv_mask - przechowuje indeks maski w vectorze
  code - zakodowana maska
*/
void encode(int different_used, const Mask& mask, const map<int, int>& inv_mask,
            int& code) {
  code = inv_mask.find(mask.mask)->second * different_used + mask.used;
}

/*
  different_used - liczba roznych wartosci "used" dla maski (zazwyczaj k+1)
  mask - maska
  masks - vector dostepnych masek
  code - zakodowana maska
*/
void decode(int different_used, Mask& mask, const vector<Mask>& masks,
            int code) {
  mask.used = code % different_used;
  mask.mask = masks[code / different_used].mask;
}

int task_2(int m, int n, int k) {
  /* Znajdz wszystkie dobre maski */
  // TODO

  /* Znajdz funkcje odwrotna (mape) dla funkcji indeks -> maska (tj. maska ->
   * indeks w vectorze) */
  // TODO

  /* Znajdz macierz T tranzycji miedzy warstwami. Rozpatrz masks.size() * (k+1)
   * roznych stanow. Kazdy stan to maska (ze zmodyfikowana liczba posadzonych
   * osob) Nalezy uwzglednic osoby posadzone w poprzednich warstwach.
   * Mozliwych opcji jest [liczba roznych masek] * [liczba
   * roznych liczb posadzonych osob 0...k]
   */
  // TODO

  /*
    Znajdz:
    - sn = R * s0, gdzie s0[i] oznacza liczbe sposobow na otrzymanie danej maski
    w zerowej warstwie. (Jedyna dozwolona zerowa warstwa jest pusta, siedzi w
    niej 0 osob.)
    - R = T ^ n;
    */
  // TODO

  /* Przejdz po ostatniej warstwie i zsumuj wszystkie dobre mozliwosci (tj.
   * wszystkie sn[i] takie, że i-ta maska w wektorze uzywa dokladnie k
   * osob) */
  // TODO

  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  int m, n, k, i = 1;
  string line;
  stringstream ss;
  while (getline(cin, line)) {
    if (line.size() > 1) {
      cerr << "CASE " << i << ": ";
      ss.clear();
      ss.str(line);
      ss >> m >> n >> k;
      cerr << m << " " << n << " " << k << endl;
      if (n > 50) {
        cout << task_2(m, n, k) << endl;
      } else {
        cout << task_1(m, n, k) << endl;
      }
      i++;
    }
  }

  return 0;
}