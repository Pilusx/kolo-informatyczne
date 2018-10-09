#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
using vit = vector<int>::iterator;

void merge_sort(vit begin, vit end) {
    size_t len = distance(begin, end);
    
    if(len == 1)
        return;
    
    vit mid = begin + len/2;

    merge_sort(begin, mid);
    merge_sort(mid, end);
    
    vector<int> a;
    a.resize(len);
    merge(begin, mid, mid, end, a.begin());
    copy(a.begin(), a.end(), begin);
    a.clear();

    return;
}

void wypisz(vector<int> &v) {
    for(auto i : v)
        cout << i << " ";
    cout << endl;
}

int main() {
    const int N = 10;
    vector<int> t;
    
    t.resize(N);
    generate_n(t.begin(), N, rand);
    wypisz(t);
    cout << endl;
    
    merge_sort(t.begin(), t.end());
    
    wypisz(t);
    return 0;
}
