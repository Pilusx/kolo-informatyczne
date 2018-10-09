#include <queue>
#include <vector>
#include <climits> // INT_MAX
#include <iostream>

using namespace std;

typedef struct {
    int dest, w; // cel, waga
} Edge;

typedef struct {
    int x, w; // gdzie, dlugosc aktualnej sciezki
} Visitor;

class cmp {
public:
    bool operator()(const Visitor& a, const Visitor& b) {
        return a.w > b.w;
    }
};

priority_queue<Visitor, vector<Visitor>, cmp> pq;
vector<vector<Edge> > graph;
vector<int> dist; // Lepiej nie distance... http://www.cplusplus.com/reference/iterator/distance/
vector<int> father;

void dijkstra(int x) {   
    fill(father.begin(), father.end(), -1);
    fill(dist.begin(), dist.end(), INT_MAX);
    
    dist[x] = 0;
    father[x] = x;
    pq.push({x, 0});
    
    while(!pq.empty()) {
        Visitor v = pq.top();
        pq.pop();
               
        for(const Edge& e : graph[v.x]) {
            int new_dist = dist[v.x] + e.w;
            if(new_dist < dist[e.dest]) {
                dist[e.dest] = new_dist;
                father[e.dest] = v.x;
                pq.push({e.dest, new_dist});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, v, e, x ,y, w;
    cin >> t;
    while(t--) {
        cin >> v >> e;
        
        graph.clear();
        graph.resize(v+1);
        father.resize(v+1);
        dist.resize(v+1);
        
        while(e--) {
            cin >> x >> y >> w;
            graph[x].push_back({y, w});
        }
        
        cin >> x >> y;
        dijkstra(x);
        if(father[y] == -1)
            cout << "NIE" << endl;
        else
            cout << dist[y] << endl;
    }  
}
