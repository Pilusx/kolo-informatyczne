
// Zadanie 2

#include <algorithm> // swap
#include <cassert>
#include <cstdio>
#include <iostream>

//#define TEMPLATE

using namespace std;

template <class T>
inline int isset(const T* ptr) {
  return ptr != NULL;
}

class Node {
private:
  Node *left, *right;
  int value;

public:
  static Node* new_node(int v) {
    Node* n = new Node;
    n->value = v;
    n->left = NULL;
    n->right = NULL;
    return n;
  }

  bool add(int v) {
    if (v == value)
      return false;

    if (v < value) {
      if (isset(left))
        return left->add(v);
      left = new_node(v);

    } else {
      if (isset(right))
        return right->add(v);
      right = new_node(v);
    }

    return true;
  }

  bool del(int v) {
    if (value == v && !isset(left) && !isset(right)) {
      delete this;
      return true;
    }

    if (v < value && isset(left) && left->del(v))
      left = NULL;
    if (value < v && isset(right) && right->del(v))
      right = NULL;
    return false;
  }

  void neg() {
    value = -value; // Neguje wartość
    if (isset(left))
      left->neg(); // Neguje lewe poddrzewo
    if (isset(right))
      right->neg();    // Neguje prawe poddrzewo
    swap(left, right); // Zamienia je miejscami
  }

  void print(ostream& os) const {
    if (isset(left))
      left->print(os);
    os << value << " ";
    if (isset(right))
      right->print(os);
  }
};

class Tree {
private:
  Node* root;

public:
  Tree() : root(NULL){};
  bool add(int v) {
    if (!isset(root)) {
      root = Node::new_node(v);
      return true;
    } else
      return root->add(v);
  }

  bool empty() const {
    return !isset(root);
  }

  void neg() {
    if (isset(root))
      root->neg();
  }

  void del(int v) {
    if (isset(root) && root->del(v))
      root = NULL;
  }

  void print(ostream& os) const {
    if (!isset(root))
      os << "[Empty]";
    else {
      os << "[Tree : ";
      root->print(os);
      os << "]";
    }
  }

  // Operatory cz. II
};

// Operatory cz. I

ostream& operator<<(ostream& os, const Tree& t) {
  t.print(os);
  return os;
}

void test_func() {
  cout << "===Test funkcji===" << endl;
#ifndef TEMPLATE
  Tree s;
#else
  Tree<int> s;
#endif // TEMPLATE
  s.add(3);
  assert(s.add(3) == false);
  assert(!s.empty());
  cout << s << endl;
  s.del(3);
  cout << s << endl;
  assert(s.empty());

  for (int i = 0; i < 15; i++) {
    int k = i * 17 % 41;
    s.add(k);
    s.add(-(k % 14));
  }

  cout << s << endl;
  s.neg();
  cerr << s << endl;

  for (int i = 0; i < 13; i++) {
    int k = i * 31 % 41;
    s.del(k);
    s.del(-(k % 7));
  }

  cout << s << endl;
}

void test_op() {
  cout << "===Test operatorów===" << endl;
#ifndef TEMPLATE
  Tree s;
#else
  Tree<int> s;
#endif // TEMPLATE

  s + 3;
  s + 3 + 3 + 3 + (3 + 0) + 3 + 3 + 3;
  assert(!s());
  s[cout];
  s - 3;
  s - 1 - 2 - 3 - 4 - (5 - 6);
  s - (-1);
  s[cout];
  assert(s());

  for (int i = 0; i < 15; i++) {
    int k = i * 17 % 41;
    s + k;
    s + (-(k % 14));
  }

  s[cout];
  !s;
  s[cerr];

  for (int i = 0; i < 13; i++) {
    int k = i * 31 % 41;
    s - k;
    s - (-(k % 7));
  }

  s[cout];
}

#ifdef TEMPLATE
void test_temp() {
  cout << "===Test template=== (przesuniete o 0.1 w prawo, po negacji w lewo)"
       << endl;
  Tree<float> s;
  s + 3.1;
  s + 3.1 + 3.1 + 3.1 + (3.1 + 0.0) + 3.1 + 3.1 + 3.1;
  assert(!s());
  s[cout];
  s - 3.1;
  s - 1 - 2 - 3 - 4 - (5 - 6);
  s - (-1);
  s[cout];
  assert(s());

  for (int i = 0; i < 15; i++) {
    int k = i * 17 % 41;
    s + (k + 0.1);
    s + (-(k % 14) + 0.1);
  }

  s[cout];
  !s;
  s[cerr];

  for (int i = 0; i < 13; i++) {
    int k = i * 31 % 41;
    s - (k - 0.1);
    s - (-(k % 7 + 0.1));
  }

  s[cout];
}
#endif // TEMPLATE

int main() {
  test_func();
  test_op();
#ifdef TEMPLATE
  test_temp();
#endif // TEMPLATE
}
