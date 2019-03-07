/* 
 * Input: (s_1, ..., s_n) (p)
 * L = max_i |s_i|
 * S = sum_i |s_i|
 * Preprocessing: O(S)
 * Zapytanie: O(L*|p|)
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Node {
    Node * parent; // Wezel reprezentujacy string, krotszy o jeden znak.
    map<char, Node*> sons; // Wezly reprezentujace stringi powstale przez dodanie jednej litery.
    vector<int> ids; // Wektor id stringow konczacych sie w danym wezle.
};

void free_node(Node* n) {
    n->sons.clear();
    n->ids.clear();
    delete n;
}

void recursive_free_node(Node *n) {
    for(auto son : n->sons) {
        recursive_free_node(son.second);
    }
    free_node(n);
}

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node;
    }
    ~Trie() {
        recursive_free_node(root);
    }
    
    /* 
     * Aktualizuje strukture drzewa o dany string ze znanym id.
     */
    void insert(int id, string& p) {
    /* Zainicjalizuj zmienne pomocnicze. (Zacznij parsowanie stringa od roota.)
     * Dla każdego znaku ze stringa:
     * - Sprawdz czy dany znak jest w zbiorze synow danego wezla
     * - - Jesli jest, to ten wezel jest aktualnym wezlem
     * - - Wpp utworz nowy wezel i przypnij go do ostatniego wezla.
     * - Zaaktualizuj ostatni wezel 
     * - Wstaw id stringu do vectora w wezle */

        // TODO
    }
    
    /* 
     * Dla danego stringu s, mask[id] == true wtw. string o danym id jest podciagiem s.
     */
    void find(string& s, vector<bool>& mask) {
    /* Zainicjalizuj wektor zawierajacy wszystkie wezly,
     * ktore reprezentuja sufiksy wystepujace w stringu 
     * Nalezy utworzyc dwie warstwy. 
     * W warstwie pierwszej nalezy umiescic korzen (roota). */

    // TODO
    
    /* Dla kazdego znaku ze stringa:
     * - oraz dla kazdego sufiksu z aktualnej warstwy, 
     * -- sprobuj przedluzyc aktualny sufiks o znak.
     * -- Jesli jest to mozliwe to do kolejnej warstwy wrzuc przedluzone sufiksy. 
     * --- Nastepnie, jesli ids danego wezla jest niepuste to zaktualizuj maske.*/

    // TODO
    }
};


int main() {
    string s, p;
    int n;
    Trie t;
    vector<bool> mask;
    
    cin >> s >> n;
    for(int i = 0; i < n; i++) {
        cin >> p;
        t.insert(i, p);
    }
    
    mask.resize(n, false);
    t.find(s, mask);
    for(bool b : mask) {
        cout << (b ? "Y" : "N") << endl;
    }
    
    return 0;
}
