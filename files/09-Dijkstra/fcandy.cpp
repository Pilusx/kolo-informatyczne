#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int n, D, M, C, res = INT_MAX, nv;
vector<int> k;
vector<int> c;
vector<bool> visited;
vector<int> update[2];

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
    visited[0] = true;
    
    for(int i = 1; i <= n; i++) { // O(CKN)
        int dc = c[i];
        for(int i = 0; i < 2; i++)
            update[i].clear();
        
        for(int i = 0; i + dc < visited.size(); i++)
            if(visited[i] && !visited[i + dc]) 
                update[0].push_back(i);
        
        for(int j = 1; j <= k[i] && !update[(j+1)%2].empty(); j++) {
            update[j%2].clear();
            for(auto& v : update[(j+1)%2]) {
                nv = v + dc;
                if(nv < visited.size() && !visited[nv]) {
                    visited[nv] = true;
                    res = min(res, abs(2*nv - D));
                    update[j%2].push_back(nv);
                }
            }
        }
    }
    
    cout << res << endl;
    return 0;
}
