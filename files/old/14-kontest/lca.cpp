#include <vector>
#include <iostream>

using namespace std;

typedef struct {
	int parent;
	int depth;
	vector<int> sons;
} node_t;

vector<node_t> nodes;

#define parent(i) nodes[i].parent
#define depth(i) nodes[i].depth
#define sons(i) nodes[i].sons

void dfs(int x) {
	if(x == 1) parent(x) = 1, depth(x) = 0;
	for(int son : sons(x)) {
		depth(son) = depth(x) + 1;
		dfs(son);
	}
}

int lca(int x, int y) {
	int dx = depth(x);
	int dy = depth(y);

	while(dx < dy) y = parent(y), dy--;
	while(dy < dx) x = parent(x), dx--;
	while(x != y) x = parent(x), y = parent(y);
	return x;
}

void test_case() {
	int v, e, q, f, t; /* Number of vertices, Number of edges, Number of queries, Node 'from', Node 'to' */
	cin >> v;
	nodes.clear();
	nodes.resize(v+1);
	
	for(f = 1; f <= v; f++) {
		cin >> e;
		while(e--) {
			cin >> t;
			sons(f).push_back(t);
			parent(t) = f;
		}
	}
	dfs(1);
	cin >> q;
	while(q--) {
		cin >> f >> t;
		cout << lca(f, t) << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	int t;
	cin >> t;

	for(int i = 1; i <= t; i++){ 
		cout << "CASE " << i << ":" << endl;
		test_case();
	}

	return 0;
}