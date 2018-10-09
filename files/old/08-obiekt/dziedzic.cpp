#include <iostream>
#include <set>
#include <vector>

using namespace std;

#ifdef Polecenie
0) Klasa punkt 'Point' majaca zmienne x, y

1) Interfejs odcinka (dwa punkty) 'ISegment'
- funkcja odleglosc

2) Implementacja odcinka 'Segment'

class ISegment {
public:
    virtual int length() const = 0; // O(1)
    virtual ISegment& operator+(Point x) = 0;
}

3) Implementacja krzywej 'Curve' V=(a0, a1, ...., an) E=(a0-> a1, ... an-1 -> an)

class IPolygon final : public ISegment {
public:
    virtual float area() const = 0; // O(n)
}

4) Implementacja wielokata 'Polygon' (jako krzywej zamkniętej) V=(a0, a1, ..., an) E=(a0->a1, ..., an->a0)


Przetestowac dla 
a1) (0,0) -> (4,0) -> (4,4) -> (0,4) // S=16 Obw=12
a2) (0,0) -> (3,0) -> (0,4) // S=12 Obw=12
a3) (3,5) -> (6,5) -> (3,9) // S=12 Obw=12
b1) (0,0) -> (4,0) -> (4,4) -> (0,4) -> (0,0) -> (2,2) -> (4,0) // (0,0))) // S=12 Obw = ...
b2) (0,0) -> (4,0) -> (4,4) -> (0,4) -> (2,2) //-> (0,0) // S=12 Obw=8 + ...
#endif
