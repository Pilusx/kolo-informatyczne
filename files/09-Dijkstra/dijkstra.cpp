#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef struct Edge {
    int to;
    int dist;
} edge_t;

typedef struct Visit {
    int to;
    int new_dist;
} visit_t;

bool operator<(const visit_t& lhs, const visit_t& rhs) {
    return lhs.new_dist < rhs.new_dist;
}

vector<int> dist;
vector<vector<Edge>> graph;
vector<bool> visited;

#define MAX_INT std::numeric_limits<int>::max()

void dijkstra(int x) {
    set<Visit> pqueue;
    Visit v = {x, 0};
    pqueue.insert(v);
    while(!pqueue.empty()) {
        auto s = pqueue.begin();
        int x = s->to;
        int new_dist = s->new_dist;
        pqueue.erase(s);
        //cout << x << " " << new_dist << endl;    
        if(!visited[x]) {
            visited[x] = true;        
            if(dist[x] > new_dist) {
                dist[x] = new_dist; 
                for(auto& e : graph[x]) {
                    int y = e.to;
                    int new_dist_y = new_dist + e.dist;
                    v = {y, new_dist_y};
                    if(new_dist_y < dist[y]) {
                        pqueue.insert(v);
                    }
                }    
            }
        }
    }
}

void task() {
    int v, e, x, y, w;
    cin >> v >> e;
    graph.resize(v+1);
    dist.resize(v+1);
    visited.resize(v+1);
    fill(dist.begin(), dist.end(), MAX_INT);
    fill(visited.begin(), visited.end(), 0);
    for(int i = 0; i < e; i++) {
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
    }
    cin >> x >> y;
    
    dijkstra(x);
    if(dist[y] == MAX_INT) {
        cout << "NO" << endl;
    } else {
        cout << dist[y] << endl;
    }
    graph.clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) task();
}
