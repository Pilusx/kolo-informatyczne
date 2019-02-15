/*
  Minimalistyczna biblioteka do dynamicznych macierzy
  Zastrzezenia:
  - Do macierzy mozna sie odwolywac jak do vector<vector<int>>.
  - Wpisywanie wartosci nie gwarantuje wpisania ich modulo P. np. d[0][0] = -1,
  nie wpisze (P-1).
  - Wszystkie zmienne sa publiczne, a wiec zakladamy, ze uzytkownik wie co robi.
  np. zmiana wartosci w shape, aktualnie nie zmienia rozmiaru macierzy.
  np. podanie wartosci shape w konstruktorze ustawia rozmiar macierzy.
  - Moze miec bugi :)
*/

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

const int P = 420047;
inline int mmod(int x) { return x % P; }
inline int madd(int x, int y) { return mmod(x + y); }

class Vector : public vector<int> {
 public:
  int shape;
  /* Inicjalizuje vector 0 */
  Vector(int shape) : shape(shape) { resize(shape, 0); }
  /* Wypelnia vector zerami */
  void zeros() { fill(begin(), end(), 0); }
};

ostream& operator<<(ostream& os, const Vector& x) {
  for (int value : x) {
    os << value << " ";
  }
  return os;
}

class Matrix : public vector<Vector> {
 public:
  int shape[2];
  Matrix(const int shape[2]) {
    copy(shape, shape + 2, this->shape);
    resize(shape[0], Vector(shape[1]));
  }
  /* Wypelnia macierz zerami */
  void zeros() {
    for (Vector& row : *this) row.zeros();
  }
  /* Ustawia elementy na diagonali na dana wartosc (value) */
  void set_diagonal(int value) {
    for (int i = 0; i < min(shape[0], shape[1]); i++) {
      this->operator[](i)[i] = value;
    }
  }
};

ostream& operator<<(ostream& os, const Matrix& A) {
  for (const Vector& row : A) {
    os << row << endl;
  }
  return os;
}

/* Mnozy przez siebie wektor i macierz */
void matvecmul(const Matrix& A, const Vector& x, Vector& b) {
  const int I = A.shape[0], J = A.shape[1];
  assert(J == x.shape);
  assert(I == b.shape);
  b.zeros();
  for (int i = 0; i < I; i++) {
    for (int j = 0; j < J; j++) {
      b[i] = madd(b[i], mmod(A[i][j] * x[j]));
    }
  }
}

/* Kopiuje macierz A do B */
void matcpy(const Matrix& A, Matrix& B) {
  const int I = A.shape[0], J = A.shape[1];
  assert(I == B.shape[0] && J == B.shape[1]);
  for (int i = 0; i < I; i++) {
    copy(A[i].begin(), A[i].end(), B[i].begin());
  }
}

/* C = A * B */
void matmul(const Matrix& A, const Matrix& B, Matrix& C) {
  const int I = A.shape[0], K = A.shape[1], J = B.shape[1];
  assert(K == B.shape[0]);
  assert(I == C.shape[0] && J == C.shape[1]);
  C.zeros();
  for (int i = 0; i < I; i++) {
    for (int j = 0; j < J; j++) {
      for (int k = 0; k < K; k++) {
        C[i][j] = madd(C[i][j], mmod(A[i][k] * B[k][j]));
      }
    }
  }
}

/* C = A ^ n */
void power(const Matrix& A, int n, Matrix& C) {
  const int K = A.shape[0];
  const int shape[2] = {K, K};
  assert(K == A.shape[1]);
  assert(K == C.shape[0] && K == C.shape[1]);
  Matrix mult = A;
  Matrix temp(shape);
  C.zeros();
  C.set_diagonal(1);
  while (n > 0) {
    cerr << "[" << n << "]" << endl;
    if (n % 2 == 1) {
      matmul(C, mult, temp);
      matcpy(temp, C);
    }
    matmul(mult, mult, temp);
    matcpy(temp, mult);
    n /= 2;
  }
}

#endif  // _MATRIX_HPP_