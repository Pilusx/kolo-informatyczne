#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Edge {
public:
  int x, y, w;
};

bool cmp(const Edge &e1, const Edge &e2) { return e1.w < e2.w; }

vector<int> father;
vector<int> size;
vector<Edge> edges;
int t, n, m, a, b, c;

// Na poczatku size[i] = 1, father[i] = i

int Find(int x) {
  if (father[x] == x)
    return x;
  else
    father[x] = Find(father[x]);
  return father[x];
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (a == b)
    return;
  if (size[a] < size[b]) {
    size[b] += size[a];
    father[a] = b;
  } else {
    size[a] += size[b];
    father[b] = a;
  }
}

int main() {
  cin >> n >> m;

  father.resize(n + 1);
  size.resize(n + 1);
  for (int i = 0; i < n + 1; i++) {
    father[i] = i;
    size[i] = 1;
  }

  for (int i = 0; i < m; ++i) {
    cin >> a >> b >> c;
    edges.push_back({a, b, c});
  }

  sort(edges.begin(), edges.end(), cmp);
  long long int res = 0;
  for (auto edge : edges) {
    if (Find(edge.x) != Find(edge.y)) {
      Union(edge.x, edge.y);
      res += (long long int)edge.w;
    }
  }
  cout << res << endl;
}
