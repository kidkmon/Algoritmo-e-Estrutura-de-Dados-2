#include <iostream>
#include <vector>
#include <iomanip>

#define NUMVERTICES 100

using namespace std;

typedef int vertex;
typedef int Weight;

struct Grafo {
    //Matriz usa as linhas 1..n e colunas 1..n, e não utiliza a linha 0 e coluna 0.
    Weight mat[NUMVERTICES+1][NUMVERTICES+1];
    int n, m;
};

//funções do Grafo por Struct
void initial(Grafo &g){
    for(int i =0; i <= g.n;i++){
        for(int j = 0; i <= g.n;i++){
            g.mat[i][j] = 0;
        }
    }
}

void insertEdge (vertex u, vertex v, Weight w, Grafo &g){
    g.mat[u][v] = w;
    g.mat[v][u] = w;
    g.m++;
}

void print (Grafo g){
    int k = 3; //largura de campo
    cout << " ";
    for(int j = 1;j <= g.n;j++){
        cout << setw(k) << j;
    }
    cout << endl;
    for(int j = 1;j <= g.n*k+3;j++){
        cout << "-";
    }
    cout << endl;
    for(int i = 1; i <= g.n;i++){
        cout << setw(1) << i; cout << " |";
        for(int j = 1; j <= g.n;j++){
            cout << setw(k) << g.mat[i][j];
        }
        cout << endl;
    }
}

/*class MST{
public:
    Prim(G,r,w);
};


MST::Prim(G,r,w){

} */



class Item {
public:
    int item;
    Item() {}
    Item(int item) {
        this->item = item;
    }
    void print();

};

class Vertice {
public:
    Item item;
    Vertice* prox;

    Vertice () {
        prox = NULL;
    }

    Vertice (Item item) {
        this->item = item;
        prox = NULL;
    }
};

class LSE {
private:
    Vertice* prim, *ult;
public:
    LSE () {
        prim = new Vertice();
        prim->prox = NULL;
        ult = prim;
    }

    void insere(Item);
    Vertice* pred(Vertice*);
    bool vazia();
    Vertice* busca(Item);
    void remove(Vertice*, Item&);
    void print();

};

bool LSE::vazia() {
    return prim == ult;
}

void LSE::insere(Item item) {
    ult->prox = new Vertice();
    ult = ult->prox;
    ult->prox = NULL;
    ult->item = item;
}

Vertice* LSE::pred(Vertice* r) {
    Vertice* p = prim->prox;
    while (p->prox != r) {
        p = p->prox;
    }
    return p;
}

void LSE::remove(Vertice* r, Item& item){
    if (vazia() || r == NULL || r == prim) {
        cout << "impossível remover\n";
    }
    else {
        item = r->item;
        Vertice* p = pred(r);
        p->prox = r->prox;
        if (p->prox == NULL) ult = p;
        delete r;
    }
}

void LSE::print() {
    Vertice* p = prim->prox;
    while (p != NULL) {
        p->item.print();
        p = p->prox;
        cout << endl;
    }
}

void Item::print() {
    cout << item << endl;
}





int main() {

    return 0;
}