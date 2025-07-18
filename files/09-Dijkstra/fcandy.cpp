#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int n, D, M, C, nv, res = INT_MAX, dc;
vector<int> k;
vector<int> c;
vector<bool> visited;
vector<int> update[2];

void visit(int nv) {
    visited[nv] = true;
    res = min(res, abs(2*nv - D));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    k.resize(n+1);
    c.resize(n+1);
    D = 0;
    C = 0;
    for(int i = 1; i <= n; i++) { // O(N)
        cin >> k[i] >> c[i];
        D += k[i] * c[i];
        C = max(C, c[i]);
    }
    M = (D + C)/2;
    visited.resize(M+1, false);
    visit(0);
    
    for(int i = 1; i <= n; i++) { // O(CKN)
        dc = c[i];
        
        update[1].clear();
        for(int nv = visited.size() - 1; nv - dc >= 0; nv--) {
            if(visited[nv-dc] && !visited[nv]) {
                visit(nv);
                update[1].push_back(nv);
            }
        }
        
        for(int j = 2; j <= k[i] && !update[(j+1)%2].empty(); j++) {
            update[j%2].clear();
            for(auto& v : update[(j+1)%2]) {
                nv = v + dc;
                if(nv < visited.size() && !visited[nv]) {
                    visit(nv);
                    update[j%2].push_back(nv);
                }
            }
        }
    }
    
    cout << res << endl;
    return 0;
}
