#include <climits>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n, D, M, C, res = INT_MAX;
vector<int> k;
vector<int> c;
vector<bool> visited;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    k.resize(n+1);
    c.resize(n+1);
    D = 0;
    C = 0;
    for(int i = 1; i <= n; i++) {
        cin >> k[i] >> c[i];
        D += k[i] * c[i];
        C = max(C, c[i]);
    }
    M = D + C;
    visited.resize(M+1, false);
    visited[0] = true;
    
    for(int i = 1; i <= n; i++) { // O(N)
        int dc = 2 * c[i];
        vector<int> update[2];
        for(int i = 0; i < visited.size() - dc; i++) 
            if(visited[i] && !visited[i + dc]) update[0].push_back(i);
        
        for(int j = 1; j <= k[i] && !update[(j+1)%2].empty(); j++) { // O(KC)
            update[j%2].clear();
            for(auto& v : update[(j+1)%2]) {
                int nv = v + dc;
                if(nv < visited.size() && !visited[nv]) {
                    visited[nv] = true;
                    res = min(res, abs(nv - D));
                    update[j%2].push_back(nv);
                }
            }
        }
    }
    
    cout << res << endl;
    return 0;
}
