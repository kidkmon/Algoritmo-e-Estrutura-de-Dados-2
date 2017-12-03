#include <iostream>

using namespace std;
/*
class Aresta{
    int partida, destino, peso;
};

class Grafo{
    //V = numero de vertices, A = numero de arestas
    int V, A;
    Aresta<Aresta> *aresta;
public:
    Grafo criar (int V, int A){
        Grafo *grafo = new Grafo();
        this->A = A;
        this->V = V;
        Aresta *aresta = new Aresta[A];
    }

};

class Subset{
    int parente, rank;
public:
    int find (Subset[], int);
    void Union (Subset[], int, int);
    void KruskalMST(Grafo grafo);
};

int Subset::find(Subset subsets[], int i) {
    if(subsets[i].parente != i){
        subsets[i].parente = find(subsets,subsets[i].parente);
    }
    return subsets[i].parente;
}

void Subset::Union (Subset subsets[], int x, int y){
    int xroot = find(subsets,x);
    int yroot = find(subsets,y);

    if(subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parente = yroot;
    }else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parente = xroot;
    }
    else
    {
        subsets[yroot].parente = xroot;
        subsets[xroot].rank++;
    }
}

void Subset::KruskalMST(Grafo grafo) {
    int ;
}
*/

template<typename T>
class No{
private:
    T valor;
    No<T>* prox;
    No<T>* raiz;
public:
    No(){prox = NULL;}
    No(T);
    void setValor(T);
    void setProx(No<T>*);
    void setRaiz(No<T>*);
    T getValor();
    No<T>* getProx();
    No<T>* getRaiz();
};

template<typename T>
No<T>::No(T valor) {
    this->valor = valor;
    this->prox = NULL;
}

template<typename T>
void No<T>::setValor(T valor) { this->valor = valor; }

template<typename T>
void No<T>::setProx(No* prox) { this->prox = prox; }

template<typename T>
void No<T>::setRaiz(No* raiz) { this->raiz = raiz; }

template<typename T>
T No<T>::getValor() { return valor; }

template<typename T>
No<T>* No<T>::getProx() { return prox; }

template<typename T>
No<T>* No<T>::getRaiz() { return raiz; }

template<typename T>
class Aresta{
private:
    No<T> *partida, *destino;
    int peso;
public:
    void setPartida(No<T>*);
    void setDestino(No<T>*);
    void setPeso(T);
    No<T>* getPartida();
    No<T>* getDestino();
    T getPeso();
};

template<typename T>
void Aresta<T>::setPartida(No* partida) { this->partida = partida; }

template<typename T>
void Aresta<T>::setDestino(No* destino) { this->destino = destino; }

template<typename T>
No<T>* Aresta<T>::getPartida() { return partida; }

template<typename T>
No<T>* Aresta<T>::getDestino() { return destino; }

template<typename T>
void Aresta<T>::setPeso(T peso) { this->peso = peso; }

template<typename T>
void Aresta<T>::setPeso(T peso) { this->peso = peso; }


template<typename T>
class Grafo{
public:
    No<T>* vertice;
    Aresta<T>* aresta;
    Grafo();
};

template<typename T>
class Lista{
private:
    No<T>* prim;
    No<T>* ult;
public:
    Lista ();
    Lista (No<T>*);
    ~Lista(){}
    No<T>* getPrim();
    No<T>* busca(T);
    void insere(T);
    void remove(T);
    void print();
    void union_function(Lista<T>*, Lista<T>*);
    No<T> find_set(Lista<T>*);
    Lista<T> makeSet(No<T>*);
    Lista<T> mstKruskal(Grafo<T>*);
};

template<typename T>
Lista<T> Lista::mstKruskal(Grafo* grafo) {
    //grafo->lista de arestas = 0
    while(grafo->vertice != NULL){
        grafo->vertice = grafo->vertice->getProx();
    }
    //algoritmo de ordenacao em ordem nao decrescente de peso
    //for
    if(find_set(u) != find_set(v) ){
        //grafo->lista de aresta.add
        union_function(u,v);
    }
    //return grafo->lista de arestas;
}


template <typename T>
Lista<T> Lista<T>::makeSet(No<T> *x) {//Funcao que cria uma lista/conjunto de um so no/representante
    return Lista(x);
}

template <typename T>
void Lista<T>::union_function(Lista<T> *x, Lista<T> *y) { //Funcao que une duas listas, quando for chamada tem que fazer
                                                          //a(s) raiz(es) da arvore menor apontar pra raiz da arvore maior
    y->ult = x->prim;
    x->prim->setRaiz(y->prim);
    while(!x->ult){ //Fazer uma condicao que faça percorrer a lista
        x->prim->getProx()->setRaiz(y->prim); //Aqui dentro tem que trocar em cada no da lista a raiz para o primeiro no de y
    }
}

template <typename T>
No<T> Lista<T>::find_set(Lista<T> *x) {//Funcao procura a raiz da lista/arvore
    return x->prim;
}

template <typename T>
Lista<T>::Lista(No<T> *x){
    prim = new No<T>(x);
    prim->setProx(NULL);
    ult = prim;
}

template <typename T>
Lista<T>::Lista(){
    prim = new No<T>;
    prim->setProx(NULL);
    ult = prim;
}

template<typename T>
No<T>* Lista<T>::getPrim(){
    return prim;
}

template<typename T>
No<T>* Lista<T>::busca(T elemento){
    No<T>* p = prim->getProx();
    while(p != NULL && p->getValor() != elemento){
        p = p->getProx();
    }
    return p;
}

template<typename T>
void Lista<T>::insere(T elemento){
    ult->setProx(new No<T>);
    ult = ult->getProx();
    ult->setProx(NULL);
    ult->setValor(elemento);
    ult->setRaiz(prim);
}

template<typename T>
void Lista<T>::print(){
    No<T>* p = prim->getProx();
    while(p != NULL){
        cout << p->getValor() << " ";
        p = p->getProx();
    }
    cout << endl;
}

/*
template<typename T>
class Kruskal{
private:
    Grafo<T>* grafo;
public:
    void setGrafo(Grafo*);
    Grafo<T>* getGrafo();
    void mstKruskal(Grafo*);
};


template<typename T>
void Kruskal<T>::setGrafo(Grafo* grafo) { this->grafo = grafo; }

template<typename T>
Grafo<T>* Kruskal<T>::getGrafo() { return grafo; }
*/

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}