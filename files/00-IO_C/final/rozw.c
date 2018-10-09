#include <stdio.h>
#include <ctype.h>
#include <assert.h>

char c;
int n;
const int N = 500000;
int a;
long long int sum;
double d;

const int BUF_LEN = 16;

int main() {
	char buffer[BUF_LEN];
	
	scanf("%c:))-%d", &c, &n);
	assert(!isdigit(c));
	assert(!islower(c));
	assert(0 <= n && n < N);
	
	snprintf(buffer, BUF_LEN, "pref%.6i.in", n);
	
	FILE* fin = fopen("liczby.in", "r");
	FILE* fout = fopen(buffer, "w+");
	
	for(int i = 0; i < n; i++) {
		fscanf(fin, "%d#", &a);
		sum += a;
		fprintf(fout, "%lld ", sum);
	}
	
	d = (double) sum / n;
	printf("%.2f", d);
	
	fclose(fin);
	fclose(fout);
}
