#include <iostream>
#define BRANCO 0
#define CINZA 1
#define PRETO 2

using namespace std;

//não sei qual é o typedef certo pra cor
//typedef int cor;
typedef string Cor;
typedef int Posicao;
typedef string Chave;

class Item {
private:
    Cor item;
public:
    Item() {}
    Item(Cor item) {
        this->item = item;
    }
    void print();
    Cor getItem();
    void setItem(Cor);

};

class Lista {
private:
    Item *item;
    int TAM;
    int n; // tamanho corrente da lista
    bool posicaoValida(Posicao);
    bool vazia();
public:
    Lista (): Lista(100)  { }

    Lista(int tam) {
        n = 0;
        TAM = tam;
        item = new Item[TAM];
    }
    void insere(Item);
    void print();
    Item* busca(Cor);
    void remove(Posicao, Item&);
};

// --- TAREFA
Cor Item::getItem() {
    return item;
}

void Item::setItem(Cor item) {
    this->item = item;
}

void Item::print() {
    cout << item << endl;
}


// --- LISTA
void Lista::insere(Item x) {
    if (n < TAM) {
        n++;
        item[n] = x;
    }
    else {
        cout << "Lista cheia!\n";
    }
}

void Lista::print() {
    for (int i = 1; i <= n; i++)  {
        item[i].print();
        cout << endl;
    }
}
/*
Item* Lista::busca(Cor item) {
    item[0].setItem(item); // sentinela
    int i = n;
    while (item != item[i].getItem()) {
        i--;
    }
    if (i > 0) return &item[i];
    else return NULL;
}
*/

bool Lista::posicaoValida(Posicao pos) {
    return 1 <= pos && pos <= n;
}

bool Lista::vazia() {
    return n == 0;
}

void Lista::remove(Posicao pos, Item &t) {
    if (!vazia() && posicaoValida(pos)) {
        t = item[pos];
        for (int i = pos; i < n; i++) {
            item[i] = item[i + 1];
        }
        n--;
    }
    else {
        cout << "Lista vazia ou posição inválida!\n";
    }
}