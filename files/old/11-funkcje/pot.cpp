#include <cstdio>	// size_t
#include <algorithm> // min, generate, max
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template <typename T, size_t N, size_t M>
class Matrix
{
  public:
	T value[N][M];

	void set(T val)
	{
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < M; j++)
				value[i][j] = val;
	}

	inline void zero() { set(0); }

	void one()
	{
		zero();
		for (size_t i = 0; i < min(N, M); i++)
			value[i][i] = 1;
	}

	T *operator[](int n)
	{
		return value[n];
	}

	const T *operator[](int n) const
	{
		return value[n];
	}

	Matrix<T, N, M> operator+(const Matrix<T, N, M> &B) const
	{
		Matrix<T, N, M> res;
		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < M; j++)
				res[i][j] = value[i][j] + B[i][j];
		return res;
	}

	template <size_t R>
	Matrix<T, N, R> operator*(const Matrix<T, M, R> &B) const
	{
		Matrix<T, N, R> res;
		res.zero();

		for (size_t i = 0; i < N; i++)
			for (size_t j = 0; j < R; j++)
				for (size_t k = 0; k < M; k++)
					res[i][j] += value[i][k] * B[k][j];
		return res;
	}
};

template <typename T, size_t N, size_t M>
ostream &operator<<(ostream &os, Matrix<T, N, M> &A)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
			cout << A.value[i][j] << " ";
		cout << endl;
	}
	return os;
}

class Integer
{
  public:
	int value;
	Integer(int x = 0) : value(x) {}
	void zero() { value = 0; }
	void one() { value = 1; }
	Integer operator+(const Integer &other) const { return Integer(value + other.value); }
	Integer operator*(const Integer &other) const { return Integer(value * other.value); }
	operator int() { return value; }
};

template <typename T>
void power(const T &x, size_t n, T &res)
{
	T temp, temp2;

	res.one(); // res = 1
	temp = x;

	while (n > 0)
	{
		if (n % 2 == 1)
			res = res * temp;

		temp = temp * temp;
		n /= 2;
	}
}

typedef Matrix<int, 2, 2> Mat;

int rec2(int a[2], int p[2], size_t n) {
    Matrix<int, 2, 1> ff, fres;
    Matrix<int, 2, 2> fs, fn;    
            
    for(size_t i = 0; i < 2; i++) {
        ff[i][0] = a[1-i];
        for(size_t j = 0; j < 2; j++)
            fs[i][j] = ( i == 0 ? p[1 - j] : (i == j + 1 ? 1 : 0));
    }
    
    power(fs, n, fn);
    fres = fn * ff;
    return fres[1][0];
}

int fibonacci(size_t n) {
    static int a[2] = {1, 1};
    static int p[2] = {1, 1};
    return rec2(a, p, n);
}

int lucas(size_t n)
{
    static int a[2] = {2, 1};
    static int p[2] = {1, 1};
	return rec2(a,p,n);
}

int int_power(size_t x, size_t n)
{
	Integer res;
	power(Integer(x), n, res);
	return res;
}

ostream &operator<<(ostream &os, vector<int> &v)
{
	for (auto x : v)
		cout << x << " ";
	return os;
}

void generate1(vector<int> &res, int (*func)(size_t), size_t n)
{
	res.resize(n);
	for (size_t i = 0; i < n; i++)
		res[i] = func(i);
}

int main()
{
	vector<int> v;

	generate1(v, [](size_t i) { return (int)i; }, 30);
	cout << v << endl;

	generate1(v, [](size_t i) { return (int)(1 << i); }, 30);
	cout << v << endl;

	generate1(v, [](size_t i) { return int_power(2, i); }, 30);
	cout << v << endl;

	generate1(v, &fibonacci, 30); // O(nlogn)
	cout << v << endl;

	generate1(v, &lucas, 30); // O(nlogn)
	cout << v << endl;
}
