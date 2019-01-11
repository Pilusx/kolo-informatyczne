#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    vector<int> numbers;
    int n, t, res;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t;
        numbers.push_back(t);
    }
    
    sort(numbers.begin(), numbers.end());
    res = 0;
    for(auto v : numbers) {
        res = max(res, v - res);
    }
    cout << res << endl;
    return 0;
}
