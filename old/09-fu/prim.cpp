#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Edge {
public:
  int x, y, w;
};

class cmp {
public:
  bool operator()(const Edge &e1, const Edge &e2) { return e1.w > e2.w; }
};

vector<bool> visited;
vector<vector<Edge>> graph;
priority_queue<Edge, std::vector<Edge>, cmp> pq;

int v, e, v1, v2, w;
long long int res;

int main() {
  cin >> v >> e;
  visited.resize(v + 1);
  graph.resize(v + 1);
  for (int i = 0; i < e; i++) {
    cin >> v1 >> v2 >> w;
    graph[v1].push_back({v1, v2, w});
    graph[v2].push_back({v2, v1, w});
  }

  fill(visited.begin(), visited.end(), false);
  visited[1] = true;

  for (auto &edge : graph[1]) {
    pq.push(edge);
  }

  res = 0;
  while (!pq.empty()) {
    Edge ed = pq.top();
    pq.pop();
    int dst = ed.y;

    if (!visited[dst]) {
      visited[dst] = true;
      res += (long long int)ed.w;
      for (auto &edge : graph[dst]) {
        pq.push(edge);
      }
    }
  }
  cout << res << endl;
}
