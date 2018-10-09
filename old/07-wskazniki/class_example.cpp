#include <iostream>

using namespace std;

/// Klasa bez template'ow

class Point {
public:
    int x, y;
    // Konstruktor z listą inicjującą
    Point(int x, int y) : x(x), y(y) {}
    
    static Point middle() { return Point(0, 0); }
    
    // Operator+ zdefiniowany wewnątrz klasy
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point& operator +=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this; // Zwraca wskaźnik na siebie
    }
};

// Operator- zdefiniowany poza klasą
Point operator-(const Point& first, const Point& second) {
    return Point(first.x - second.x, first.y - second.y);
}

// Operator<< zdefiniowany poza klasą
ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

/// Klasa jako template

template<class T>
class TPoint {
private:
    T x, y;
public:
    TPoint(T x, T y) : x(x), y(y) {} // Konstruktor z listą inicjującą
    
    // Operator+ zdefiniowany wewnątrz klasy-template
    TPoint operator+(const TPoint& other) const {
        return TPoint(x + other.x, y + other.y);
    }
      
    // Deklaracja funkcji zdefiniowanej poza klasą
    template<class U>
    friend TPoint<U> operator-(const TPoint<U>& first, const TPoint<U>& second);
    
    // Deklaracja funkcji zdefiniowanej poza klasą
    template<class U> 
    friend ostream& operator<<(ostream& os, const TPoint<U>& p); 
};


// Definicja funkcji poza klasą korzystającą ze zmiennych prywatnych
template<class T>
TPoint<T> operator-(const TPoint<T>& first, const TPoint<T>& second) {
    return TPoint<T>(first.x - second.x, first.y - second.y);
}

// Definicja funkcji poza klasą korzystającą ze zmiennych prywatnych
template<class T>
ostream& operator<<(ostream& os, const TPoint<T>& p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}


using IntPoint = TPoint<int>; // Definiujemy sobie nowy typ, który zachowuje się jak Point

int main() {
    Point p (1, 2), q (3,4);
    TPoint<float> tp(3.14, 2.71), tq(2.71, 3.14);
    IntPoint ip(1, 2), iq(3, 4);
    
    cout << p << q << p + q << p - q;
    cout << Point::middle() << endl; // Wywołanie funkcji statycznej
    p+=q;
    cout << p + q << endl;
    cout << tp << tq << tp + tq << tp - tq << endl;
    cout << ip << iq << ip + iq << ip - iq << endl;
    
}
