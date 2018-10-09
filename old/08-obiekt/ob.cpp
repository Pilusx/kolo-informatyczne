#include <iostream>
#include <set>
#define PROG 11

using namespace std;

class A {
public:
    int x;
    int get_x() const { return x; }
    void set_x(int x) { this->x = x; }
    void print() const { cout << "Jestem A" << endl; }
    static void print(const A& a) { cout << "Jestem A (static)" << endl; }
};


/// Dziedziczenie public
#if PROG == 1
class B : public A {};

int main() {
    B b;
    b.x = 3;
    b.x++;
    cout << b.x << endl; // 4
}

/// Przykrywanie zmiennych
#elif PROG == 2
class B : public A {
public:
    int x;
};

int main() {
    B b;
    b.x = 4;
    cout << b.x << " " << b.get_x() << endl; // 4 ?
    b.set_x(13);
    cout << b.x << " " << b.get_x() << endl; // 4 13
}

/// Dziedziczenie protected
#elif PROG == 3
class B : protected A {
public:
    int y;
    int get_x() const { return x; }
};

int main() {
    B b;
    b.y = 3;
    b.y++;
    cout << b.get_x() << endl; // Dziala
    b.x = 2; // Blad kompilacji
}

/// Dziedziczenie private
#elif PROG == 4
class B : private A {};

int main() {
    B b;
    b.get_x(); // Blad kompilacji
    //b.set_x(3); // Tez nie zadziala
    //b.x = 5; // To tez nie
}


/// Is a has a
#elif PROG == 5
class Person {
public:
    int id; // Ma id
};

/// To nie dziala.
#elif PROG == 6
class Person : int {};


#elif PROG == 7
class B : public A {
public:
    void print() const { cout << "Jestem B" << endl; }
};

int main() {
    B b;
    b.print();
    A a = b;
    a.print();
    A::print(b);
    //B::print(b); // Blad kompilacji
    
}

/// Override && virtual && Klasy abstrakcyjne (takie ktore maja przynajmniej jedna funkcje wirtualna)
#elif PROG == 8
class IC {
public:
    virtual void print() = 0;
};

class C: public IC {};

class C2: public IC {
public:
    void print() override { cout << "Jestem C2" << endl; }
};

int main() {
    IC ic;
    C c;
    C2 c2;
    c2.print();
    
    
}

/// Final
#elif PROG == 9
class B final : public A {};
class C : public B {};


/// Diament
#elif PROG == 10
class B : public A {};
class C : public A {};
class D : public B, C {};
class E : public A, B {};

#elif PROG == 11
template<class T>
class Ta {
    T x;
};

template<class T>
class Tb : public Ta<T>{
    T y;
};

#endif


