/* 
 * Input: (s_1, ..., s_n) (p)
 * L = max_i |s_i|
 * S = sum_i |s_i|
 * z = liczba wystapien
 * Preprocessing: O(S)
 * Zapytanie: O(|p| + z)
 */

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    Node * parent; // Wezel reprezentujacy string, krotszy o jeden znak.
    map<char, Node*> sons; // Wezly reprezentujace stringi powstale przez dodanie jednej litery.
    vector<int> ids; // Wektor id stringow konczacych sie w danym wezle.
    
    int level; // Dlugosc sciezki do roota. (stringu konczacego sie w danym wezle)
    Node* suffix_link; // Wezel o najdluzszym krotszym wspolnym sufiksie. (root jesli nie ma)
    Node* shortcut; // Wezel o najdluzszym wspolnym sufiksie, zawierajacy niezerowa liczbe id. (root jesli nie ma)
};

void free_node(Node* n) {
    for(auto son : n->sons) {
        free_node(son.second);
    }
    n->sons.clear();
    n->ids.clear();
    delete n;
}

void print_trie(Node *n, string& s) {
    cout << n << "[" << n->level << "]*" << n->ids.size() << "*(" 
        << s << ")->" << n->suffix_link << "->" << n->shortcut << endl;
    if(n->sons.empty()) {
        return;
    }
    
    for(auto it : n->sons) {
        s.push_back(it.first);
        print_trie(it.second, s);
        s.pop_back();
    }
}


class Trie {
private:
    Node* root;
    
    /* Zwraca true jesli z danego wezla wychodzi krawedz ze znakiem c */
    inline bool can_transition(Node* n, char c) {
        //TODO
    }
    
    /*
     * Dokonuje tranzycji po zwyklych krawedziach, zuzywajac jedna krawedz.
     * Jesli istnieje (v1) --c--> (v2) to zwraca v2,
     * wpp zwraca korzen (root).
     */
    Node* simple_transition(Node* n, char c) {
        //TODO
    }
    
    /* 
     * Dokonuje tranzycji wstecznej po krawedziach wstecznych 'suffix_link',
     * dopoki nie moze dokonac tranzycji naprzod.
     * Wykonuje tranzycje naprzod.
     * 
     * Znajduje najdluzszy sufiks.
     */
    Node* transition(Node* n, char c) {
        // TODO
    }

public:
    Trie() {
        root = new Node;
    }
    ~Trie() {
        free_node(root);
    }
    
    
    /* 
     * Aktualizuje strukture drzewa o dany string ze znanym id.
     * TODO: Dodaj obliczanie 'level' dla wszystkich wezlow. (Reszta jest analogiczna). 
     */
    void insert(int id, string& p) {
        // TODO
    }
    
    /*
     * Znajduje 'suffix_link' oraz 'shortcut' dla wszystkich wezlow w drzewie.
     */
    void find_suffix_links() {
        /* Uzywajac algorytmu BFS (z kolejka), nalezy znalezc odpowiednie sciezki wsteczne.
         * Wskazowka: prosciej jest to zrobic z poziomu ojca.
         * 
         * Jesli wezel jest na glebokosci < 2 to oba wskazniki ustawiamy na korzen.
         * Wpp
         * Dla kazdego syna (p --c--> v) znajdujemy najdluzszy wspolny sufiks ('suffix_link'), 
         * korzystajac z sufiksu obliczonego dla rodzica.
         * 
         * Pokazać, że skrot da sie obliczyc w ponizszy sposob:
         * shortcut = (link->ids.empty() ? link->shortcut : link);
         */
         
        // TODO
    }
    
    /* 
     * Dla danego stringu s, mask[id] == true wtw. string o danym id jest podciagiem s.
     */
    void find(string& s, vector<bool>& mask) {
        /* Zacznij przeszukiwanie grafu od korzenia (root). 
         * Dla kazdego znaku ze stringa:
         * -Dokonaj tranzycji o jeden znak. (v_1) --c--> (v_2)
         * -Korzystajac ze znalezionych skrotow ('shortcut') zaaktualizuj maske, 
         *  skaczac, dopoki jest to mozliwe.
         */
        
        // TODO
    }
    
    void print() {
        string s = "";
        print_trie(root, s);
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
    
    t.find_suffix_links();
    //t.print();
    
    mask.resize(n, false);
    t.find(s, mask);
    for(bool b : mask) {
        cout << (b ? "Y" : "N") << endl;
    }
    
    return 0;
}
