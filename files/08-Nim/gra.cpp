#include <iostream>
#include <vector>

using namespace std;

#define DEBUG

typedef struct chain {
    unsigned group;
    unsigned count;
    #ifdef DEBUG
    vector<unsigned> nodes;
    #endif
} chain_t;
vector<chain_t> uchains, chains;
unsigned n;

unsigned staircase() {
    unsigned t = 0;
    for(auto& v : chains) if(v.group%2) t^=v.count;
    return t;
}

unsigned options(unsigned x) {
    unsigned res = 0;
    unsigned last_count = 0, last_group = 0;
    for(auto& v : chains) {
        unsigned g = v.group, s = v.count, p;
        if(last_group + 1 != g) last_count = 0;
        p = x^last_count - last_count;
        if((g%2==1) && (x^s < s)) res++;
        if((g%2==0) && (g>2) && (p>0) && (p<=s)) res++;
        last_group = g;
        last_count = s;
    }
    return res;
}

void merge() {
    for(auto& v : uchains) {
        if(!chains.empty()) {
            auto& last = chains.back();
            if(last.group + last.count == v.group) {
                last.count++;
                continue;
            }
        }
        chains.push_back(v);
    }
    uchains.clear();
    unsigned limit = n, new_limit;
    unsigned group_count = 0;
    for(auto& v : chains) {
        new_limit = v.group;
        v.group = limit - (v.group + v.count) + group_count;
        group_count = v.group;
        limit = new_limit;
    }
}

unsigned task() {
    unsigned t, x, count, group;
    cin >> n >> t;
    for(int i = 0; i < t; i++) {
        cin >> x;
        uchains.push_back({x, 1});
        #ifdef DEBUG
        uchains.back().nodes.push_back(x);
        #endif
    }
    merge();
    for(auto& v : chains) {
        cout << v.group << " " << v.count << endl;
    }
    
    if(chains[0].group == 0) return 0;
    if(chains[0].group == 1) return chains[0].count;
    if((x = staircase()) == 0) return 0;
    return options(x);
}

int main() {
    ios_base::sync_with_stdio(0);
    cout << task() << endl;
    return 0;
}
