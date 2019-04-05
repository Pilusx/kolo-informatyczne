// Wzorowane na blo4.cpp

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> num;
vector<int> low;
vector<bool> art;
vector<int> s;
typedef long long int lli;
vector<lli> res;
vector<vector<int>> cut;

int nr, V, E, x, y;

int dfs(int v, int o) {
    visited[v] = true;
    nr++;
    num[v] = nr;
    low[v] = num[v];
    s[v] = 1;
    
    for(int u : adj[v]) {
        if(u != o) {
            if(!visited[u]) {
                dfs(u, v);
                low[v] = min(low[v], low[u]);
                s[v] += s[u];
                if(low[u] >= num[v]) {
                    cut[v].push_back(u);
                }
            } else {
                low[v] = min(low[v], num[u]);
            }
        }
    }
    int r = V - 1;
    for(int u : cut[v]) {
        r -= s[u];
    }
    for(int u : cut[v]) {
        lli su = s[u];
        res[v] += su * (- su + V - 1);
        res[v] += su * r;
    }
}

#define prepv(x) x.resize(V+1)
#define prepvv(x, v) x.resize(V+1, v);

int main() {
    ios_base::sync_with_stdio(0);
    cin >> V >> E;
    prepvv(visited, false);
    prepv(adj);
    prepv(low);
    prepv(num);
    prepv(s);
    prepv(art);
    prepv(cut);
    prepvv(res, (2 * (V - 1)));
    
    for(int i = 0; i < E; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, 0);
    
    for(int i = 1; i <= V; i++) {
        cout << res[i] << endl;
    }
}
