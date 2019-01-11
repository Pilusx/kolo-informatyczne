#include <iostream>

using namespace std;

void task() {
    unsigned t, n, x;
    cin >> n;
    t = 0;
    for(unsigned i = 0; i < n; i++) {
        cin >> x;
        t ^= x;
    }
    cout << t << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    unsigned t;
    cin >> t;
    for(unsigned i = 0; i < t; i++) task();
    
    return 0;
}
