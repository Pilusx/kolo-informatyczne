#include <ctime>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

const int M[] = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};
const int IM[] = {1, 7, 3, 9, 1, 7, 3, 9, 1, 7, 1};
const int R[] = {19, 20, 21, 22 ,18};

int ctoi(char c) {
	return c - '0';
}

bool czy_przestepny(string &current) {
	int rok = R[ctoi(current[2])/2]*100 + ctoi(current[0])*10 + ctoi(current[1]);
	return (rok%4 == 0 && rok%100 != 0) || (rok%400 == 0);
}

bool check_day(int day, int date_day, int date_month, int date_year) {
	tm t;
	t.tm_year = date_year;
	t.tm_mday = date_day;
	t.tm_mon = date_month - 1;
	return t.tm_wday == day%7;
}

bool ok(vector<int> &key, string &current) {
	size_t idx = current.find('?');
	if(idx != string::npos) {
		int sum = 0;
		for(size_t i = 0; i < current.size(); i++) {
			if(i == idx)
				continue;
			sum += M[i] * (ctoi(current[i]));
		}
		sum%=10;
		
		current[idx] = '0' + IM[idx]*(9 - sum);
	}
	
	if(key[0] != 0 && ctoi(current[9])%2 != key[0]%2)
		return false;
	
	
	bool b = czy_przestepny(current);
	if(key[2] == 1 && !b)
		return false;
	
	if(key[2] == 2 && b)
		return false;
	
	
	int year = R[ctoi(current[2])/2]*100 + ctoi(current[0])*10 + ctoi(current[1]),
		month = (ctoi(current[2])%2)*10 + ctoi(current[3]),
		day = (ctoi(current[4])*10) + ctoi(current[5]);
	if(key[1] != 0 && check_day(key[1], day, month, year))
		return false;
		
	return true;
}

int main() {
	ios_base::sync_with_stdio(0);
	
	string key, current;
	vector<int> v;
	
	int x, counter = 0;
	
	cin >> key >> x;
	for(size_t i = 0; i < key.size(); i++) {
		v.push_back(ctoi(key[i]));
	}
	
	for(int i = 0; i < x; i++) {
		cin >> current;
		if(ok(v, current))
			counter++;
	}
	cout << counter << endl;

	return 0;
}
