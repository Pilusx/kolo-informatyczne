#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long int num_t;

class Pair {
public:
    num_t i;
    num_t value;

    bool operator<(Pair& other) {
        return value < other.value;
    }
    bool operator==(const Pair& other) {
        return value == other.value;
    }
};

ostream& operator<<(ostream& os, Pair &p) {
    os << '[' << p.i << ',' << p.value << ']';
    return os;
}

vector<num_t> x;
vector<Pair> a, b, c;

/* O(log k) */
num_t power(num_t n, num_t k, num_t p) {
    num_t temp = 1, npow = n;
    while(k > 0) {
        if(k%2 == 1) temp *= npow, temp %= p;
        npow *= npow, npow %= p; 
        k/=2;
    }
    return temp;
}

int main() {
    ios_base::sync_with_stdio(0);

    num_t k = 40097, m = 1000, p = 1000000007;

    for(num_t i = 0; i <= m; i++)
        x.push_back(k + i);

    for(num_t i : x) { /* O(m log p) */
        a.push_back({i, power(i, p*k, p)});
        b.push_back({i, power(i, p*m, p)});
        c.push_back({i, power(i, p*p, p)});
    }

    sort(c.begin(), c.end()); /* O(mlogm) */

    for(Pair ia : a) { /* O(m^2 logm) */
        for(Pair ib : b) {
            num_t value = (2*p - ia.value + ib.value)%p;
            Pair pa = {0, value};
            vector<Pair>::iterator vit = find(c.begin(), c.end(), pa);
            if(vit != c.end()) {
                cout << "(" << ia << "," << ib << "," << *vit << ")" << endl;
            }
        }
    }
}
