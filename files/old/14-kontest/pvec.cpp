#include <iomanip>
#include <string>
using namespace std;

// #define DEBUG
/* Wypisz vector */
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

int main(){
	string s = "Hello World!";
	pvec<char>(s, "H");
	vector<int> v;
	pvec<int>(v, "V", 3);
}
