#include <cmath>
#include <cstdio>
#include <vector>

// Zadanie 1.1-4

using namespace std;

float avg, m, M;

void stats(const vector<float>& v) {
  m = 10000;
  M = -10000;
  avg = 0;
  for (float x : v) {
    avg += x;
    m = min(m, x);
    M = max(M, x);
  }
  avg /= v.size();
  printf("Avg=%.3f Min=%.3f Max=%.3f\n", avg, m, M);
}

int main() {
  int n;
  vector<float> t;

  scanf("%d", &n);
  t.resize(n);

  for (float& x : t)
    scanf("%f", &x);

  stats(t);

  for (float& x : t)
    x = abs(avg - x);

  for (auto x : t)
    printf("%.2f ", x);
  printf("\n");

  stats(t);

  return 0;
}

// Zadanie 1.5-7
