#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
T absolute(const T& x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

template <class T>
vector<T>& operator+(vector<T>& t, T x) {
  t.push_back(x);
  return t;
}
template <class T>
vector<T>& operator-(vector<T>& t, T x) {
  auto it = find(t.begin(), t.end(), x);
  if (it != t.end()) { // t.erase(t.end()) powoduje segmentation fault
    t.erase(it);
  }
  return t;
}

template <class T>
ostream& operator<<(ostream& os, vector<T> t) {
  for (auto x : t)
    os << x << " ";
  return os;
}

template <class T>
vector<T>& operator!(vector<T>& t) {
  t.clear(); // lub t.resize(0);
  return t;
}

vector<int> v = {1, 2, 3};
int main() {
  float x = -12387;
  printf("%f   %f   %d %d\n", absolute(x), x, absolute<int>(-3),
         absolute<int>(-3.5));

  v + 3 + 4;   // Dodaje 3 i 4
  v + (3 + 4); // Dodaje 7
  v - 1;       // Usuwa 1
  v - 1;       // Nie robi nic
  int n = 5;
  v + n; // Dodaje 5
  n++;   // Nie inkrementuje elementu w vectorze.

  cout << v << endl << 3 << endl;
  !v; // Czyści vector.
  v + 1;
  cout << v;
}
