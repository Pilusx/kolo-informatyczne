https://en.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

#define INF 1000006
#define NIL 0

int matching;
int U, V;

vector<int> dist;
vector<int> pair_U, pair_V;
vector<vector<int>> adj;
queue<int> Q;

bool BFS() {
    for(int u = 1; u <= U; u++) {
        if(pair_U[u] == NIL) {
            dist[u] = 0;
            Q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[NIL] = INF;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        if(dist[u] < dist[NIL]) {
            for(int v : adj[u]) {
                int pv = pair_V[v];
                if(dist[pv]  == INF) {
                    dist[pv] = dist[u] + 1;
                    Q.push(pv);
                }
            }
        }
    }
    return dist[NIL] != INF;
}

bool DFS(int u) {
    if(u != NIL) {
        for(int v : adj[u]) {
            int pv = pair_V[v];
            if(dist[pv] == dist[u] + 1) {
                if(DFS(pv)) {
                    pair_V[v] = u;
                    pair_U[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int main() {
    int E, x, y;
    cin >> U >> V >> E;

    pair_U.resize(U+1, NIL);
    pair_V.resize(V+1, NIL);
    dist.resize(U+1, 0);
    adj.resize(U+1);
    
    for(int i = 0; i < E; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
    }

    matching = 0;
    // Match
    while(BFS()) {
        for(int u = 1; u <= U; u++) {
            if(pair_U[u] == NIL) {
                if(DFS(u)) {
                    matching = matching + 1;
                }
            }
        }
    }
    
    cout << matching << endl;
    
    return 0;
}
