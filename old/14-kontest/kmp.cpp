#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

string h;
vector<int> lps;
vector<bool> z;

// #define DEBUG
/* Print vector */
template<typename T, typename R>
void pvec(R v, const char * comment, int space=1) {
    #ifdef DEBUG
    cerr.width(3);
    cerr << string(comment);
    for (T t : v){
        cerr << " ";
		cerr.width(space);
		cerr << t;
	}
    cerr << endl;
    #endif
}

/* Calculate longest prefix-suffix table */
void KMP(const string& p, const string& s) {
    h = '$' + p + '#' + s;
    lps.resize(h.size());
    for(size_t i = 2, k = 0; i < h.size(); i++) {
        while(k != 0 && h[k+1] != h[i]) k = lps[k];
        if(h[k+1] == h[i]) k++;
        lps[i] = k;
    }
}

/* Print all occurences of p in s */
void occurence(const string &p, const string &s){ 
    KMP(p, s);
    
    z.resize(h.size());
    size_t k = p.length();
    z[0] = false;
    lps[0] = 0;
    for(size_t i = 1; i < z.size(); i++)
        z[i] = i == k || lps[i] == k || z[lps[i]];

    for(size_t i = 0; i < s.size(); i++)
        if(z[k + 2 + i]) cout << i - k + 1 << endl;

    pvec<char>(h, "H");
    pvec<int>(lps, "LPS");
    pvec<bool>(z, "Z");

}

int main() {
    ios_base::sync_with_stdio(0);

    int n, k;
    string p, s;
    cin >> n;
    while(n--) {
        cin >> k >> p >> s;
        occurence(p, s);
    }

    return 0;
}