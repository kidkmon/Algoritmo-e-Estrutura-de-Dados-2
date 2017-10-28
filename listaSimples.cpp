#include <iostream>
#define BRANCO 0
#define CINZA 1
#define PRETO 2
using namespace std;

//não sei qual é o typedef certo pra cor
//typedef int cor;
typedef string cor;

class Item {
public:
    cor item;
    Item() {}
    Item(cor item) {
        this->item = item;
    }
    void print();

};

class No {
public:
    Item item;
    No* prox;

    No () {
        prox = NULL;
    }

    No (Item item) {
        this->item = item;
        prox = NULL;
    }
};

class LSE {
private:
    No* prim, *ult;
public:
    LSE () {
        prim = new No();
        prim->prox = NULL;
        ult = prim;
    }

    void insere(Item);
    No* pred(No*);
    bool vazia();
    No* busca(Item);
    void remove(No*, Item&);
    void print();

};

bool LSE::vazia() {
    return prim == ult;
}

void LSE::insere(Item item) {
    ult->prox = new No();
    ult = ult->prox;
    ult->prox = NULL;
    ult->item = item;
}

No* LSE::pred(No* r) {
    No* p = prim->prox;
    while (p->prox != r) {
        p = p->prox;
    }
    return p;
}

void LSE::remove(No* r, Item& item){
    if (vazia() || r == NULL || r == prim) {
        cout << "impossível remover\n";
    }
    else {
        item = r->item;
        No* p = pred(r);
        p->prox = r->prox;
        if (p->prox == NULL) ult = p;
        delete r;
    }
}

void LSE::print() {
    No* p = prim->prox;
    while (p != NULL) {
        p->item.print();
        p = p->prox;
        cout << endl;
    }
}

void Item::print() {
    cout << item << endl;
}
