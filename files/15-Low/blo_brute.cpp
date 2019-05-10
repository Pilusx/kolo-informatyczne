// Wzorowane na blo4.cpp

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
int V, E, x, y;

int count(int v) {
    visited[v] = true;
    int res = 1;
    for(int u : adj[v]) {
        if(!visited[u]) {
            res += count(u);
        }
    }
    return res;
}


long long int count() {
    long long int res = V * (V-1), c;
    for(int i = 1; i <= V; i++) {
        if(!visited[i]) {
            c = count(i);
            res -= c * (c - 1);
        }
    }
    return res;
}

#define prepv(x) x.resize(V+1)
#define prepvv(x, v) x.resize(V+1, v);

int main() {
    ios_base::sync_with_stdio(0);
    cin >> V >> E;
    prepvv(visited, false);
    prepv(adj);
    
    for(int i = 0; i < E; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i = 1; i <= V; i++) {
        fill(visited.begin(), visited.end(), false);
        visited[i] = 1;
        cout << count() << endl;
    }
}
