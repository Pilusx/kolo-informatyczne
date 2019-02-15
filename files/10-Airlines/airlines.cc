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
  int mask;
  int used;
};

/* Wypisuje maske na strumien */
ostream& operator<<(ostream& os, const Mask& mask) {
  const int B = 4;
  bitset<B> b = mask.mask;
  os << "(" << b.to_string() << " " << mask.used << ")";
  return os;
}

/* Sprawdza czy maska jest dobra (tzn. nie ma dwoch kolejnych zapalonych bitow)
 */
inline bool good_mask(int x) {
  bool last = x % 2;
  x /= 2;
  while (x > 0) {
    if (x % 2 == 1 && last) return false;
    last = x % 2;
    x /= 2;
  }
  return true;
}

/* Oblicza liczbe zapalonych bitow (tj. bitset::count() dla intow */
inline int count(int x) {
  int count = 0;
  while (x > 0) {
    if (x % 2 == 1) count++;
    x /= 2;
  }
  return count;
}

/* Zapisuje wszystkie dobre maski (rozmiaru maksymalnie m, uzywajacych
 * maksymalnie k bitow) do vectora */
void get_good_masks(vector<Mask>& v, int m, int k) {
  int used;
  v.clear();
  for (int i = 0; i < (1 << m); i++) {
    used = count(i);
    if (good_mask(i) && used <= k) {
      v.push_back({i, used});
    }
  }
}

bool operator<(const Mask& lhs, const Mask& rhs) {
  return lhs.mask < rhs.mask || (lhs.mask == rhs.mask && (lhs.used < rhs.used));
}

int task_1(int m, int n, int k) {
  /* Znajdz dobre maski i zapisz je do vectora */
  vector<Mask> masks;
  get_good_masks(masks, m, k);

  /* Zainicjalizuj liczbe sposobow dla pierwszej warstwy dp[1]. Dla kazdej maski
   * wynosi ona 1. */
  map<Mask, int> dp[2];
  for (Mask mask : masks) {
    dp[1][mask] = 1;
  }

  /* Oblicz wszystkie mozliwe kombinacje par dla nastepujacych po sobie warstw.
   */
  int r = 0;
  map<int, set<int>> pairs;
  for (Mask& mask : masks) {
    for (Mask& mask2 : masks) {
      if ((mask.mask & mask2.mask) == 0) {
        pairs[mask.mask].insert(mask2.mask);
        r++;
      }
    }
  }

  /* Przejdz po wszystkich warstwach obliczajac liczbe kombinacji */
  Mask current;
  int options;
  for (int l = 2; l <= n; l++) {
    cerr << l << " iteration" << endl;
    auto& dpc = dp[l % 2];
    auto& dpf = dp[(l + 1) % 2];
    dpc.clear();
    for (auto& state : dpf) {
      // cout << state.first << "->" << state.second << ", ";
      for (int mask : pairs[state.first.mask]) {
        current.mask = mask;
        current.used = count(mask) + state.first.used;
        options = state.second;
        if (current.used <= k) {
          auto it = dpc.find(current);
          dpc[current] =
              (it != dpc.end() ? madd(it->second, options) : options);
        }
      }
    }
    // cout << endl;
  }

  /* Przejdz po ostatniej warstwie i zsumuj wszystkie dobre mozliwosci (tj.
   * wszystkie warstwy uzywajace dokladnie k osob) */
  int res = 0;
  for (auto& state : dp[n % 2]) {
    current = state.first;
    if (state.first.used == k) {
      // cout << current << "->" << state.second << endl;
      res = madd(res, state.second);
    }
  }
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
  vector<Mask> masks;
  /* Znajdz wszystkie dobre maski */
  get_good_masks(masks, m, k);

  /* Znajdz funkcje odwrotna (mape) dla funkcji indeks -> maska (tj. maska ->
   * indeks w vectorze) */
  map<int, int> inv_mask;
  for (int i = 0; i < masks.size(); i++) {
    inv_mask[masks[i].mask] = i;
  }

  /* Znajdz macierz T tranzycji miedzy warstwami. Rozpatrz masks.size() * (k+1)
   * roznych stanow. Kazdy stan to maska (ze zmodyfikowana liczba posadzonych
   * osob) Nalezy uwzglednic osoby posadzone w poprzednich warstwach.
   * Mozliwych opcji jest
   */
  const int X = masks.size() * (k + 1);
  const int shape[2] = {X, X};
  Matrix T(shape);
  T.zeros();

  Mask last, current;
  int j;
  for (int i = 0; i < X; i++) {
    decode(k + 1, last, masks, i);
    for (auto& mask : masks) {
      if ((mask.mask & last.mask) == 0) {
        current.mask = mask.mask;
        current.used = last.used + mask.used;
        if (current.used <= k) {
          encode(k + 1, current, inv_mask, j);
          T[j][i] = 1;
        }
      }
    }
  }

  /*
    Znajdz:
    - sn = R * s0, gdzie s0[i] oznacza liczbe sposobow na otrzymanie danej maski
    w zerowej warstwie. (Jedyna dozwolona zerowa warstwa jest pusta, siedzi w
    niej 0 osob.)
    - R = T ^ n;
    */
  Matrix R(shape);
  R.zeros();
  Vector s0(X), sn(X);
  current.mask = 0;
  current.used = 0;
  encode(k + 1, current, inv_mask, j);
  s0[j] = 1;

  power(T, n, R);
  matvecmul(R, s0, sn);
  cerr << sn << endl;

  /* Przejdz po ostatniej warstwie i zsumuj wszystkie dobre mozliwosci (tj.
   * wszystkie sn[i] takie, że i-ta maska w wektorze uzywa dokladnie k
   * osob) */
  int res = 0;
  for (int i = 0; i < X; i++) {
    decode(k + 1, current, masks, i);
    if (current.used == k) {
      res = madd(res, sn[i]);
    }
  }

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