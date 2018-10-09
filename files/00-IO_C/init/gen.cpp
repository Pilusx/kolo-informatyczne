#include <fstream>

const int N = 500005;

int main() {
	std::fstream fs;
	fs.open("liczby.in", std::fstream::out);
	
	for(int i = 0; i < N; i++) {
		fs << i << "#";
	}
	
	fs.close();
}
