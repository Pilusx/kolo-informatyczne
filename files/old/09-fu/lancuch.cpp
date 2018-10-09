#include <iostream>
#define N 500005
#define K 20
//#define DEBUG

using namespace std;
int father[N][K];
int ranga[N][K];
int score;
int n, m, v1, v2, k, d;

int Find(int x, int poz) {
  if (father[x][poz] == x)
    return x;
  else
    father[x][poz] = Find(father[x][poz], poz);
  return father[x][poz];
}
void Union(int a, int b, int poz) {
  a = Find(a, poz);
  b = Find(b, poz);
  if (a == b)
    return;
  if (ranga[a][poz] < ranga[b][poz])
    ranga[b][poz] += ranga[a][poz], father[a][poz] = b;
  else
    ranga[a][poz] += ranga[b][poz], father[b][poz] = a;
}

int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  // Inicjalizacja
  for (int z = 0; z < K; z++)
    for (int i = 1; i <= n; i++)
      father[i][z] = i, ranga[i][z] = 1;

  // Wczytanie danych
  for (int i = 0; i < m; i++) {
    cin >> v1 >> v2 >> k;
    for (int z = 0; k > 0; z++) {
      if (k % (1 << (z + 1)) == (1 << z)) {
        Union(v1, v2, z);
#ifdef DEBUG
        cout << v1 << " " << v2 << " " << (1 << z) << endl;
#endif
        v1 += (1 << z);
        v2 += (1 << z);
        k -= (1 << z);
      }
    }
  }

  // Przepychamy w dol
  for (int p = K - 1; p > 0; p--) {
    for (int i = 1; i <= n; i++)
      if (Find(i, p) != i) {
        Union(Find(i, p), i, p - 1);
        Union(Find(i, p) + (1 << (p - 1)), i + (1 << (p - 1)), p - 1);
      }
  }

#ifdef DEBUG
  for (int z = 0; z < 3; z++) {
    for (int i = 1; i <= n; i++)
      cout << Find(i, z) << " ";
    cout << endl;
  }
#endif

  // Zliczamy reprezentantow
  for (int i = 1; i <= n; i++)
    if (Find(i, 0) == i)
      score++;

  cout << score << endl;
  return 0;
}
