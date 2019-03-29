#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    bool rev;
    int id;
    int to;
};

Edge e;
int V, E, x, y, vmax;

vector<int> degout;
vector<bool> orientation;
vector<vector<Edge>> edges;
vector<bool> visited;

bool print() {
    cout << "IT" << endl << "D: ";
    for(int i = 1; i <= V; i++) {
        cout << degout[i] << " ";
    }
    cout << endl << "O: ";
    for(auto o : orientation) {
        cout << o << " ";
    }
    cout << endl;
}

bool dfs(int v) {
    bool b;
    visited[v] = true;
    
    if(degout[vmax] - 1 > degout[v]) {
        degout[v]++;
        return true;
    }
    
    for(auto e : edges[v]) {
        if(!visited[e.to] && (e.rev ^ orientation[e.id])) {
           #ifdef SHOW_REACHABLE
           cout << v << "->(" << e.to << " " << e.id << ")" << endl;
           #endif // SHOW_REACHABLE
           if(dfs(e.to)) {
               #ifdef SHOW_PATH
               cout << e.to << endl;
               #endif // SHOW_PATH
               orientation[e.id] = !orientation[e.id];
               return true;
           }
        }
    }
    return false;
}

bool search() {
#ifdef PRINT
    print();
#endif // PRINT
    vmax = 0;
    degout[0] = 0;
    for(int i = 1; i <= V; i++) {
        visited[i] = false;
        if(degout[vmax] <= degout[i]) {
            vmax = i;
        }
    }
    bool b = dfs(vmax);
    if(b) {
        degout[vmax]--;
    }
    return b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> V >> E;
    orientation.resize(E);
    degout.resize(V+1);
    edges.resize(V+1);
    visited.resize(V+1);
    
    for(int i = 0; i < E; i++) {
        cin >> x >> y;
        e = {0, i, y};
        edges[x].push_back(e);
        e = {1, i, x};
        edges[y].push_back(e);
        orientation[i] = 1;
        degout[x]++;
    }
    
    while(search());
    cout << degout[vmax] << endl;
    for(auto o : orientation) {
        cout << o << endl;
    }
#ifdef PRINT
    print();
#endif // PRINT
    return 0;
}
